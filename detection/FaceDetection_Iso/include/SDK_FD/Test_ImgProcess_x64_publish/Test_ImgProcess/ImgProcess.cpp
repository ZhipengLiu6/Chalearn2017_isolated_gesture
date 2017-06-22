#include "ImgProcess.h"
#include "time.h"
#include "windows.h"

ImgProcess::ImgProcess():faceDetector("model\\VIPLFaceDetector4.0.1.dat")
{
	faceDetector.SetMinFaceSize(20);
	facenum = 0;
}

ImgProcess::~ImgProcess()
{

}

void ImgProcess::CvtGray(cv::Mat &src, cv::Mat &src_gray)
{
	if (src.channels() == 1)
		src_gray = src;
	else
		cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
}

void ImgProcess::CvtVIPLData(cv::Mat &src, VIPLImageData &srcdata)
{
	srcdata.channels = src.channels();
	srcdata.width = src.cols;
	srcdata.height = src.rows;
	srcdata.data = src.data;
}

void ImgProcess::SetFDPara(int minfacesize, int view, int performancelevel, int speedlevel)
{
	faceDetector.SetMinFaceSize(minfacesize);
	faceDetector.SetPerformanceLevel(performancelevel);
	faceDetector.SetSpeedLevel(speedlevel);
	if (view == 0)
		faceDetector.SetView(VIPLFaceView::Frontal);
	else
		faceDetector.SetView(VIPLFaceView::Frontal|VIPLFaceView::Profile);
}

void ImgProcess::GetFDResult(cv::Mat &src, int &facenum, VIPLFaceInfo *FDResult, int confidence)
{
	cv::Mat src_gray;
	CvtGray(src, src_gray);
	VIPLImageData src_gray_data;
	CvtVIPLData(src_gray, src_gray_data);
	time_t be = clock();
	facenum = faceDetector.Detect(src_gray_data);
	const VIPLFaceInfo *faces = faceDetector.GetDetections(&facenum, float(confidence));
	std::cout << "¼ì²âÊ±¼ä" << clock() - be << std::endl;
	for (int i = 0; i < facenum; i++)
	{
		FDResult[i] = *(faces+i);
	}
	
}

int ImgProcess::GetMaxFaceNum()
{
	int maxfacenum = 1024;
	return maxfacenum;
}

void ImgProcess::DrawFDResult(cv::Mat &src, int facenum, VIPLFaceInfo *FDResult, int thickness, cv::Scalar scalar)
{
	if (FDResult == NULL)
		return;
	for (int i = 0; i != facenum; i++)
	{
		cv::rectangle(src, cv::Rect(FDResult[i].x, FDResult[i].y, FDResult[i].width, FDResult[i].height), scalar, thickness);
	}
}

void ImgProcess::DrawSinFDResult(cv::Mat &src, int x, int y, int width, int height, int thickness, cv::Scalar scalar)
{
	cv::rectangle(src, cv::Rect(x, y, width, height), scalar, thickness);
}
