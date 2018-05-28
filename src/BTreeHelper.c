#include "BTreeHelper.h"

typedef struct _AigBTreeNode
{
	short   IsLeaf;					//�Ƿ�ΪҶ��
	short	KeyNum;					//Key������

	unsigned char**	Keys;			//Key����
	unsigned char** Values;			//ֵ����

	struct _BTNode* Parent;			//���ڵ�
	struct _BTNode** Child;			//�ӽڵ�����
}AigBTreeNode;

typedef struct __AIG_BTREE_HANDLE
{
	int Size;						//�ڵ�����		
	int KeyLen;						//�ؼ��ֳ���
	int ValueLen;					//ֵ����
	int MValue;						//Mֵ,�����M������,>=2
	int SplitKeyNum;				//�·��ѵĽڵ�Key����������Mֵ��ż����ͬ����ͬ��

	AigBTreeNode* pRoot;			//�����
	pfn_AIG_CMP_CALLBACK pCmpFunc;	//�ڵ�Ƚϻص�����
} AIG_BTREE_HANDLE;

static AigBTreeNode* btree_CreatNode(AIG_BTREE_HANDLE* pHandle)
{
	AigBTreeNode* pNode = (AigBTreeNode*)malloc(sizeof(AigBTreeNode));
	memset(pNode, 0, sizeof(AigBTreeNode));


	return pNode;
}


void* btree_Creat(int iMValue, int iKeyLen, int iValueLen, pfn_AIG_CMP_CALLBACK pCmpFunc)
{
	if (iMValue < 2 || pCmpFunc == NULL)
		return NULL;

	AIG_BTREE_HANDLE* pHandle = (AIG_BTREE_HANDLE*)malloc(sizeof(AIG_BTREE_HANDLE));
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
	btree_RemoveAll(*pHandle);
	free(*pHandle);

	*pHandle = NULL;
}

int btree_Insert(void* pHandle, void* pKey, void* pValue, int bIsReplace)
{
	if (pHandle == NULL || pKey == NULL)
		return eAEC_Input;

	AIG_BTREE_HANDLE* pTreeHandle = (AIG_BTREE_HANDLE*)pHandle;


	return eAEC_Success;
}

int btree_Remove(void* pHandle, void* pKey);

int btree_RemoveAll(void* pHandle);

void* btree_Find(void* pHandle, void* pKey);

int btree_GetSize(void* pHandle);


