#include "HashHelper.h"

/*********************************************************
˵����
1�������������ȡ��ֵ���������ⲿ�Ķ�
2�����ڵ����������������3/4ʱ����Ҫ��������
3�����ڵ���±���ͬʱ��������ķ�ʽ��ֹ��ͻ
*********************************************************/

typedef struct _AigHashNode
{
	int	Hash;						//Hashֵ
	unsigned char*	pKey;			//�ؼ���
	unsigned char*	pValue;			//����
	struct _AigHashNode* pNext;		//�������һ��
}AigHashNode;

typedef struct _AigHashHanle
{
	int Size;						//�ڵ�����
	int KeyLen;						//�ؼ��ֵĳ���
	int ValueLen;					//ֵ�ĳ���
	int Capacity;					//��ϣ������
	AigHashNode** pEntry;			//�������
	pfn_AIG_CMP_CALLBACK pCmpFunc;	//�ؼ��ֱȽ�����

	unsigned char* pSeekKey;		//����ʱ���صĹؼ��ֻ���
	int SeekIndex;					//����ʱ������±�
	int SeekSubIndex;				//����ʱ������±�
}AigHashHanle;


int hash_AlgorithmBKDR(char* pStr);
int hash_AlgorithmFNV(char* pStr);
int hash_AlgorithmFNV_1A(char* pStr);
int hash_AlgorithmAP(char* pStr);
int hash_AlgorithmDJP(char* pStr);
int hash_AlgorithmDJP2(char* pStr);
int hash_AlgorithmJS(char* pStr);
int hash_AlgorithmSDMS(char* pStr);
int hash_AlgorithmRS(char* pStr);
int hash_AlgorithmDEK(char* pStr);
int hash_AlgorithmELF(char* pStr);

/// <summary>
/// ����	 :	��������
/// ����	 :	iInputCapacity		[in] ����
/// ����ֵ: 
/// </summary> 
static int hash_CalcCapacity(int iInputCapacity)
{
	//��ϣ���С 0.75 load factor.
	int minimumBucketCount = iInputCapacity * 4 / 3;

	// Bucket count must be power of 2.
	int iRet = 1;
	while (iRet <= minimumBucketCount)
		iRet <<= 1;										
	
	return iRet;
}

/// <summary>
/// ����	 :	�����ϣֵ
/// ����	 :	pHandle				[in] ���
///			pKey				[in] �ؼ���
/// ����ֵ: 
/// </summary> 
static int hash_CalcHash(AigHashHanle*pMap, void* pKey)
{
	int hash = hash_AlgorithmBKDR(pKey);
	//��ڶ���
	hash += ~(hash << 9);
	hash ^= (((unsigned int)hash) >> 14);
	hash += (hash << 4);
	hash ^= (((unsigned int)hash) >> 10);

	return hash;
}

/// <summary>
/// ����	 :	�����ϣֵ���ڵ��±�
/// ����	 :	pHandle				[in] ���
///			Capacity			[in] ��ϣ������
/// ����ֵ: 
/// </summary> 
static int hash_CalcHashIndex(int hash, int Capacity)
{
	return (hash)& (Capacity - 1);
}

/// <summary>
/// ����	 :	���������������ǰ�ڵ����������0.75���������������ϣ��
/// ����	 :	pHandle				[in] ���
/// ����ֵ: 
/// </summary> 
static int hash_ExpandIfNecessary(AigHashHanle* pHandle)
{
	if (pHandle->Size > pHandle->Capacity * 3 / 4)
	{
		int NewBuckerCount		= pHandle->Capacity << 1;
		AigHashNode** pNewEntry = (AigHashNode**)malloc(sizeof(AigHashNode*) * NewBuckerCount);
		AigHashNode* pTmp		= NULL;
		AigHashNode* pNext		= NULL;
		int Index				= 0;

		for (int i = 0; i < pHandle->Capacity; i++)
		{
			pTmp = pHandle->pEntry[i];
			while (pTmp != NULL)
			{
				//�����±�
				Index = hash_CalcHashIndex(pTmp->Hash, NewBuckerCount);

				pNext				= pTmp->pNext;
				pTmp->pNext			= pNewEntry[Index];
				pNewEntry[Index]	= pTmp;
				pTmp				= pNext;
			}
		}

		free(pHandle->pEntry);
		pHandle->Capacity	= NewBuckerCount;
		pHandle->pEntry		= pNewEntry;
	}
	return 0;
}

/// <summary>
/// ����	 :	����ڵ�
/// ����	 :	pHandle				[in] ���
///			pKey				[in] �ؼ���
///			pValue				[in] ֵ
///			hash				[in] ��ϣֵ2
/// ����ֵ: 
/// </summary> 
static AigHashNode* hash_CreatNode(AigHashHanle* pHandle, void* pKey, void* pValue, int hash)
{
	AigHashNode* pNode = (AigHashNode*)malloc(sizeof(AigHashNode));
	void* pNewKey	= malloc(pHandle->KeyLen);
	void* pNewValue = pHandle->ValueLen > 0 ? malloc(pHandle->ValueLen) : NULL;

	pNode->Hash		= hash;
	pNode->pKey		= pNewKey;
	pNode->pValue	= pNewValue;
	pNode->pNext	= NULL;

	memcpy(pNewKey, pKey, pHandle->KeyLen);
	if (pHandle->ValueLen > 0)
		memcpy(pNewValue, pValue, pHandle->ValueLen);

	return pNode;
}

/// <summary>
/// ����	 :	���ٽڵ�
/// ����	 :	pNode				[in] �ڵ�
/// ����ֵ: 
/// </summary> 
static void hash_DestroyNode(AigHashNode* pNode)
{
	free(pNode->pKey);
	if (pNode->pValue)
		free(pNode->pValue);

	free(pNode);
}

/// <summary>
/// ����	 :	�жϹؼ����Ƿ���ͬ
/// ����	 :	pHandle				[in] ���
///			pKey0				[in] �ؼ���1
///			hash0				[in] ��ϣֵ1
///			pKey1				[in] �ؼ���2
///			hash1				[in] ��ϣֵ2
/// ����ֵ: 
/// </summary> 
static int hash_IsEqualKeys(AigHashHanle* pHandle, void* pKey0, int hash0, void* pKey1, int hash1)
{
	//���жϹ�ϣֵ,�ٵ��ûص������ж�
	if (hash0 != hash1)	//hashֵ��ͬ
		return 0;

	return pHandle->pCmpFunc(pKey0, pKey1, pHandle->KeyLen) == 0;
}

/// <summary>
/// ����	 :	������ϣ��
/// ����	 :	iKeyLen				[in] �ؼ��ֳ���
///			iValueLen			[in] ֵ����
///			iHashCapacity		[in] ����
///			pCmpFunc			[in] �ȽϺ���
/// ����ֵ: 
/// </summary> 
void* hash_Creat(int iKeyLen, int iValueLen, int iHashCapacity, pfn_AIG_CMP_CALLBACK pCmpFunc)
{
	if (iKeyLen <= 0 || iValueLen < 0 || iHashCapacity <= 0 || pCmpFunc == NULL)
		return NULL;

	AigHashHanle* pHandle = (AigHashHanle*)malloc(sizeof(AigHashHanle));
	memset(pHandle, 0, sizeof(AigHashHanle));

	//��������
	pHandle->Capacity = hash_CalcCapacity(iHashCapacity);

	//����ָ�������ڴ�
	pHandle->pEntry = (AigHashNode**)malloc(sizeof(AigHashNode*) * pHandle->Capacity);
	memset(pHandle->pEntry, 0, sizeof(AigHashNode*) * pHandle->Capacity);

	//��������õ�Key����Ҫ�Ƿ�ֹ���ⲿָ��������޸���key
	pHandle->pSeekKey = (unsigned char*)malloc(iKeyLen);
	memset(pHandle->pSeekKey, 0, iKeyLen);

	//������ֵ
	pHandle->Size		= 0;
	pHandle->KeyLen		= iKeyLen;
	pHandle->ValueLen	= iValueLen;
	pHandle->pCmpFunc	= pCmpFunc;

	return pHandle;
}

/// <summary>
/// ����	 :	���ٹ�ϣ��
/// ����	 :	pHandle				[in-out] ���
/// ����ֵ: 
/// </summary> 
void hash_Destroy(void** pHandle)
{
	if (pHandle == NULL || *pHandle == NULL)
		return;

	AigHashHanle* pHashHandle = (AigHashHanle*)pHandle;
	hash_RemoveAll(*pHandle);
	free(pHashHandle->pEntry);
	free(pHashHandle->pSeekKey);
	free(*pHandle);

	*pHandle = NULL;
}

/// <summary>
/// ����	 :	����ڵ�
/// ����	 :	pHandle				[in] ���
///			pKey				[in] �ؼ���
///			pValue				[in] ֵ
///			bIsReplace			[in] ����Ѵ����Ƿ��滻
/// ����ֵ: 
/// </summary> 
int hash_Insert(void* pHandle, void* pKey, void* pValue, int bIsReplace)
{
	if (pHandle == NULL || pKey == NULL)
		return eAEC_Input;

	AigHashHanle* pHashHandle = (AigHashHanle*)pHandle;
	if (pValue == NULL && pHashHandle->ValueLen > 0)
		return eAEC_Input;

	int iHash				= hash_CalcHash(pHashHandle, pKey);
	int iHashIndex			= hash_CalcHashIndex(iHash, pHashHandle->Capacity);
	AigHashNode** pEntry	= &(pHashHandle->pEntry[iHashIndex]);
	AigHashNode*  pCurrent	= *pEntry;

	while (1)
	{
		pCurrent = *pEntry;
		if (pCurrent == NULL)
		{
			*pEntry = hash_CreatNode(pHashHandle, pKey, pValue, iHash);
			pHashHandle->Size++;

			//��������
			hash_ExpandIfNecessary(pHashHandle);
			break;
		}
		//���ʹ�õ���ͬһ��Key���滻
		if (hash_IsEqualKeys(pHashHandle, pCurrent->pKey, pCurrent->Hash, pKey, iHash))
		{
			if (!bIsReplace)
				return eAEC_AlreadyExist;

			if (pHashHandle->ValueLen > 0)
				memcpy(pCurrent->pValue, pValue, pHashHandle->ValueLen);
			pCurrent->Hash = iHash;
			break;
		}
		pEntry = &pCurrent->pNext;
	}

	return eAEC_Success;
}

/// <summary>
/// ����	 :	�Ƴ��ڵ�
/// ����	 :	pHandle				[in] ���
///			pKey				[in] �ؼ���
/// ����ֵ: 
/// </summary> 
int hash_Remove(void* pHandle, void* pKey)
{
	if (pHandle == NULL || pKey == NULL)
		return eAEC_Input;

	AigHashHanle* pHashHandle	= (AigHashHanle*)pHandle;
	int iHash					= hash_CalcHash(pHashHandle, pKey);
	int iHashIndex				= hash_CalcHashIndex(iHash, pHashHandle->Capacity);
	AigHashNode** pEntry		= &(pHashHandle->pEntry[iHashIndex]);
	AigHashNode*  pCurrent		= *pEntry;

	while ((pCurrent = *pEntry) != NULL)
	{
		if (hash_IsEqualKeys(pHashHandle, pCurrent->pKey, pCurrent->Hash, pKey, iHash))
		{
			//�Ƚ�ָ��ָ����һ����ɾ��
			*pEntry = pCurrent->pNext;
			hash_DestroyNode(pCurrent);

			pHashHandle->Size--;
			break;
		}
		pEntry = &pCurrent->pNext;
	}
	return eAEC_Success;
}

/// <summary>
/// ����	 :	�Ƴ�ȫ���ڵ�
/// ����	 :	pHandle				[in] ���
/// ����ֵ: 
/// </summary> 
int hash_RemoveAll(void* pHandle)
{
	if (pHandle == NULL)
		return eAEC_Input;

	AigHashHanle* pHashHandle = (AigHashHanle*)pHandle;
	AigHashNode* pEntry;
	AigHashNode* pNext;

	for (int i = 0; i < pHashHandle->Capacity; i++)
	{
		pEntry = pHashHandle->pEntry[i];
		if (pEntry != NULL)
		{
			pNext = pEntry->pNext;
			hash_DestroyNode(pEntry);

			pEntry = pNext;
		}
	}

	pHashHandle->Size = 0;
	return eAEC_Success;
}

/// <summary>
/// ����	 :	��ȡ��ǰ�ڵ������
/// ����	 :	pHandle				[in]  ���
/// ����ֵ: 
/// </summary> 
int hash_GetSize(void* pHandle)
{
	if (pHandle == 0)
		return eAEC_Err;

	AigHashHanle* pHashHandle = (AigHashHanle*)pHandle;
	return pHashHandle->Size;
}

/// <summary>
/// ����	 :	����ǰ����
/// ����	 :	pHandle				[in]  ���
/// ����ֵ: 
/// </summary> 
int hash_SetOut(void* pHandle)
{
	if (pHandle == 0)
		return eAEC_Err;

	AigHashHanle* pHashHandle	= (AigHashHanle*)pHandle;
	pHashHandle->SeekIndex		= 0;
	pHashHandle->SeekSubIndex	= 0;

	return eAEC_Success;
}

/// <summary>
/// ����	 :	������һ��
/// ����	 :	pHandle				[in]  ���
///			out_pKey			[out] �ؼ���
///			out_pValue			[out] ֵ
/// ����ֵ: 
/// </summary> 
int hash_GetNext(void* pHandle, void** out_pKey, void** out_pValue)
{
	if (pHandle == 0 || out_pKey == NULL)
		return eAEC_Err;

	AigHashHanle* pHashHandle = (AigHashHanle*)pHandle;
	if (pHashHandle->Size == 0)
		return eAEC_End;

	AigHashNode* pEntry = pHashHandle->pEntry[pHashHandle->SeekIndex];
	AigHashNode* pCurrent = pEntry;

	//��ȡ�ڵ�
	for (int i = 0; i < pHashHandle->SeekSubIndex && pCurrent != NULL; i++)
		pCurrent = pCurrent->pNext;

	//ѭ��ȡ����һ����ȷ�ڵ�
	while (pCurrent == NULL)
	{
		if (pHashHandle->SeekIndex == pHashHandle->Capacity - 1)
			return eAEC_End;

		pHashHandle->SeekSubIndex = 0;
		pHashHandle->SeekIndex++;

		pEntry = pHashHandle->pEntry[pHashHandle->SeekIndex];
		pCurrent = pEntry;
	}

	//��ֵ
	memcpy(pHashHandle->pSeekKey, pCurrent->pKey, pHashHandle->KeyLen);
	*out_pKey = pHashHandle->pSeekKey;
	if (out_pValue)
		*out_pValue = pCurrent->pValue;

	//ָ����һ��
	pHashHandle->SeekSubIndex++;
	return eAEC_Success;
}

/// <summary>
/// ����	 :	����
/// ����	 :	pHandle				[in] ���
///			pKey				[in] �ؼ���
/// ����ֵ: 
/// </summary> 
void* hash_Find(void* pHandle, void* pKey)
{
	if (pHandle == NULL || pKey == NULL)
		return NULL;

	AigHashHanle* pHashHandle	= (AigHashHanle*)pHandle;
	int iHash					= hash_CalcHash(pHashHandle, pKey);
	int iHashIndex				= hash_CalcHashIndex(iHash, pHashHandle->Capacity);
	AigHashNode** pEntry		= &(pHashHandle->pEntry[iHashIndex]);
	AigHashNode*  pCurrent		= *pEntry;

	while ((pCurrent = *pEntry) != NULL)
	{
		if (hash_IsEqualKeys(pHashHandle, pCurrent->pKey, pCurrent->Hash, pKey, iHash))
			return pCurrent->pValue;
		
		pEntry = &pCurrent->pNext;
	}
	return NULL;
}


//********************************�ַ�����ϣ�㷨********************************
//HASH-BKDR
int hash_AlgorithmBKDR(char* pStr)
{
	unsigned int iTmp = 0;
	unsigned int iSeed = 131;	//31 131 1313 13131
	while (*pStr != '\0')
	{
		iTmp = iTmp * iSeed + (*pStr++);
	}
	return (iTmp & 0x7FFFFFFF);
}

//HASH-FNV
int hash_AlgorithmFNV(char* pStr)
{
	unsigned int iTmp = 2166136261UL;
	unsigned int iPrime = 16777619;
	while (*pStr != '\0')
	{
		iTmp *= iPrime;
		iTmp ^= *pStr++;
	}
	return (iTmp & 0x7FFFFFFF);
}

//HASH-FNV-1a
int hash_AlgorithmFNV_1A(char* pStr)
{
	unsigned int iTmp = 2166136261UL;
	unsigned int iPrime = 16777619;
	while (*pStr != '\0')
	{
		iTmp ^= (*pStr++);
		iTmp *= iPrime;
	}
	return (iTmp & 0x7FFFFFFF);
}

//HASH-AP
int hash_AlgorithmAP(char* pStr)
{
	unsigned int iValue = 0, iTmp = 0;

	while (*pStr != '\0')
	{
		if ((iValue++ & 1) == 0)
			iTmp ^= ((iTmp << 7) ^ (*pStr++) ^ (iTmp << 3));
		else
			iTmp ^= (~((iTmp << 11) ^ (*pStr++) ^ (iTmp << 5)));
	}
	return (iTmp & 0x7FFFFFFF);
}

//HASH-DJP
int hash_AlgorithmDJP(char* pStr)
{
	unsigned int iTmp = 5381;
	while (*pStr != '\0')
	{
		iTmp += (iTmp << 5) + (*pStr++);
	}
	return (iTmp & 0x7FFFFFFF);
}

//HASH-DJP2
int hash_AlgorithmDJP2(char* pStr)
{
	unsigned int iTmp = 5381;
	while (*pStr != '\0')
	{
		iTmp = iTmp * 33 ^ (*pStr++);
	}
	return (iTmp & 0x7FFFFFFF);
}

//HASH-JS
int hash_AlgorithmJS(char* pStr)
{
	unsigned int iTmp = 0;
	while (*pStr != '\0')
	{
		iTmp ^= ((iTmp << 5) + (*pStr++) + (iTmp << 2));
	}
	return (iTmp & 0x7FFFFFFF);
}

//HASH-SDMS
int hash_AlgorithmSDMS(char* pStr)
{
	unsigned int iTmp = 0;
	while (*pStr != '\0')
	{
		iTmp = 65599 * iTmp + (*pStr++);
	}
	return (iTmp & 0x7FFFFFFF);
}

//HASH-RS
int hash_AlgorithmRS(char* pStr)
{
	unsigned int iTmp = 0;
	unsigned int iMagic = 63689;
	while (*pStr != '\0')
	{
		iTmp = iTmp * iMagic + (*pStr++);
		iMagic *= 378551;
	}
	return (iTmp & 0x7FFFFFFF);
}


//HASH-DEK
int hash_AlgorithmDEK(char* pStr)
{
	unsigned int iTmp = 0;
	while (*pStr != '\0')
	{
		iTmp = ((iTmp << 5) ^ (iTmp >> 27) ^ (*pStr++));
	}
	return (iTmp & 0x7FFFFFFF);
}

//HASH-ELF
int hash_AlgorithmELF(char* pStr)
{
	unsigned int iTmp = 0;
	unsigned int iValue = 0;
	while (*pStr != '\0')
	{
		iTmp = (iTmp << 24) + (*pStr++);
		if ((iValue = iTmp & 0xF0000000L) != 0)
		{
			iTmp ^= (iTmp >> 24);
			iTmp &= ~iValue;
		}
	}
	return (iTmp & 0x7FFFFFFF);
}