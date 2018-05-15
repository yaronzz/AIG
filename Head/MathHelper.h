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


#ifdef __cplusplus
}
#endif

#endif  //__AIG_MATH_H__