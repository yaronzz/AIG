#if !defined __AIG_MATH_H__
#define __AIG_MATH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"

#define PI									 3.14159265359
#define FLOAT_EQUAL_LIMIT					 0.0000001f	

//�����ֵ\���ֵ\��Сֵ
#define AIG_MATH_ABS(value)			         ((value) > 0 ? (value) : -(value))
#define AIG_MATH_MAX(A, B)					 (A > B ? A : B)
#define AIG_MATH_MIN(A, B)					 (A > B ? B : A)

//�󸡵���\������Ƿ���ͬ
#define AIG_MATH_FLOAT_EQUAL(A, B)			 (AIG_MATH_ABS(A - B) < FLOAT_EQUAL_LIMIT)
#define AIG_MATH_POINT_EQUAL(AX, AY, BX, BY) (AIG_MATH_FLOAT_EQUAL(AX, BX) && AIG_MATH_FLOAT_EQUAL(AY, BY))

//2ά����
typedef struct _AigCoords
{
	double x;
	double y;
}AigCoords;

//�߿�
typedef struct _AigRect
{
	double left;
	double top;
	double right;
	double bottom;
}AigRect;

//���Է���
typedef struct _AigEquation
{
	double A;
	double B;
	double C;
}AigEquation;

typedef enum _enumAigLenghtUnit
{
	eALUnit_km,		//ǧ��
	eALUnit_m,		//��
	eALUnit_dm,		//����
	eALUnit_cm,		//����
	eALUnit_mm,		//����
	eALUnit_um,		//΢��
	eALUnit_nm,		//����

	eALUnit_mi,		//Ӣ��
	eALUnit_ft,		//Ӣ��
	eALUnit_in,		//Ӣ��

	eALUnit_nmi,	//����
	eALUnit_yd,		//��

	eALUnit_L,		//��
	eALUnit_Z,		//��
	eALUnit_CHI,	//��
	eALUnit_CUN,	//��
	eALUnit_FEN,	//��
	eALUnit_LI,		//��
	eALUnit_HAO,	//��

}enumAigLenghtUnit;


/// <summary>
/// ����	 :	�鿴�Ƿ�Ϊ���ģʽ
/// ����ֵ: 
/// </summary>
int math_IsBigEndian();

/// <summary>
/// ����	 :	��ȡ���ֽڶ���ĳ���
/// ����	 :	iSize			[in] ԭʼ����
/// ����ֵ: 
/// </summary>
int math_Get4ByteAlignSize(int iSize);

/// <summary>
/// ����	 :	��1��ת��Ϊ������λ
/// ����	 :	eUnit			[in] ��λ
/// ����ֵ: 
/// </summary>
double math_MetersToUnits(enumAigLenghtUnit eUnit);

/// <summary>
/// ����	 :	������
/// ����	 :	dValue		[in] ֵ
/// ����ֵ:  
/// </summary>
double math_Sqrt(double dValue);




/// <summary>
/// ����	 :	ʮ������תʮ����
/// ����	 :	pChar		[in] ֵ
/// ����ֵ:  
/// </summary>
int math_HexToDec(char pChar);

/// <summary>
/// ����	 :	ʮ����תʮ������
/// ����	 :	pInt		[in] ֵ
/// ����ֵ:  
/// </summary>
char math_DecToHex(short int pInt);





/// <summary>
/// ����	 :	��ȡֱ�ߵ�һ�㷽��
/// ����	 :	point0		[in] ��һ���������
///			point1		[in] �ڶ����������
///			pEquation	[out]ֱ�߷���
/// ����ֵ:  
/// </summary>
int math_GetLinearEquation(AigCoords point0, AigCoords point1, AigEquation* pEquation);





/// <summary>
/// ����	 :	��ȡ����֮��ľ���
/// ����	 :	point0		[in] ��һ���������
///			point1		[in] �ڶ����������
/// ����ֵ:  
/// </summary>
double math_GetTwoPointsDistance(AigCoords point0, AigCoords point1);

/// <summary>
/// ����	 :	��ȡ�㵽�ߵľ���
/// ����	 :	point			[in] �������
///			line_point0		[in] ��һ���ߵ�����
///			line_point1		[in] �ڶ����ߵ�����
/// ����ֵ:  
/// </summary>
double math_GetPointToLineDistance(AigCoords point, AigCoords line_point0, AigCoords line_point1);




/// <summary>
/// ����	 :	��ȡ����X��ĽǶ�
/// ����	 :	start_point		[in] ��һ���ߵ�����
///			end_point		[in] �ڶ����ߵ�����
/// ����ֵ:  
/// </summary>
double math_GetLineToXAxisAngle(AigCoords start_point, AigCoords end_point);

/// <summary>
/// ����	 :	�жϵ����ߵ���һ��
/// ����	 :	point			[in] �������
///			start_point		[in] ��һ���ߵ�����
///			end_point		[in] �ڶ����ߵ�����
/// ����ֵ:  0��ʾ 1��� 2�Ҳ� -1����
/// </summary> 
int math_GetPointSideToLine(AigCoords point, AigCoords start_point, AigCoords end_point);

/// <summary>
/// ����	 :	��㵽ֱ�ߵĴ����
/// ����	 :	point			[in] �������
///			start_point		[in] ��һ���ߵ�����
///			end_point		[in] �ڶ����ߵ�����
///			out_point		[out]����
/// ����ֵ:  
/// </summary> 
int math_GetVerticalPoint(AigCoords point, AigCoords start_point, AigCoords end_point, AigCoords* out_point);





/// <summary>
/// ����	 :	�жϵ��Ƿ��ھ��ο���
/// ����	 :	point			[in] �������
///			rect			[in] ���ο�
///			isIncBoundary	[in] �Ƿ�����߽�(1��-�����ڿ�߽�Ҳ��������,0��)
/// ����ֵ:  
/// </summary> 
int math_PointInRect(AigCoords point, AigRect rect, int isIncBoundary);

/// <summary>
/// ����	 :	�жϾ��ο��Ƿ��ཻ(���������Ҳ�����ཻ)
/// ����	 :	rect0			[in] ���ο�
///			rect1			[in] ���ο�
/// ����ֵ:  
/// </summary> 
int math_IsRectIntersect(AigRect* in_Rect0, AigRect* in_Rect1);

#ifdef __cplusplus
}
#endif

#endif  //__AIG_MATH_H__