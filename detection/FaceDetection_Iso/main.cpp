// ProcessingDataConG.cpp : 定义控制台应用程序的入口点。
//
#pragma once
#include "stdafx.h"
#include "PreProcessGestureData.h"
#include <fstream>
#include <string>
#include <direct.h>
#include <iostream>
#include <io.h>
#include "afx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <math.h>
#include <stdio.h>
using namespace std;

void getCurrentDir(string path, vector<string>& files);
void getDefinedFiles(string path, vector<string>& results);

string filePath = ".\\sample\\IsoGD_Phase_1\\train";    //folder
CString Trainlist = ".\\sample\\IsoGD_Phase_1\\train_list.txt";   //filelist

int main()
{
	//写入格式：脸部中心坐标：(frame, x0, y0):x0 y0 每行一帧图片,若无法检测到人脸，则x0=y0=0;
	//			int temp=(int)((uchar*)(tempImg->imageData+y0*tempImg->widthStep))[x0];
	//			minDepth += temp;
	//
	PreProcessGestureData PreProcessFace;
	
	CString outputPath = ".\\sample\\FacePosition\\IsoRGBtraintFacePosition.txt";
	
	int videoLabel = -1;

	fstream trainfilestream;
	trainfilestream.open(Trainlist, ios::in);
	char tbuffer[256];
	vector<string> vdepthtrainlist;
	vector<int> vlabel;
	char rgbname[100], depthname[100];
	int label;
	char cdevel[100], cvideoID[100];
	char ctmp[100];
	while(trainfilestream.getline(tbuffer, 256))
	{
		//sscanf(tbuffer, "%s %s %d", rgbname, depthname, &label);
		sscanf(tbuffer, "%s %s", rgbname, depthname);
		string rgbname_str = rgbname;
		label = 0;
		int index1 = rgbname_str.find_first_of("/");
		int index2 = rgbname_str.find_last_of("/");
		string sdevel = rgbname_str.substr(index1+1, index2-index1-1);
		string svideoID = rgbname_str.substr(index2+1, rgbname_str.length()-index2-1);
		
		string stmp = sdevel + "\\"  + svideoID;
		std::cout<<stmp<<endl;
		vdepthtrainlist.push_back(stmp);
		vlabel.push_back(label);

		string dsdevel = sdevel;
		string dsvideoID = "K" + svideoID.substr(1, svideoID.length()-1);
		
		string dstmp = dsdevel + "\\"  + dsvideoID;
		std::cout<<dstmp<<endl;
		vdepthtrainlist.push_back(dstmp);
		vlabel.push_back(label);
	}
	
	int numVideo = vdepthtrainlist.size();
	for(int i = 0; i < numVideo; i++)
	{
		std::cout<<i<<"/"<<numVideo<<endl;
		string oneRGBVideoPath = filePath + "\\" + vdepthtrainlist[i];
		cout<<"RGB:"<<vdepthtrainlist[i]<<endl;
		i++;
		string oneDepthVideoPath = filePath + "\\" + vdepthtrainlist[i];
		cout<<"Depth:"<<vdepthtrainlist[i]<<endl;
		CvCapture *capture = cvCreateFileCapture(oneRGBVideoPath.c_str());
		int numFrames = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT); 
		if(numFrames < 1)
		{
			cout<<"video file's path is wrong and can be read"<<endl;
			//PreProcessFace.ReleaseVector();
			continue;
		}		
		CString finalFacePath;
		finalFacePath = outputPath;
		CString tmp = vdepthtrainlist[i].c_str();
		CString CSvideoid = tmp.Right(9).Left(5);
		int videoid = _ttoi(CSvideoid);
		cout<<"video id:"<<videoid<<endl;
		for(int i = 0; i < numFrames; i++)
		{
			IplImage* tempFrame = cvQueryFrame(capture);
			int countframe = i + 1;
			if(PreProcessFace.IsoOutheadDetectionVIPLSDK(tempFrame, finalFacePath, countframe, videoid))
				break;
			if(i == numFrames - 1)
			{
				PreProcessFace.readVideo(oneRGBVideoPath.c_str(), oneDepthVideoPath.c_str());
				PreProcessFace.getISoFacePositionHist(finalFacePath, countframe, videoid);
				PreProcessFace.ReleaseVector();
			}			
		}
		PreProcessFace.ReleaseVector();
		cvReleaseCapture(&capture);
	}
	for(int i = numVideo - 1; i >=0 ; i--)
	{
		vlabel.pop_back();
		vdepthtrainlist.pop_back();
	}
	vdepthtrainlist.clear();
	vlabel.clear();
	trainfilestream.close();

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
