#ifndef IMGPROCESS_H
#define IMGPROCESS_H

#include "VIPLFaceDetector.h"
#include <cv.h>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <iostream>

class ImgProcess
{
public:
	ImgProcess();
	~ImgProcess();

	int GetMaxFaceNum();
	void CvtVIPLData(cv::Mat &src, VIPLImageData &srcdata);
	void CvtGray(cv::Mat &src, cv::Mat &src_gray);
	void SetFDPara(int minfacesize = 20, int view = 0, int performancelevel = 4, int speedlevel = 3);
	void GetFDResult(cv::Mat &src, int &facenum, VIPLFaceInfo *FDResult, int confidence = 20);
	void DrawFDResult(cv::Mat &src, int facenum, VIPLFaceInfo *FDResult, int thickness = 3, cv::Scalar scalar = cv::Scalar(255, 0, 0));
	void DrawSinFDResult(cv::Mat &src, int x, int y, int width, int height, int thickness = 3, cv::Scalar scalar = cv::Scalar(255, 0, 0));

private:
	VIPLFaceDetector faceDetector;

	int maxfacenum;
	int facenum;
	int featsize;

};

#endif