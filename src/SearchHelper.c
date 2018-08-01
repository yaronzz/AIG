#include "SearchHelper.h"

/// <summary>
/// 功能	 :	顺序查找
/// 参数	 :	pArrary			[in]	 元素数组
///			arrary_num		[in]	 元素个数
///			element_size	[in]	 元素大小
///			pFindEle		[in]	 查找的元素
///			in_pCmpFunc		[in]	 元素比较回调函数
/// 返回值:  >= 0成功
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
/// 功能	 :	二分查找
/// 参数	 :	pArrary			[in]	 顺序元素数组
///			arrary_num		[in]	 元素个数
///			element_size	[in]	 元素大小
///			pFindEle		[in]	 查找的元素
///			in_pCmpFunc		[in]	 元素比较回调函数
/// 返回值:  >= 0成功
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

