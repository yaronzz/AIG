#include "SortHelper.h"

/// <summary>
/// ����	 :	ð������(��С����)
/// ����	 :	pArrary			[in-out] Ԫ������
///			arrary_num		[in]	 Ԫ�ظ���
///			element_size	[in]	 Ԫ�ش�С
///			in_pCmpFunc		[in]	 Ԫ�رȽϻص�����
/// ����ֵ: 
/// </summary>
int sort_Bubble(void* pArrary, int Arrary_num, int Element_size, pfn_AIG_CMP_CALLBACK in_pCmpFunc)
{
	if (in_pCmpFunc == NULL || Element_size <= 0 || Arrary_num < 0)
		return eAEC_Input;
	
	unsigned char* pEleA, *pEleB;
	for (int j = 0; j < Arrary_num - 1; j++)
	{
		for (int i = 0; i < Arrary_num - 1 - j; i++)
		{
			pEleA = (unsigned char*)pArrary + i*Element_size;
			pEleB = (unsigned char*)pArrary + (i + 1)*Element_size;
			if (in_pCmpFunc(pEleA, pEleB, Element_size) > 0)
				string_MemorySwap(pEleA, pEleB, Element_size);
		}
	}
	return eAEC_Success;
}

/// <summary>
/// ����	 :	��������(��С����)
/// ����	 :	pArrary			[in-out] Ԫ������
///			arrary_num		[in]	 Ԫ�ظ���
///			element_size	[in]	 Ԫ�ش�С
///			in_pCmpFunc		[in]	 Ԫ�رȽϻص�����
/// ����ֵ: 
/// </summary>
int sort_Insertion(void* pArrary, int Arrary_num, int Element_size, pfn_AIG_CMP_CALLBACK in_pCmpFunc)
{
	if (in_pCmpFunc == NULL || Element_size <= 0 || Arrary_num < 0)
		return eAEC_Input;

	int i, j;
	unsigned char* pEleA;
	unsigned char* pEleB;

	for (i = 1; i < Arrary_num; i++)
	{
		//��ߵĻ�����жԱ�����
		for (j = i - 1; j >= 0; j--)
		{
			pEleA = (unsigned char*)pArrary + (j + 1) * Element_size;
			pEleB = (unsigned char*)pArrary + j * Element_size;
			if (in_pCmpFunc(pEleA, pEleB, Element_size) > 0)
				break;

			string_MemorySwap(pEleA, pEleB, Element_size);
		}
	}
	return eAEC_Success;
}

/// <summary>
/// ����	 :	���ֲ�������(��С����)
/// ����	 :	pArrary			[in-out] Ԫ������
///			arrary_num		[in]	 Ԫ�ظ���
///			element_size	[in]	 Ԫ�ش�С
///			in_pCmpFunc		[in]	 Ԫ�رȽϻص�����
/// ����ֵ: 
/// </summary>
int sort_BinaryInsertion(void* pArrary, int Arrary_num, int Element_size, pfn_AIG_CMP_CALLBACK in_pCmpFunc)
{
	if (in_pCmpFunc == NULL || Element_size <= 0 || Arrary_num < 0)
		return eAEC_Input;

	int i, j;
	int iLow, iHigh, iMid;
	unsigned char* pEleA;
	unsigned char* pEleB;

	for (i = 1; i < Arrary_num; i++)
	{
		pEleA = (unsigned char*)pArrary + i * Element_size;

		//���ַ����Ҳ����λ��(��ʡ�˱ȽϵĴ���)
		for (iLow = 0, iHigh = i - 1; iLow <= iHigh;)
		{
			iMid = (iLow + iHigh) / 2;
			pEleB = (unsigned char*)pArrary + iMid * Element_size;
			if (in_pCmpFunc(pEleA, pEleB, Element_size) > 0)
				iLow = iMid + 1;
			else
				iHigh = iMid - 1;
		}

		//��������
		for (j = i - 1; j >= iHigh + 1; j--)
		{
			pEleA = (unsigned char*)pArrary + (j + 1) * Element_size;
			pEleB = (unsigned char*)pArrary + j * Element_size;
			string_MemorySwap(pEleA, pEleB, Element_size);
		}
	}

	return eAEC_Success;
}

/// <summary>
/// ����	 :	ϣ������(��С����)
/// ����	 :	pArrary			[in-out] Ԫ������
///			arrary_num		[in]	 Ԫ�ظ���
///			element_size	[in]	 Ԫ�ش�С
///			in_pCmpFunc		[in]	 Ԫ�رȽϻص�����
/// ����ֵ: 
/// </summary>
int sort_Shell(void* pArrary, int Arrary_num, int Element_size, pfn_AIG_CMP_CALLBACK in_pCmpFunc)
{
	if (in_pCmpFunc == NULL || Element_size <= 0 || Arrary_num < 0)
		return eAEC_Input;

	int i, j;
	int iField;
	unsigned char* pEleA;
	unsigned char* pEleB;

	//�����������
	for (iField = Arrary_num / 2; iField > 0; iField /= 2)
	{
		for (i = iField; i < Arrary_num; i++)
		{
			for (j = i - iField; j >= 0; j -= iField)
			{
				pEleA = (unsigned char*)pArrary + j * Element_size;
				pEleB = (unsigned char*)pArrary + (j + iField) * Element_size;
				if (in_pCmpFunc(pEleA, pEleB, Element_size) <= 0)
					break;

				string_MemorySwap(pEleA, pEleB, Element_size);
			}
		}
	}
	return 0;
}
