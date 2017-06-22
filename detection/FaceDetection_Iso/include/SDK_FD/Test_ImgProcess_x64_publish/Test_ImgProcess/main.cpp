#include "ImgProcess.h"
#include <iostream>
#include <fstream>

int main()
{
	cv::Mat src = cv::imread("img1.jpg");
	cv::Mat src_nomark = src.clone();
	cv::namedWindow("ss1", 1);
	cv::imshow("ss1", src);
	cv::waitKey(0);

	int facenum = 0;
	ImgProcess ImgProcessor;

	//参数分别为最小人脸，姿态、performance level 及speed level，具体设置方法请查看参考文档
	//姿态中0表示准正面，1表示侧面，2 表示正面、侧面都检测，
	//对于只有准正面的SDK这一参数不影响，设置为0即可
	ImgProcessor.SetFDPara(20, 0, 4, 3);


	VIPLFaceInfo FDResult[1024];

	//人脸检测，最后一个参数为置信度
	ImgProcessor.GetFDResult(src, facenum, FDResult, 11);
	if (facenum == 0)
		return 0;
	ImgProcessor.DrawFDResult(src, facenum, FDResult);
	cv::namedWindow("ss1", 1);
	cv::imshow("ss1", src);
	cv::waitKey(0);

	return 0;
}