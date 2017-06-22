#include <iostream>
#include <direct.h>
#include <fstream>
#include <io.h>
#include "afx.h"
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;


void getDefinedFiles(string path, vector<string>& results);
void getCurrentDir(string path, vector<string>& files);

void string_replace(string&s1,const string&s2,const string&s3)
{
	string::size_type pos=0;
	string::size_type a=s2.size();
	string::size_type b=s3.size();
	while((pos=s1.find(s2,pos))!=string::npos)
	{
		s1.replace(pos,a,s3);
		pos+=b;
	}
}

struct TwoDimension
{
	int x;
	int y;
};

//global variable
CvMat *mx1;
CvMat *my1;
CvMat *mx2;
CvMat *my2;

void RectifyPerCompute(CvMat *mx1, CvMat *my1, CvMat *mx2, CvMat *my2);
double getTwoDimDis(TwoDimension A, TwoDimension B);
void Depth2RGBRectify(TwoDimension src, TwoDimension &dst);

int main(int argc, char** argv)
{
	// this program is used argc argv
	// useage: CalibrationDepthVideo.exe [RootFolder(eg, Iso/Cons)]
	//preCompute
	int width = 320;
	int height = 240;
	CvSize imageSize={width, height};
	mx1=cvCreateMat(imageSize.height,imageSize.width,CV_32F);
	my1=cvCreateMat(imageSize.height,imageSize.width,CV_32F);
	mx2=cvCreateMat(imageSize.height,imageSize.width,CV_32F);
	my2=cvCreateMat(imageSize.height,imageSize.width,CV_32F);
	RectifyPerCompute(mx1, my1, mx2, my2);

	string exe_path = argv[0];

	int index = exe_path.find_last_of("\\");
	string root_path = exe_path.substr(0, index);
	string_replace(root_path, "\\", "\\\\");

	string original_root_path = root_path;
	string calibration_root_path = root_path+"\\CalibrationDepth";

	vector<string> datasets;
	getCurrentDir(original_root_path, datasets);
	_mkdir((calibration_root_path).c_str());
	for (int i=0; i<datasets.size(); i++)
	{
		cout<<datasets[i]<<endl;
		//创建相应层级的文件夹
		_mkdir((calibration_root_path+"\\"+datasets[i]).c_str());
		vector<string> subfolders;
		getCurrentDir(original_root_path+"\\"+datasets[i], subfolders);
		for (int j=0; j<subfolders.size(); j++)
		{
			cout<<"    "<<subfolders[j]<<endl;
			_mkdir((calibration_root_path+"\\"+datasets[i]+"\\"+subfolders[j]).c_str());
			vector<string> videos;
			getDefinedFiles(original_root_path+"\\"+datasets[i]+"\\"+subfolders[j]+"\\*K*.avi", videos);
			for (int k=0; k<videos.size(); k++)
			{
				//cout<<"        "<<videos[k]<<endl;
				//判断文件是否存在,如果存在直接跳过
				if(_access((calibration_root_path+"\\"+datasets[i]+"\\"+subfolders[j]+"\\"+videos[k]).c_str(), 0)!=-1)
					continue;
				//读取原始深度视频
				CvCapture* oriDepth = cvCreateFileCapture((original_root_path+"\\"+datasets[i]+"\\"+subfolders[j]+"\\"+videos[k]).c_str());
				CvVideoWriter* calDepth = cvCreateVideoWriter((calibration_root_path+"\\"+datasets[i]+"\\"+subfolders[j]+"\\"+videos[k]).c_str(),
					CV_FOURCC('M', 'J', 'P', 'G'), 10, cvSize(320, 240), 1);

				IplImage* oriImg = NULL;
				while ((oriImg = cvQueryFrame(oriDepth)) != NULL)
				{
					IplImage* calDepthImg = cvCreateImage(cvSize(oriImg->width, oriImg->height), oriImg->depth, oriImg->nChannels);
					for (int j=0; j<calDepthImg->height; j++)
					{
						for (int i=0; i<calDepthImg->width; i++)
						{
							((uchar*)(calDepthImg->imageData + j * calDepthImg->widthStep))[i * 3] = 255;
							((uchar*)(calDepthImg->imageData + j * calDepthImg->widthStep))[i * 3 + 1] = 255;
							((uchar*)(calDepthImg->imageData + j * calDepthImg->widthStep))[i * 3 + 2] = 255;
						}
					}
					for (int j=0; j<oriImg->height; j++)
					{
						for (int i=0; i<oriImg->width; i++)
						{
							TwoDimension src;
							src.x = i; src.y = j;
							TwoDimension dst;
							Depth2RGBRectify(src, dst);
							if(dst.x<0 || dst.x>calDepthImg->width || dst.y<0 || dst.y>calDepthImg->height)
								continue;
							((uchar*)(calDepthImg->imageData + dst.y * calDepthImg->widthStep))[dst.x * 3] = ((uchar*)(oriImg->imageData + j * oriImg->widthStep))[i * 3];
							((uchar*)(calDepthImg->imageData + dst.y * calDepthImg->widthStep))[dst.x * 3 + 1] = ((uchar*)(oriImg->imageData + j * oriImg->widthStep))[i * 3 + 1];
							((uchar*)(calDepthImg->imageData + dst.y * calDepthImg->widthStep))[dst.x * 3 + 2] = ((uchar*)(oriImg->imageData + j * oriImg->widthStep))[i * 3 + 2];
						}
					}
					cvWriteFrame(calDepth, calDepthImg);
					cvReleaseImage(&calDepthImg);
				}
				cout<<"        "<<videos[k]<<endl;
				cvReleaseCapture(&oriDepth);
				cvReleaseVideoWriter(&calDepth);
			}
		}
	}
	system("pause");
	return 0;
}

void getDefinedFiles(string path, vector<string>& results)
{
	HANDLE hFile;
	LPCTSTR lpFileName = path.c_str();
	WIN32_FIND_DATA pNextInfo;	//搜索得到的文件信息将储存在pNextInfo中;
	hFile = FindFirstFile(lpFileName, &pNextInfo);//请注意是 &pNextInfo , 不是pNextInfo;
	if(hFile == INVALID_HANDLE_VALUE)
	{
		//搜索失败
		exit(-1);
	}
	else
	{
		do 
		{
			if(pNextInfo.cFileName[0] == '.')//过滤.和..
				continue;
			results.push_back(pNextInfo.cFileName);
		} while(FindNextFile(hFile, &pNextInfo));
	}
}

void getCurrentDir(string path, vector<string>& files) 
{ 
	//文件句柄 
	long  hFile  =  0; 
	//文件信息 
	struct _finddata_t fileinfo; 
	string p; 
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1) 
	{ 
		do
		{  
			if((fileinfo.attrib & _A_SUBDIR)) 
			{ 
				if(strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0) 
				{
					files.push_back(fileinfo.name);
					//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
				}
			}  
		}while(_findnext(hFile, &fileinfo) == 0); 
		_findclose(hFile); 
	} 
} 


void RectifyPerCompute(CvMat *mx1, CvMat *my1, CvMat *mx2, CvMat *my2)
{
	double R1[3][3],R2[3][3],P1[3][4],P2[3][4];
	int width = 320;
	int height = 240;
	CvSize imageSize={width, height};
	//师姐计算出来的对齐参数
	double M1[3][3]={597.27, 0, 322.67, 0, 597.04, 232.64, 0, 0, 1};
	double M2[3][3]={529.45, 0, 319.35, 0, 530.51, 234.79, 0,0, 1};
        
	/*double D1[5]={3.71403933e-01, -1.29047451e+01, 0, 0, 1.56843994e+02};
	double D2[5]={4.39538926e-01, -1.70257187e+01, 0, 0, 2.23054718e+02};*/

	double D1[5]={0, 0, 0, 0, 0};
	double D2[5]={0, 0, 0, 0, 0};
	//double D2[5]={0.1884,-0.4865,0,-0.003,0.0007};

	double R[3][3]={0.9999,-0.0106,    0.0049,  0.0106,   0.9999,   0.0034, -0.0049,   -0.0034 ,  0.9999};
	double T[3]={25.0479, 0.2849, -2.0667};
	CvMat CvM1=cvMat(3,3,CV_64F,M1);
	CvMat CvM2=cvMat(3,3,CV_64F,M2);
	CvMat _D1=cvMat(1,5,CV_64F,D1);
	CvMat _D2=cvMat(1,5,CV_64F,D2);
	CvMat _R=cvMat(3,3,CV_64F,R);
	CvMat _T=cvMat(3,1,CV_64F,T);
	CvMat _R1=cvMat(3,3,CV_64F,R1);
	CvMat _R2=cvMat(3,3,CV_64F,R2);
	CvMat _P1=cvMat(3,4,CV_64F,P1);
	CvMat _P2=cvMat(3,4,CV_64F,P2);

	//imageSize=cvGetSize(bgrFrameL);
	cvStereoRectify(&CvM1,&CvM2,&_D1,&_D2,imageSize,&_R,&_T,&_R1,&_R2,&_P1,&_P2,0,0);

	cvInitUndistortRectifyMap(&CvM1,&_D1,&_R1,&_P1,mx1,my1);
	cvInitUndistortRectifyMap(&CvM2,&_D2,&_R2,&_P2,mx2,my2);
}

double getTwoDimDis(TwoDimension A, TwoDimension B)
{
	return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y) * 1.0;
}

void Depth2RGBRectify(TwoDimension src, TwoDimension &dst)
{
	TwoDimension facemiddle;
	int height = 240;
	int width = 320;
	facemiddle.x = cvmGet(mx2, src.y, src.x);
	facemiddle.y = cvmGet(my2, src.y, src.x);
	//cout<<"hello\n";
	//cout<<src.x<<" "<<cvmGet(mx1, src.y, src.x)<<endl;
	int aroundWidth = 30;
	int beginx = max(0, facemiddle.x - aroundWidth);
	int endx = min(width, facemiddle.x + aroundWidth);
	int beginy = max(0, facemiddle.y - aroundWidth);
	int endy = min(height, facemiddle.y + aroundWidth);
	double mindistance = 99999999999;
	//from depth to determination
	for(int i = beginy; i < endy; i++)
	{
		for(int j = beginx; j < endx; j++)
		{
			TwoDimension tmp;
			tmp.x = cvmGet(mx1, i, j);
			tmp.y = cvmGet(my1, i, j);
			double tmpdis = getTwoDimDis(tmp, facemiddle);
			if(mindistance > tmpdis)
			{
				mindistance = tmpdis;
				dst.x = j;
				dst.y = i;
			}
		}
	}
}