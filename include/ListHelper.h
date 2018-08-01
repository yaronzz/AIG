#if !defined __AIG_LIST_H__
#define __AIG_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"


/// <summary>
/// 功能	 :	新建链表
/// 参数	 :	iRecordLen		[in] 节点数据长度
///			pCmpFunc		[in] 查找时的比较函数
/// 返回值: 
/// </summary> 
void* list_Creat(int iRecordLen, pfn_AIG_CMP_CALLBACK pCmpFunc);

/// <summary>
/// 功能	 :	销毁链表
/// 参数	 :	pHandle			[in] 句柄
/// 返回值: 
/// </summary> 
void list_Destroy(void** pHandle);

/// <summary>
/// 功能	 :	添加节点
/// 参数	 :	pHandle			[in] 句柄
///			pRecord			[in] 节点数据
/// 返回值: 
/// </summary> 
int list_Add(void* pHandle, void* pRecord);

/// <summary>
/// 功能	 :	插入节点
/// 参数	 :	pHandle			[in] 句柄
///			pRecord			[in] 节点数据
///			iIndex			[in] 节点下标
/// 返回值: 
/// </summary> 
int list_Insert(void* pHandle, void* pRecord, int iIndex);





/// <summary>
/// 功能	 :	删除节点
/// 参数	 :	pHandle			[in] 句柄
///			iIndex			[in] 节点下标
/// 返回值: 
/// </summary> 
int list_Remove(void* pHandle, int iIndex);

/// <summary>
/// 功能	 :	删除全部节点
/// 参数	 :	pHandle			[in] 句柄
/// 返回值: 
/// </summary> 
int list_RemoveAll(void* pHandle);




/// <summary>
/// 功能	 :	获取节点数量
/// 参数	 :	pHandle			[in] 句柄
/// 返回值: 
/// </summary> 
int list_GetSize(void* pHandle);

/// <summary>
/// 功能	 :	获取节点数据
/// 参数	 :	pHandle			[in] 句柄
///			iIndex			[in] 节点下标
/// 返回值: 
/// </summary> 
void* list_GetAt(void* pHandle, int iIndex);

/// <summary>
/// 功能	 :	查找节点下标
/// 参数	 :	pHandle			[in] 句柄
///			pFind			[in] 查找的节点
///			iOrder			[in] 第几个匹配的节点
/// 返回值: 
/// </summary> 
int list_Find(void* pHandle, void* pFind, int iOrder);



#ifdef __cplusplus
}
#endif

#endif  //__AIG_LIST_H__