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

//����ڵ�
typedef struct _AigListNode
{
	void* pData;					//�ڵ�����
	struct _AigListNode* pNext;		//��һ���ڵ�
}AigListNode;

typedef struct _AigListHandle
{
	int Size;						//�ڵ�����
	int RecordLen;					//�ڵ����ݳ���
	AigListNode* pEntry;			//�ڵ����
	pfn_AIG_CMP_CALLBACK pCmpFunc;	//�ڵ�ȽϺ���
}AigListHandle;

/// <summary>
/// ����	 :	�½��ڵ�
/// ����	 :	pHandle			[in] ���
///			pRecord			[in] �ڵ�����
/// ����ֵ: 
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
/// ����	 :	ɾ���ڵ�
/// ����	 :	pNode			[in] �ڵ�
/// ����ֵ: 
/// </summary> 
static void list_DelNode(AigListNode* pNode)
{
	AIG_FUNC_FREE(pNode->pData);
	AIG_FUNC_FREE(pNode);
}

/// <summary>
/// ����	 :	�½�����
/// ����	 :	iRecordLen		[in] �ڵ����ݳ���
///			pCmpFunc		[in] ����ʱ�ıȽϺ���
/// ����ֵ: 
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
/// ����	 :	��������
/// ����	 :	pHandle			[in] ���
/// ����ֵ: 
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
/// ����	 :	��ӽڵ�
/// ����	 :	pHandle			[in] ���
///			pRecord			[in] �ڵ�����
/// ����ֵ: 
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
/// ����	 :	����ڵ�
/// ����	 :	pHandle			[in] ���
///			pRecord			[in] �ڵ�����
///			iIndex			[in] �ڵ��±�
/// ����ֵ: 
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
/// ����	 :	ɾ���ڵ�
/// ����	 :	pHandle			[in] ���
///			iIndex			[in] �ڵ��±�
/// ����ֵ: 
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
/// ����	 :	ɾ��ȫ���ڵ�
/// ����	 :	pHandle			[in] ���
/// ����ֵ: 
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
/// ����	 :	��ȡ�ڵ�����
/// ����	 :	pHandle			[in] ���
/// ����ֵ: 
/// </summary> 
int list_GetSize(void* pHandle)
{
	if (pHandle == NULL)
		return -1;

	AigListHandle* pListHandle = (AigListHandle*)pHandle;
	return pListHandle->Size;
}

/// <summary>
/// ����	 :	��ȡ�ڵ�����
/// ����	 :	pHandle			[in] ���
///			iIndex			[in] �ڵ��±�
/// ����ֵ: 
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
/// ����	 :	���ҽڵ��±�
/// ����	 :	pHandle			[in] ���
///			pFind			[in] ���ҵĽڵ�
///			iOrder			[in] �ڼ���ƥ��Ľڵ�
/// ����ֵ: 
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