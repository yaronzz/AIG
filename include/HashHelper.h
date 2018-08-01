#if !defined __AIG_HASH_H__
#define __AIG_HASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"

typedef int(*pfn_AIG_HASH_CALCHASH_CALLBACK)(void* pKey, int iKeyLen);		//计算哈希值

/// <summary>
/// 功能	 :	创建哈希表
/// 参数	 :	iKeyLen				[in] 关键字长度
///			iValueLen			[in] 值长度
///			iHashCapacity		[in] 容量
///			pCmpFunc			[in] Key比较函数
///			pCalcHashFunc		[in] 计算哈希值
/// 返回值: 
/// </summary> 
void* hash_Creat(int iKeyLen, int iValueLen, int iHashCapacity, pfn_AIG_CMP_CALLBACK pCmpFunc, pfn_AIG_HASH_CALCHASH_CALLBACK pCalcHashFunc);

/// <summary>
/// 功能	 :	销毁哈希表
/// 参数	 :	pHandle				[in-out] 句柄
/// 返回值: 
/// </summary> 
void hash_Destroy(void** pHandle);

/// <summary>
/// 功能	 :	插入节点
/// 参数	 :	pHandle				[in] 句柄
///			pKey				[in] 关键字
///			pValue				[in] 值
///			bIsReplace			[in] 如果已存在是否替换
/// 返回值: 
/// </summary> 
int hash_Insert(void* pHandle, void* pKey, void* pValue, int bIsReplace);

/// <summary>
/// 功能	 :	移除节点
/// 参数	 :	pHandle				[in] 句柄
///			pKey				[in] 关键字
/// 返回值: 
/// </summary> 
int hash_Remove(void* pHandle, void* pKey);

/// <summary>
/// 功能	 :	移除全部节点
/// 参数	 :	pHandle				[in] 句柄
/// 返回值: 
/// </summary> 
int hash_RemoveAll(void* pHandle);

/// <summary>
/// 功能	 :	获取当前节点的数量
/// 参数	 :	pHandle				[in]  句柄
/// 返回值: 
/// </summary> 
int hash_GetSize(void* pHandle);

/// <summary>
/// 功能	 :	遍历前重置
/// 参数	 :	pHandle				[in]  句柄
/// 返回值: 
/// </summary> 
int hash_SetOut(void* pHandle);

/// <summary>
/// 功能	 :	遍历下一个
/// 参数	 :	pHandle				[in]  句柄
///			out_pKey			[out] 关键字
///			out_pValue			[out] 值
/// 返回值: 
/// </summary> 
int hash_GetNext(void* pHandle, void** out_pKey, void** out_pValue);

/// <summary>
/// 功能	 :	查找
/// 参数	 :	pHandle				[in] 句柄
///			pKey				[in] 关键字
/// 返回值: 
/// </summary> 
void* hash_Find(void* pHandle, void* pKey);












#ifdef __cplusplus
}
#endif

#endif  //__AIG_HASH_H__