#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <time.h>
#include <io.h>
#include <direct.h>
#endif

#if defined(__linux) || defined(linux) || defined(__LYNX)
#include <unistd.h>
#include <dirent.h>
#include <stdarg.h>
#include <time.h>
#include <strings.h>
#include <sys/stat.h>
#endif

#include "ListHelper.h"

//链表节点
typedef struct _AigListNode
{
	void* pData;					//节点数据
	struct _AigListNode* pNext;		//下一个节点
}AigListNode;

typedef struct _AigListHandle
{
	int Size;						//节点数量
	int RecordLen;					//节点数据长度
	AigListNode* pEntry;			//节点入口
	pfn_AIG_CMP_CALLBACK pCmpFunc;	//节点比较函数
}AigListHandle;

/// <summary>
/// 功能	 :	新建节点
/// 参数	 :	pHandle			[in] 句柄
///			pRecord			[in] 节点数据
/// 返回值: 
/// </summary> 
static AigListNode* list_CreatNode(AigListHandle* pHandle, void* pRecord)
{
	AigListNode* pNode	= (AigListNode*)AIG_FUNC_MALLOC(sizeof(AigListNode));
	pNode->pNext		= NULL;
	pNode->pData		= AIG_FUNC_MALLOC(pHandle->RecordLen);
	memcpy(pNode->pData, pRecord, pHandle->RecordLen);

	return pNode;
}

/// <summary>
/// 功能	 :	删除节点
/// 参数	 :	pNode			[in] 节点
/// 返回值: 
/// </summary> 
static void list_DelNode(AigListNode* pNode)
{
	AIG_FUNC_FREE(pNode->pData);
	AIG_FUNC_FREE(pNode);
}

/// <summary>
/// 功能	 :	新建链表
/// 参数	 :	iRecordLen		[in] 节点数据长度
///			pCmpFunc		[in] 查找时的比较函数
/// 返回值: 
/// </summary> 
void* list_Creat(int iRecordLen, pfn_AIG_CMP_CALLBACK pCmpFunc)
{
	if (iRecordLen <= 0)
		return NULL;

	AigListHandle* pHandle	= (AigListHandle*)AIG_FUNC_MALLOC(sizeof(AigListHandle));
	memset(pHandle, 0, sizeof(AigListHandle));

	pHandle->pCmpFunc		= pCmpFunc;
	pHandle->RecordLen		= iRecordLen;
	return pHandle;
}

/// <summary>
/// 功能	 :	销毁链表
/// 参数	 :	pHandle			[in] 句柄
/// 返回值: 
/// </summary> 
void list_Destroy(void** pHandle)
{
	if (pHandle == NULL || *pHandle == NULL)
		return;

	list_RemoveAll(*pHandle);
	AIG_FUNC_FREE(*pHandle);

	*pHandle = NULL;
}


/// <summary>
/// 功能	 :	添加节点
/// 参数	 :	pHandle			[in] 句柄
///			pRecord			[in] 节点数据
/// 返回值: 
/// </summary> 
int list_Add(void* pHandle, void* pRecord)
{
	if (pHandle == NULL || pRecord == NULL)
		return eAEC_Input;

	AigListHandle* pListHandle	= (AigListHandle*)pHandle;
	AigListNode* pNewNode		= list_CreatNode(pListHandle, pRecord);

	if (pListHandle->Size == 0)
		pListHandle->pEntry	= pNewNode;
	else
	{
		AigListNode* pTemp = pListHandle->pEntry;
		for (int i = 0; i < pListHandle->Size - 1; i++)
			pTemp = pTemp->pNext;
	
		pTemp->pNext = pNewNode;
	}

	pListHandle->Size++;
	return eAEC_Success;
}

/// <summary>
/// 功能	 :	插入节点
/// 参数	 :	pHandle			[in] 句柄
///			pRecord			[in] 节点数据
///			iIndex			[in] 节点下标
/// 返回值: 
/// </summary> 
int list_Insert(void* pHandle, void* pRecord, int iIndex)
{
	if (pHandle == NULL || pRecord == NULL || iIndex < 0)
		return eAEC_Input;

	AigListHandle* pListHandle	= (AigListHandle*)pHandle;
	AigListNode* pNewNode		= list_CreatNode(pListHandle, pRecord);

	if (pListHandle->Size == 0)
		pListHandle->pEntry = pNewNode;
	else if (iIndex == 0)
	{
		pNewNode->pNext		= pListHandle->pEntry;
		pListHandle->pEntry = pNewNode;
	}
	else
	{
		AigListNode* pPreNode		= pListHandle->pEntry;
		AigListNode* pInsertNode	= pListHandle->pEntry->pNext;
		for (int i = 0; i < pListHandle->Size - 1 && i < iIndex - 1; i++)
		{
			pPreNode	= pPreNode->pNext;
			pInsertNode = pInsertNode->pNext;
		}

		pNewNode->pNext = pInsertNode;
		pPreNode->pNext = pNewNode;
	}

	pListHandle->Size++;
	return eAEC_Success;
}

/// <summary>
/// 功能	 :	删除节点
/// 参数	 :	pHandle			[in] 句柄
///			iIndex			[in] 节点下标
/// 返回值: 
/// </summary> 
int list_Remove(void* pHandle, int iIndex)
{
	if (pHandle == NULL || iIndex < 0)
		return eAEC_Input;

	AigListHandle* pListHandle = (AigListHandle*)pHandle;
	if (pListHandle->Size <= iIndex || pListHandle->Size == 0)
		return eAEC_IndexOver;

	AigListNode* pPreNode = pListHandle->pEntry;
	AigListNode* pFreeNode = pListHandle->pEntry;
	if (iIndex == 0)
		pListHandle->pEntry  = pListHandle->pEntry->pNext;
	else
	{
		pFreeNode = pFreeNode->pNext;
		for (int i = 0; i < iIndex - 1; i++)
		{
			pPreNode = pPreNode->pNext;
			pFreeNode = pFreeNode->pNext;
		}

		pPreNode->pNext = pFreeNode->pNext;
	}

	list_DelNode(pFreeNode);
	pListHandle->Size--;
	return eAEC_Success;
}

/// <summary>
/// 功能	 :	删除全部节点
/// 参数	 :	pHandle			[in] 句柄
/// 返回值: 
/// </summary> 
int list_RemoveAll(void* pHandle)
{
	if (pHandle == NULL)
		return eAEC_Input;

	AigListHandle* pListHandle = (AigListHandle*)pHandle;
	AigListNode* pNext;
	AigListNode* pFreeNode = pListHandle->pEntry;
	for (int i = 0; i < pListHandle->Size; i++)
	{
		pNext = pFreeNode->pNext;
		list_DelNode(pFreeNode);
	}

	pListHandle->Size = 0;
	return eAEC_Success;
}

/// <summary>
/// 功能	 :	获取节点数量
/// 参数	 :	pHandle			[in] 句柄
/// 返回值: 
/// </summary> 
int list_GetSize(void* pHandle)
{
	if (pHandle == NULL)
		return -1;

	AigListHandle* pListHandle = (AigListHandle*)pHandle;
	return pListHandle->Size;
}

/// <summary>
/// 功能	 :	获取节点数据
/// 参数	 :	pHandle			[in] 句柄
///			iIndex			[in] 节点下标
/// 返回值: 
/// </summary> 
void* list_GetAt(void* pHandle, int iIndex)
{
	if (pHandle == NULL)
		return NULL;

	AigListHandle* pListHandle = (AigListHandle*)pHandle;
	if (pListHandle->Size <= iIndex || pListHandle->Size == 0)
		return NULL;

	AigListNode* pNode = pListHandle->pEntry;
	for (int i = 0; i < iIndex; i++)
		pNode = pNode->pNext;

	return pNode->pData;
}

/// <summary>
/// 功能	 :	查找节点下标
/// 参数	 :	pHandle			[in] 句柄
///			pFind			[in] 查找的节点
///			iOrder			[in] 第几个匹配的节点
/// 返回值: 
/// </summary> 
int list_Find(void* pHandle, void* pFind, int iOrder)
{
	if (pHandle == NULL)
		return -1;

	AigListHandle* pListHandle = (AigListHandle*)pHandle;
	if (pListHandle->Size == 0 || pListHandle->pCmpFunc == NULL)
		return -1;

	int iFindOrder = 0;
	AigListNode* pNode = pListHandle->pEntry;
	for (int i = 0; i < pListHandle->Size; i++)
	{
		if (pListHandle->pCmpFunc(pNode->pData, pFind, pListHandle->RecordLen) == 0)
		{
			if (iFindOrder == iOrder)
				return i;
			
			iFindOrder++;
		}

		pNode = pNode->pNext;
	}

	return -1;
}