#if !defined __AIG_SORT_H__
#define __AIG_SORT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"


/// <summary>
/// 功能	 :	冒泡排序(从小到大)
/// 参数	 :	pArrary			[in-out] 元素数组
///			arrary_num		[in]	 元素个数
///			element_size	[in]	 元素大小
///			in_pCmpFunc		[in]	 元素比较回调函数
/// 返回值: 
/// </summary>
int sort_Bubble(void* pArrary, int Arrary_num, int Element_size, pfn_AIG_CMP_CALLBACK in_pCmpFunc);

/// <summary>
/// 功能	 :	插入排序(从小到大)
/// 参数	 :	pArrary			[in-out] 元素数组
///			arrary_num		[in]	 元素个数
///			element_size	[in]	 元素大小
///			in_pCmpFunc		[in]	 元素比较回调函数
/// 返回值: 
/// </summary>
int sort_Insertion(void* pArrary, int Arrary_num, int Element_size, pfn_AIG_CMP_CALLBACK in_pCmpFunc);
       
/// <summary>
/// 功能	 :	二分插入排序(从小到大)
/// 参数	 :	pArrary			[in-out] 元素数组
///			arrary_num		[in]	 元素个数
///			element_size	[in]	 元素大小
///			in_pCmpFunc		[in]	 元素比较回调函数
/// 返回值: 
/// </summary>
int sort_BinaryInsertion(void* pArrary, int Arrary_num, int Element_size, pfn_AIG_CMP_CALLBACK in_pCmpFunc);

/// <summary>
/// 功能	 :	希尔排序(从小到大)
/// 参数	 :	pArrary			[in-out] 元素数组
///			arrary_num		[in]	 元素个数
///			element_size	[in]	 元素大小
///			in_pCmpFunc		[in]	 元素比较回调函数
/// 返回值: 
/// </summary>
int sort_Shell(void* pArrary, int Arrary_num, int Element_size, pfn_AIG_CMP_CALLBACK in_pCmpFunc);
#ifdef __cplusplus
}
#endif

#endif  //__AIG_SORT_H__