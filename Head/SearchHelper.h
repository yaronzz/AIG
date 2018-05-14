#if !defined __AIG_SEARCH_H__
#define __AIG_SEARCH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"

/// <summary>
/// 功能	 :	顺序查找
/// 参数	 :	pArrary			[in]	 元素数组
///			arrary_num		[in]	 元素个数
///			element_size	[in]	 元素大小
///			pFindEle		[in]	 查找的元素
///			in_pCmpFunc		[in]	 元素比较回调函数
/// 返回值:  >= 0成功
/// </summary>
int search_Sequence(void* pArrary, int Arrary_num, int Element_size, void* pFindEle, pfn_AIG_CMP_CALLBACK in_pCmpFunc);

/// <summary>
/// 功能	 :	二分查找
/// 参数	 :	pArrary			[in]	 顺序元素数组
///			arrary_num		[in]	 元素个数
///			element_size	[in]	 元素大小
///			pFindEle		[in]	 查找的元素
///			in_pCmpFunc		[in]	 元素比较回调函数
/// 返回值:  >= 0成功
/// </summary>
int search_Binary(void* pArrary, int Arrary_num, int Element_size, void* pFindEle, pfn_AIG_CMP_CALLBACK in_pCmpFunc);

#ifdef __cplusplus
}
#endif

#endif  //__AIG_SEARCH_H__