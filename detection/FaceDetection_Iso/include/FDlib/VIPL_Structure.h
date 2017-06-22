#ifndef _VIPL_STRUCTURE_H_
#define _VIPL_STRUCTURE_H_

#define VIPL_EPS 0.01

//输入图像格式结构定义
//图象颜色深度，支持位真彩色和位灰度图象
enum BitsPerPixel
{
	Gray8 = 8,
	Color24 = 24,
};

//-------------------FD----------------------------------
//检测参数结构定义
// 设置深度旋转(Pan)的检测范围，缺省Level_1
// 3 levels
enum PanLevel
{
    PL_1_30_degree = 1,		// Level_1 +/-30 degree
    PL_2_60_degree = 2,		// Level_2 +/-60 degree
    PL_3_90_degree = 3,		// Level_3 +/-90 degree
};

// 设置平面内旋转(Roll)的检测范围，缺省Level_1
// 2 levels
enum RollLevel
{
    RL_1_20_degree = 1,		// Level_1 +/-20 degree
    RL_2_45_degree = 2,		// Level_2 +/-45 degree
};

// 设置俯仰旋转(Tilt)的检测范围，缺省Level_1
// 2 levels
enum TiltLevel
{
    TL_1_20_degree = 1,		// Level_1 +/-20 degree
    TL_2_40_degree = 2,		// Level_2 +/-40 degree
};

//检测函数输出人脸结构
// 深度旋转(Pan)范围标志
// 5 levels
enum PanRange
{
    PR_LeftFullProfile = 1,
    PR_LeftHalfProfile = 2,
    PR_Frontal = 3,
    PR_RightFullProfile = 4,
    PR_RightHalfProfile = 5,
};

// 平面内旋转(Roll)范围标志
// 3 levels
enum RollRange
{
    RR_Left = 11,
    RR_Frontal = 12,
    RR_Right = 1,
};

// 俯仰旋转(Tilt)范围标志
// 3 levels
enum TiltRange
{
    TR_Up = 1,
    TR_Forward = 2,
    TR_Down = 3,
};


//人脸信息
typedef struct
{
	int nLeft;		// 人脸矩形框左上点X坐标
	int nTop;		// 人脸矩形框左上点Y坐标
	int nWidth;		// 人脸矩形框宽度
	int nHeight;	// 人脸矩形框高度

	PanRange nPan;	//Pan旋转角度
	RollRange nRoll;//Roll旋转角度
	TiltRange nTilt;//Tilt旋转角度

	int nSide;

	double lfConfidence;        // 可信度，范围在到+1.0之间
}FACEINFO;


typedef struct {
	int x;
	int y;
} FD_Point;

typedef struct {
	int left;
	int top;
	int right;
	int bottom;

	int PtInRect(FD_Point point) {
		if ((point.x >= left) && (point.x < right) && (point.y >= top) && (point.y < bottom)) {
			return 1;
		}
		return 0;
	};
	int Width() {return right - left;};
	int Height() {return bottom - top;};
} FD_Rect;

//--------------------------FLL-----------------------------------


typedef struct {
    double x;
    double y;
} CPnt;

// ------   FID  ------------
enum VIPLAFRAlgTYPE
{
	GELCAFR = 1
};

class VIPLPoint
{
public:
	long x;
	long y;
	VIPLPoint(long p_x, long p_y)
	{
		x = p_x;
		y = p_y;
	}
	VIPLPoint()
	{
	}
};


#endif
