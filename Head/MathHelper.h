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
#define AIG_MATH_FLOAT_EQUAL(A, B)			 ((AIG_MATH_ABS(A - B) < FLOAT_EQUAL_LIMIT) ? AIG_TRUE : AIG_FALSE)
#define AIG_MATH_POINT_EQUAL(AX, AY, BX, BY) (((AIG_MATH_FLOAT_EQUAL(AX, BX) && AIG_MATH_FLOAT_EQUAL(AY, BY)) ?  AIG_TRUE : AIG_FALSE)

typedef struct _AigCoords
{
	double x;
	double y;
}AigCoords;

typedef struct _AigRect
{
	double left;
	double top;
	double right;
	double bottom;
}AigRect;

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


#ifdef __cplusplus
}
#endif

#endif  //__AIG_MATH_H__