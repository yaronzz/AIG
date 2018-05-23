#if !defined __AIG_MATH_H__
#define __AIG_MATH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"

#define PI									 3.14159265359
#define FLOAT_EQUAL_LIMIT					 0.0000001f	

//求绝对值\最大值\最小值
#define AIG_MATH_ABS(value)			         ((value) > 0 ? (value) : -(value))
#define AIG_MATH_MAX(A, B)					 (A > B ? A : B)
#define AIG_MATH_MIN(A, B)					 (A > B ? B : A)

//求浮点数\坐标点是否相同
#define AIG_MATH_FLOAT_EQUAL(A, B)			 (AIG_MATH_ABS(A - B) < FLOAT_EQUAL_LIMIT)
#define AIG_MATH_POINT_EQUAL(AX, AY, BX, BY) (AIG_MATH_FLOAT_EQUAL(AX, BX) && AIG_MATH_FLOAT_EQUAL(AY, BY))

//2维坐标
typedef struct _AigCoords
{
	double x;
	double y;
}AigCoords;

//边框
typedef struct _AigRect
{
	double left;
	double top;
	double right;
	double bottom;
}AigRect;

//线性方程
typedef struct _AigEquation
{
	double A;
	double B;
	double C;
}AigEquation;

typedef enum _enumAigLenghtUnit
{
	eALUnit_km,		//千米
	eALUnit_m,		//米
	eALUnit_dm,		//分米
	eALUnit_cm,		//厘米
	eALUnit_mm,		//毫米
	eALUnit_um,		//微米
	eALUnit_nm,		//奈米

	eALUnit_mi,		//英里
	eALUnit_ft,		//英尺
	eALUnit_in,		//英寸

	eALUnit_nmi,	//海里
	eALUnit_yd,		//码

	eALUnit_L,		//里
	eALUnit_Z,		//丈
	eALUnit_CHI,	//尺
	eALUnit_CUN,	//寸
	eALUnit_FEN,	//分
	eALUnit_LI,		//厘
	eALUnit_HAO,	//毫

}enumAigLenghtUnit;


/// <summary>
/// 功能	 :	查看是否为大端模式
/// 返回值: 
/// </summary>
int math_IsBigEndian();

/// <summary>
/// 功能	 :	获取四字节对齐的长度
/// 参数	 :	iSize			[in] 原始长度
/// 返回值: 
/// </summary>
int math_Get4ByteAlignSize(int iSize);

/// <summary>
/// 功能	 :	将1米转换为其他单位
/// 参数	 :	eUnit			[in] 单位
/// 返回值: 
/// </summary>
double math_MetersToUnits(enumAigLenghtUnit eUnit);

/// <summary>
/// 功能	 :	开根号
/// 参数	 :	dValue		[in] 值
/// 返回值:  
/// </summary>
double math_Sqrt(double dValue);




/// <summary>
/// 功能	 :	十六进制转十进制
/// 参数	 :	pChar		[in] 值
/// 返回值:  
/// </summary>
int math_HexToDec(char pChar);

/// <summary>
/// 功能	 :	十进制转十六进制
/// 参数	 :	pInt		[in] 值
/// 返回值:  
/// </summary>
char math_DecToHex(short int pInt);





/// <summary>
/// 功能	 :	获取直线的一般方程
/// 参数	 :	point0		[in] 第一个点的坐标
///			point1		[in] 第二个点的坐标
///			pEquation	[out]直线方程
/// 返回值:  
/// </summary>
int math_GetLinearEquation(AigCoords point0, AigCoords point1, AigEquation* pEquation);





/// <summary>
/// 功能	 :	获取两点之间的距离
/// 参数	 :	point0		[in] 第一个点的坐标
///			point1		[in] 第二个点的坐标
/// 返回值:  
/// </summary>
double math_GetTwoPointsDistance(AigCoords point0, AigCoords point1);

/// <summary>
/// 功能	 :	获取点到线的距离
/// 参数	 :	point			[in] 点的坐标
///			line_point0		[in] 第一个线的坐标
///			line_point1		[in] 第二个线的坐标
/// 返回值:  
/// </summary>
double math_GetPointToLineDistance(AigCoords point, AigCoords line_point0, AigCoords line_point1);




/// <summary>
/// 功能	 :	获取线与X轴的角度
/// 参数	 :	start_point		[in] 第一个线的坐标
///			end_point		[in] 第二个线的坐标
/// 返回值:  
/// </summary>
double math_GetLineToXAxisAngle(AigCoords start_point, AigCoords end_point);

/// <summary>
/// 功能	 :	判断点在线的哪一侧
/// 参数	 :	point			[in] 点的坐标
///			start_point		[in] 第一个线的坐标
///			end_point		[in] 第二个线的坐标
/// 返回值:  0显示 1左侧 2右侧 -1错误
/// </summary> 
int math_GetPointSideToLine(AigCoords point, AigCoords start_point, AigCoords end_point);

/// <summary>
/// 功能	 :	求点到直线的垂足点
/// 参数	 :	point			[in] 点的坐标
///			start_point		[in] 第一个线的坐标
///			end_point		[in] 第二个线的坐标
///			out_point		[out]垂足
/// 返回值:  
/// </summary> 
int math_GetVerticalPoint(AigCoords point, AigCoords start_point, AigCoords end_point, AigCoords* out_point);





/// <summary>
/// 功能	 :	判断点是否在矩形框内
/// 参数	 :	point			[in] 点的坐标
///			rect			[in] 矩形框
///			isIncBoundary	[in] 是否包括边界(1是-点落在框边界也算在其内,0否)
/// 返回值:  
/// </summary> 
int math_PointInRect(AigCoords point, AigRect rect, int isIncBoundary);

/// <summary>
/// 功能	 :	判断矩形框是否相交(包含的情况也当作相交)
/// 参数	 :	rect0			[in] 矩形框
///			rect1			[in] 矩形框
/// 返回值:  
/// </summary> 
int math_IsRectIntersect(AigRect* in_Rect0, AigRect* in_Rect1);

#ifdef __cplusplus
}
#endif

#endif  //__AIG_MATH_H__