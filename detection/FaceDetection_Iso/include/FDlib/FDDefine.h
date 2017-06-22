#ifndef _JFD_DEFINE_H_
#define _JFD_DEFINE_H_

#include "VIPL_Structure.h"

//����ͼ���ʽ�ṹ����

/* ����Դ��������*/
// ����Դ����ṹ�嶨��
typedef struct{
	int nInputWidth; // ������Ƶ�ķֱ���
	int nInputHeight; 
	BitsPerPixel nBPP;//����ͼ��ĸ�ʽ
}IMAGEINFORPARAM;

////������ṹ����
//// ���������ת(Pan)�ļ�ⷶΧ��ȱʡLevel_1
//// 3 levels
//enum PanLevel
//{
//	PL_1_30_degree = 1,		// Level_1 +/-30 degree
//	PL_2_60_degree = 2,		// Level_2 +/-60 degree
//	PL_3_90_degree = 3,		// Level_3 +/-90 degree
//};
//
//// ����ƽ������ת(Roll)�ļ�ⷶΧ��ȱʡLevel_1
//// 2 levels
//enum RollLevel
//{
//	RL_1_20_degree = 1,		// Level_1 +/-20 degree
//	RL_2_45_degree = 2,		// Level_2 +/-45 degree
//};
//
//// ���ø�����ת(Tilt)�ļ�ⷶΧ��ȱʡLevel_1
//// 2 levels
//enum TiltLevel
//{
//	TL_1_20_degree = 1,		// Level_1 +/-20 degree
//	TL_2_40_degree = 2,		// Level_2 +/-40 degree
//};

/* ����������*/
// ������ṹ�嶨��
typedef struct{
	int nMinFaceLength; // ��С��������Ŀ�͸ߵĴ�С������ڸߣ�
	PanLevel nPanLevel; // 3����̬��ⷶΧ
	RollLevel nRollLevel;
	TiltLevel nTiltLevel;
	int nSpeedAccuracyMode; // ��⣨�ٶ�\���ȣ�ģʽ

	double nTailAccuracy;	//Tail�������ľ��ȿ���
	int nCondNumAccuracy;	//��ѡ�򾫶ȿ��Ʋ���
	double nHeadThresHold;	//Head����������ֵ
	int nXPace;				//X�����ⲽ��
	int nYPace;				//Y�����ⲽ��
}FDPARAM;

//��������Χ
typedef struct {
	PanLevel nPanClassifierRange;	//Pan������ת�Ƕ�
	RollLevel nRollClassifierRange;//Roll������ת�Ƕ�
	TiltLevel nTiltClassifierRange;//Tilt������ת�Ƕ�
}CLASSIFIERRANGEPARAM;


// changed to VIPL_Structure.h
////��⺯����������ṹ
//// �����ת(Pan)��Χ��־
//// 5 levels
//enum PanRange
//{
//	PR_LeftFullProfile = 1,
//	PR_LeftHalfProfile = 2,
//	PR_Frontal = 3,
//	PR_RightFullProfile = 4,
//	PR_RightHalfProfile = 5,
//};
//
//// ƽ������ת(Roll)��Χ��־
//// 3 levels
//enum RollRange
//{
//	RR_Left = 11,
//	RR_Frontal = 12,
//	RR_Right = 1,
//};
//
//// ������ת(Tilt)��Χ��־
//// 3 levels
//enum TiltRange
//{
//	TR_Up = 1,
//	TR_Forward = 2,
//	TR_Down = 3,
//};
//
////������Ϣ
//typedef struct
//{
//	int nLeft;		// �������ο����ϵ�X���
//	int nTop;		// �������ο����ϵ�Y���
//	int nWidth;		// �������ο���
//	int nHeight;	// �������ο�߶�
//
//	PanRange nPan;	//Pan��ת�Ƕ�
//	RollRange nRoll;//Roll��ת�Ƕ�
//	TiltRange nTilt;//Tilt��ת�Ƕ�
//
//	int nSide;
//
//	double lfConfidence;        // ���Ŷȣ���Χ�ڵ�+1.0֮��
//}FACEINFO;



#endif //_JFD_DEFINE_H_
