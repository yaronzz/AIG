#include "BTreeHelper.h"

/*********************************************************
说明：
1、树的组成：根 - 分支 - 叶子
		  
*********************************************************/

typedef struct _AigBTreeNode
{
	short   IsLeaf;					//是否为叶子
	short	KeyNum;					//Key的数量

	unsigned char**	Keys;			//Key集合
	unsigned char** Values;			//值集合

	struct _AigBTreeNode* Parent;	//父节点
	struct _AigBTreeNode** Child;	//子节点数组
}AigBTreeNode;

typedef struct __AIG_BTREE_HANDLE
{
	int Size;						//节点数量		
	int KeyLen;						//关键字长度
	int ValueLen;					//值长度
	int MValue;						//M值,最多有M个孩子,>=2
	int SplitKeyNum;				//新分裂的节点Key数量（根据M值奇偶数不同而不同）

	AigBTreeNode* pRoot;			//根结点
	pfn_AIG_CMP_CALLBACK pCmpFunc;	//节点比较回调函数
} AIG_BTREE_HANDLE;


static AigBTreeNode* btree_CreatNode(AIG_BTREE_HANDLE* pHandle)
{
	AigBTreeNode* pNode = (AigBTreeNode*)AIG_FUNC_MALLOC(sizeof(AigBTreeNode));
	memset(pNode, 0, sizeof(AigBTreeNode));

	pNode->Keys		= (unsigned char**)AIG_FUNC_MALLOC(sizeof(unsigned char*)*(pHandle->MValue - 1));
	pNode->Values	= (unsigned char**)AIG_FUNC_MALLOC(sizeof(unsigned char*)*(pHandle->MValue - 1));
	pNode->Child	= (AigBTreeNode**)AIG_FUNC_MALLOC(sizeof(AigBTreeNode*)*(pHandle->MValue));

	for (int i = 0; i <= pHandle->MValue; i++)
	{
		if (i != pHandle->MValue)
		{
			pNode->Keys[i]		= NULL;
			pNode->Values[i]	= NULL;
		}
		pNode->Child[i]			= NULL;
	}

	return pNode;
}

static int btree_AddRoot(AIG_BTREE_HANDLE* pHandle, unsigned char* pKey, unsigned char* pValue)
{
	if (pHandle->pRoot == NULL)
	{
		AigBTreeNode*pNewNode	= btree_CreatNode(pHandle);
		pNewNode->IsLeaf		= 1;
		pNewNode->KeyNum		= 1;
		pNewNode->Keys[0]		= pKey;
		pNewNode->Values[0]		= pValue;

		pHandle->pRoot			= pNewNode;
		pHandle->Size++;
		return eAEC_Success;
	}

	return eAEC_Err;
}

static 	AigBTreeNode* btree_FindKeyNode(AIG_BTREE_HANDLE* pHandle, unsigned char* pKey)
{
	if (pHandle->pRoot == NULL)
		return NULL;

	int iIndex;
	AigBTreeNode* pNode = pHandle->pRoot;
	while (!pNode->IsLeaf)
	{
		for (iIndex = 0; iIndex < pNode->KeyNum; iIndex++)
		{
			int iCmp = pHandle->pCmpFunc(pNode->Keys[iIndex], pKey, pHandle->KeyLen);
			if (iCmp >= 0)
				break;
		}
		pNode = pNode->Child[iIndex];
	}

	return pNode;
}

static int btree_FindKeyIndex(AIG_BTREE_HANDLE* pHandle, AigBTreeNode* pKeyNode, unsigned char* pKey)
{
	for (int iIndex = 0; iIndex < pKeyNode->KeyNum; iIndex++)
	{
		int iCmp = pHandle->pCmpFunc(pKeyNode->Keys[iIndex], pKey, pHandle->KeyLen);
		if (iCmp == 0)
			return iIndex;
	}
	return -1;
}

static int btree_GetKeyInsertIndex(AIG_BTREE_HANDLE* pHandle, AigBTreeNode* pKeyNode, unsigned char* pKey)
{
	for (int iIndex = 0; iIndex < pKeyNode->KeyNum; iIndex++)
	{
		int iCmp = pHandle->pCmpFunc(pKeyNode->Keys[iIndex], pKey, pHandle->KeyLen);
		if (iCmp >= 0)
			return iIndex;
	}
	return 0;
}

static int btree_InsertKey(AIG_BTREE_HANDLE* pHandle, AigBTreeNode* pKeyNode, int iIndex, unsigned char* pKey, unsigned char* pValue)
{
	for (int i = pKeyNode->KeyNum; i > iIndex; i--)
	{
		pKeyNode->Keys[i]		= pKeyNode->Keys[i - 1];
		pKeyNode->Values[i]		= pKeyNode->Values[i - 1];
	}
	pKeyNode->Keys[iIndex]		= pKey;
	pKeyNode->Values[iIndex]	= pValue;
	pKeyNode->KeyNum++;

	return 0;
}

static int btree_InsertKeyAfterSplit(AIG_BTREE_HANDLE* pHandle, AigBTreeNode* pKeyNode, int iIndex, unsigned char* pKey, unsigned char* pValue)
{
	int iRightNum	= pHandle->SplitKeyNum;
	int iLeftNum	= pKeyNode->KeyNum - iRightNum;

	//分裂
	AigBTreeNode*pNewNode = btree_CreatNode(pHandle);
	pNewNode->IsLeaf = 1;
	pNewNode->KeyNum = iRightNum;
	for (int i = 0; i < iRightNum; i++)
	{
		pNewNode->Keys[i]	= pKeyNode->Keys[iRightNum + i];
		pNewNode->Values[i] = pKeyNode->Values[iRightNum + i];
		pNewNode->Child[i]	= pKeyNode->Child[iRightNum + i];

		pKeyNode->Keys[iRightNum + i]	= NULL;
		pKeyNode->Values[iRightNum + i] = NULL;
		pKeyNode->Child[iRightNum + i]	= NULL;
	}

	//重置原节点的Key数量
	pKeyNode->KeyNum = iLeftNum;

	//获取父亲的Key
	unsigned char* pParentKey	= pKey;
	unsigned char* pParentValue = pValue;
	if (iLeftNum > iIndex)
	{
		pParentKey		= pKeyNode->Keys[iLeftNum - 1];
		pParentValue	= pKeyNode->Values[iLeftNum - 1];
		for (int i = iLeftNum - 1; i > iIndex; i--)
		{	
			pKeyNode->Keys[i]		= pKeyNode->Keys[i - 1];
			pKeyNode->Values[i]		= pKeyNode->Values[i - 1];
		}
		pKeyNode->Keys[iIndex]		= pKey;
		pKeyNode->Values[iIndex]	= pValue;
	}
	else
	{
		pParentKey		= pNewNode->Keys[0];
		pParentValue	= pNewNode->Values[0];
		for (int i = 0; i < iIndex; i++)
		{
			pNewNode->Keys[i]		= pNewNode->Keys[i + 1];
			pNewNode->Values[i]		= pNewNode->Values[i + 1];
		}
		pNewNode->Keys[iIndex]		= pKey;
		pNewNode->Values[iIndex]	= pValue;
	}

	//如果没有父分支则创建一个
	AigBTreeNode*pParentNode = pKeyNode->Parent;
	if (pParentNode == NULL)
	{
		AigBTreeNode*pRoot	= btree_CreatNode(pHandle);
		pRoot->Keys[0]		= pParentKey;
		pRoot->Values[0]	= pParentValue;
		pRoot->KeyNum		= 1;
		pRoot->Child[0]		= pKeyNode;
		pRoot->Child[1]		= pNewNode;

		pKeyNode->Parent	= pRoot;
		pNewNode->Parent	= pRoot;
		return eAEC_Success;
	}

	//将Key插入到父分支中
	int iParentIndex = btree_GetKeyInsertIndex(pHandle, pParentNode, pParentKey);
	if (pParentNode->KeyNum < pHandle->MValue - 1)
		return btree_InsertKey(pHandle, pParentNode, iParentIndex, pParentKey, pParentValue);
	else 
		return btree_InsertKeyAfterSplit(pHandle, pParentNode, iParentIndex, pParentKey, pParentValue);
}


void* btree_Creat(int iMValue, int iKeyLen, int iValueLen, pfn_AIG_CMP_CALLBACK pCmpFunc)
{
	if (iMValue < 2 || pCmpFunc == NULL)
		return NULL;

	AIG_BTREE_HANDLE* pHandle = (AIG_BTREE_HANDLE*)AIG_FUNC_MALLOC(sizeof(AIG_BTREE_HANDLE));
	memset(pHandle, 0, sizeof(AIG_BTREE_HANDLE));

	pHandle->Size			= 0;
	pHandle->MValue			= iMValue;
	pHandle->SplitKeyNum	= iMValue % 2 == 0 ? iMValue / 2 - 1 : iMValue / 2;
	pHandle->pCmpFunc		= pCmpFunc;

	return pHandle;
}

void btree_Destroy(void** pHandle)
{
	if (pHandle == NULL || *pHandle == NULL)
		return;

	AIG_BTREE_HANDLE* pTreeHandle = (AIG_BTREE_HANDLE*)pHandle;
	//btree_RemoveAll(*pHandle);
	AIG_FUNC_FREE(*pHandle);

	*pHandle = NULL;
}



int btree_Insert(void* pHandle, void* pKey, void* pValue, void** pOldValue)
{
	if (pHandle == NULL || pKey == NULL)
		return eAEC_Input;

	AIG_BTREE_HANDLE* pTreeHandle = (AIG_BTREE_HANDLE*)pHandle;
	if (pTreeHandle->pRoot == NULL)
		return btree_AddRoot(pTreeHandle, pKey, pValue);

	//查找叶子节点
	AigBTreeNode* pKeyNode = btree_FindKeyNode(pTreeHandle, pKey);

	//查询是否已经存在此Key
	int iIndex = btree_FindKeyIndex(pTreeHandle, pKeyNode, pKey);
	if (iIndex >= 0)
	{
		if (pOldValue)
			*pOldValue = pKeyNode->Values[iIndex];

		pKeyNode->Values[iIndex] = pValue;
		return eAEC_Success;
	}

	//查询Key的插入位置
	iIndex = btree_GetKeyInsertIndex(pTreeHandle, pKeyNode, pKey);
	if (pKeyNode->KeyNum < pTreeHandle->MValue - 1)
		btree_InsertKey(pTreeHandle, pKeyNode, iIndex, pKey, pValue);
	else

	pTreeHandle->Size++;
	return eAEC_Success;
}

int btree_Remove(void* pHandle, void* pKey);

int btree_RemoveAll(void* pHandle);

void* btree_Find(void* pHandle, void* pKey);

int btree_GetSize(void* pHandle);


