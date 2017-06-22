/*
 * VIPL-FD-API.h
 *
 *  Created on: 2012-3-11
 *      Author: xwzhao
 */

#ifndef VIPL_FD_API_H_
#define VIPL_FD_API_H_

#include "FDDefine.h"

typedef void* VIPLFACEDETECTOR;

#ifdef __cplusplus
extern "C" 
{
#endif

//#define _WINDOWS_DLL_
//#define _WINDOWS_LIB_
//#define _LINUX_DLL_
//#define _LINUX_LIB_

// lizhe 2012-08-26
#if defined(_WINDOWS_DLL_)
   __declspec(dllexport)
#elif defined(_LINUX_DLL_)
		__attribute ((visibility("default")))
#endif
// ��ʼ��FD��Դ
bool FDInitialize(const char *sPath = 0, const PanLevel nPL = PL_1_30_degree, const RollLevel nRL = RL_1_20_degree, const TiltLevel nTL = TL_2_40_degree, const double modelReadProp = 0.7);

// �ͷ�FD��Դ
#if defined(_WINDOWS_DLL_)
   __declspec(dllexport)
#elif defined(_LINUX_DLL_)
		__attribute ((visibility("default")))
#endif
bool FDClose();

#if defined(_WINDOWS_DLL_)
   __declspec(dllexport)
#elif defined(_LINUX_DLL_)
		__attribute ((visibility("default")))
#endif
VIPLFACEDETECTOR CreateFaceDetector();

#if defined(_WINDOWS_DLL_)
   __declspec(dllexport)
#elif defined(_LINUX_DLL_)
		__attribute ((visibility("default")))
#endif
bool ReleaseFaceDetector(VIPLFACEDETECTOR facedetector);

#if defined(_WINDOWS_DLL_)
   __declspec(dllexport)
#elif defined(_LINUX_DLL_)
		__attribute ((visibility("default")))
#endif
void SetPose(VIPLFACEDETECTOR facedetector, PanLevel nP = PL_2_60_degree, RollLevel nR = RL_1_20_degree, TiltLevel nT = TL_2_40_degree);

#if defined(_WINDOWS_DLL_)
   __declspec(dllexport)
#elif defined(_LINUX_DLL_)
		__attribute ((visibility("default")))
#endif
int SetInputResolusion(VIPLFACEDETECTOR facedetector, int nInputWidth = 640, int nInputHeight = 480);

#if defined(_WINDOWS_DLL_)
   __declspec(dllexport)
#elif defined(_LINUX_DLL_)
		__attribute ((visibility("default")))
#endif
int SetMinDetectFaceSize(VIPLFACEDETECTOR facedetector, int nMDFSize = 35);

#if defined(_WINDOWS_DLL_)
   __declspec(dllexport)
#elif defined(_LINUX_DLL_)
		__attribute ((visibility("default")))
#endif
int SetSpeedAccuracyMode(VIPLFACEDETECTOR facedetector, int nSAM = 4);//������Чȡֵ��Χ1-14

#if defined(_WINDOWS_DLL_)
   __declspec(dllexport)
#elif defined(_LINUX_DLL_)
		__attribute ((visibility("default")))
#endif
void SetRunLayerNum(VIPLFACEDETECTOR facedetector, double iPara = 0.7);

#if defined(_WINDOWS_DLL_)
   __declspec(dllexport)
#elif defined(_LINUX_DLL_)
		__attribute ((visibility("default")))
#endif
int SetAccuracybyCondNum(VIPLFACEDETECTOR facedetector, int nACN = 1);//ͨ����������к�ĺ�ѡ����Ŀ������þ��ȣ�ȡֵ���⣬ȡֵԽ��Ҫ���ѡ��Խ������ж�Ϊ����

#if defined(_WINDOWS_DLL_)
   __declspec(dllexport)
#elif defined(_LINUX_DLL_)
		__attribute ((visibility("default")))
#endif
int FDFindFaces(VIPLFACEDETECTOR facedetector, const unsigned char* lpImageData, FACEINFO* lpFaces, int& detectedFaceNum);

#ifdef __cplusplus
}
#endif

#endif /* VIPL_FD_API_H_ */
