#include "MathHelper.h"

/// <summary>
/// ����	 :	�鿴�Ƿ�Ϊ���ģʽ
/// ����ֵ: 
/// </summary>
int math_IsBigEndian()
{
	//	���BigEndian��   ��Ϊ��һ���ֽ������λ�ֽڣ����մӵ͵�ַ���ߵ�ַ��˳�������ݵĸ�λ�ֽڵ���λ�ֽڣ�
	//	С��LittleEndian������Ϊ��һ���ֽ������λ�ֽڣ����մӵ͵�ַ���ߵ�ַ��˳�������ݵĵ�λ�ֽڵ���λ�ֽڣ�
	//  x86 ϵ��CPU ����littleEndian ���ֽ���PowerPC ͨ����BigEndian�����е�CPU ��ͨ������������CPU ������Little endian ����Big endian ģʽ��
	//  �жϷ���������һ��int��Ϊ1��ȡ��һ���ֽڣ������1��ΪС��
	unsigned int iNum = 0xff;
	unsigned char* pTmp = (unsigned char*)&iNum;
	if (*pTmp == 0xff)
		return AIG_FALSE;

	return AIG_TRUE;
}

/// <summary>
/// ����	 :	��ȡ���ֽڶ���ĳ���
/// ����	 :	iSize			[in] ԭʼ����
/// ����ֵ: 
/// </summary>
int math_Get4ByteAlignSize(int iSize)
{
	//	���ֽڶ���ı�Ҫ�����ǣ�		1��ֻ�ܲ��벻�ܼ��٣�����δ����֮ǰ�ĳ���Ϊ1�������ֻ����4������0
	//							2���ж��ֽڶ���������Ƕ�4���࣬���Ϊ0���Ƕ���
	//	((in_Size + 3) >> 2) << 2 ������֮�󣬱�ֻ֤�ܱ������������١����Ƴ���4����������Ķ�û�ˣ������Ƴ���4�������
	return iSize < 0 ? 0 : ((iSize + 3) >> 2) << 2;  //����(in_Size + 3 & ~3)
}

/// <summary>
/// ����	 :	��1��ת��Ϊ������λ
/// ����	 :	eUnit		[in] ��λ
/// ����ֵ: 
/// </summary>
double math_MetersToUnits(enumAigLenghtUnit eUnit)
{
	switch (eUnit)
	{
	case eALUnit_km:		//ǧ��
		return 0.001;
	case eALUnit_m:			//��
		return 1;
	case eALUnit_dm:		//����
		return 10;
	case eALUnit_cm:		//����
		return 100;
	case eALUnit_mm:		//����
		return 1000;
	case eALUnit_um:		//΢��
		return 1000 * 1000;
	case eALUnit_nm:		//����
		return 1000 * 1000 * 1000;

	case eALUnit_mi:		//Ӣ��
		return 0.0006214;
	case eALUnit_ft:		//Ӣ��
		return 3.2808399;
	case eALUnit_in:		//Ӣ��
		return 39.3700787;

	case eALUnit_nmi:		//����
		return 0.00054;
	case eALUnit_yd:		//��
		return 1.0936133;

	case eALUnit_L:			//��
		return 0.002;
	case eALUnit_Z:			//��
		return 0.3;
	case eALUnit_CHI:		//��
		return 3;
	case eALUnit_CUN:		//��
		return 30;
	case eALUnit_FEN:		//��
		return 300;
	case eALUnit_LI:		//��
		return 3000;
	case eALUnit_HAO:		//��
		return 30000;
	}
	return 0;
}