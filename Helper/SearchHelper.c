#include "SearchHelper.h"

/// <summary>
/// ����	 :	˳�����
/// ����	 :	pArrary			[in]	 Ԫ������
///			arrary_num		[in]	 Ԫ�ظ���
///			element_size	[in]	 Ԫ�ش�С
///			pFindEle		[in]	 ���ҵ�Ԫ��
///			in_pCmpFunc		[in]	 Ԫ�رȽϻص�����
/// ����ֵ:  >= 0�ɹ�
/// </summary>
int search_Sequence(void* pArrary, int Arrary_num, int Element_size, void* pFindEle, pfn_AIG_CMP_CALLBACK in_pCmpFunc)
{
	if (in_pCmpFunc == NULL || Element_size <= 0 || Arrary_num < 0)
		return -1;

	void* pTmp;
	for (int i = 0; i < Arrary_num; i++)
	{
		pTmp = (unsigned char*)pArrary + i * Element_size;
		if (in_pCmpFunc(pTmp, pFindEle, Element_size) == 0)
			return i;
	}
	return -1;
}

/// <summary>
/// ����	 :	���ֲ���
/// ����	 :	pArrary			[in]	 ˳��Ԫ������
///			arrary_num		[in]	 Ԫ�ظ���
///			element_size	[in]	 Ԫ�ش�С
///			pFindEle		[in]	 ���ҵ�Ԫ��
///			in_pCmpFunc		[in]	 Ԫ�رȽϻص�����
/// ����ֵ:  >= 0�ɹ�
/// </summary>
int search_Binary(void* pArrary, int Arrary_num, int Element_size, void* pFindEle, pfn_AIG_CMP_CALLBACK in_pCmpFunc)
{
	if (in_pCmpFunc == NULL || Element_size <= 0 || Arrary_num < 0)
		return -1;

	void* pTmp;
	int iLow = 0, iHigh = Arrary_num - 1, iMid;
	int iCheck;
	while (iLow <= iHigh)
	{
		iMid = (iLow + iHigh) / 2; //mid = low + (high - low) / 2;
		pTmp = (unsigned char*)pArrary + iMid * Element_size;
		iCheck = in_pCmpFunc(pTmp, pFindEle, Element_size);

		if (iCheck == 0)
			return iMid;
		else if (iCheck > 0)
			iHigh = iMid - 1;
		else if (iCheck < 0)
			iLow = iMid + 1;
	}
	return -1;
}

