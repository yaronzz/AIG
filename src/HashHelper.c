#include "HashHelper.h"

typedef struct _AigHashNode
{
	void* pKey;					//�ؼ���
	int hash;					//Hashֵ
	void* pValue;				//����
	struct _AigHashNode* pNext;	//�������һ��
}AigHashNode;

typedef struct _AigHashHanle
{
	int Size;						//�ڵ�����
	int KeyLen;
	int ValueLen;
	int Capacity;
	AigHashNode** pEntry;
	pfn_AIG_CMP_CALLBACK pCmpFunc;

}AigHashHanle;


static int hash_CalcCapacity(int iInputCapacity)
{
	int iRet = 1;
	int minimumBucketCount = iInputCapacity * 4 / 3;	//��ϣ���С 0.75 load factor.
	while (iRet <= minimumBucketCount) 
	{
		iRet <<= 1;										// Bucket count must be power of 2.
	}
	
	return iRet;
}

void* hash_Creat(int iKeyLen, int iValueLen, int iHashCapacity, pfn_AIG_CMP_CALLBACK pCmpFunc)
{
	if (iKeyLen <= 0 || iValueLen <= 0 || iHashCapacity <= 0 || pCmpFunc == NULL)
		return NULL;

	AigHashHanle* pHandle = (AigHashHanle*)malloc(sizeof(AigHashHanle));
	memset(pHandle, 0, sizeof(AigHashHanle));

	//��������
	pHandle->Capacity = hash_CalcCapacity(iHashCapacity);

	//����ָ�������ڴ�
	pHandle->pEntry = (AigHashNode**)malloc(sizeof(AigHashNode*) * pHandle->Capacity);
	memset(pHandle->pEntry, 0, sizeof(AigHashNode*) * pHandle->Capacity);

	//������ֵ
	pHandle->Size		= 0;
	pHandle->KeyLen		= iKeyLen;
	pHandle->ValueLen	= iValueLen;
	pHandle->pCmpFunc	= pCmpFunc;

	return pHandle;
}

void hash_Destroy(void** pHandle);

int hash_Insert(void* pHandle, void* pKey, void* pValue, int bIsReplace);

int hash_Remove(void* pHandle, void* pKey);

int hash_RemoveAll(void* pHandle);

void* hash_Find(void* pHandle, void* pKey);

