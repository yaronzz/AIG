#include "HashHelper.h"

/*********************************************************
说明：
1、查找与遍历获取的值，可以在外部改动
2、当节点的数量超过容量的3/4时，需要扩大容量
3、当节点的下标相同时，用链表的方式防止冲突
*********************************************************/

typedef struct _AigHashNode
{
	int	Hash;						//Hash值
	unsigned char*	pKey;			//关键字
	unsigned char*	pValue;			//数据
	struct _AigHashNode* pNext;		//链表的下一个
}AigHashNode;

typedef struct _AigHashHanle
{
	int Size;						//节点数量
	int KeyLen;						//关键字的长度
	int ValueLen;					//值的长度
	int Capacity;					//哈希表容量
	AigHashNode** pEntry;			//入口数组
	pfn_AIG_CMP_CALLBACK pCmpFunc;	//关键字比较行数
	pfn_AIG_HASH_CALCHASH_CALLBACK pCalcHashFunc;	//计算哈希值

	unsigned char* pSeekKey;		//遍历时返回的关键字缓存
	int SeekIndex;					//遍历时数组的下标
	int SeekSubIndex;				//遍历时链表的下标
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
/// 功能	 :	计算容量
/// 参数	 :	iInputCapacity		[in] 容量
/// 返回值: 
/// </summary> 
static int hash_CalcCapacity(int iInputCapacity)
{
	//哈希表大小 0.75 load factor.
	int minimumBucketCount = iInputCapacity * 4 / 3;

	// Bucket count must be power of 2.
	int iRet = 1;
	while (iRet <= minimumBucketCount)
		iRet <<= 1;										
	
	return iRet;
}

/// <summary>
/// 功能	 :	计算哈希值
/// 参数	 :	pHandle				[in] 句柄
///			pKey				[in] 关键字
/// 返回值: 
/// </summary> 
static int hash_CalcHash(AigHashHanle*pMap, void* pKey)
{
	int hash = 0;
	
	if (pMap->pCalcHashFunc == NULL)
		hash = hash_AlgorithmBKDR(pKey);
	else
		hash = pMap->pCalcHashFunc(pKey, pMap->KeyLen);

	//求第二层
	hash += ~(hash << 9);
	hash ^= (((unsigned int)hash) >> 14);
	hash += (hash << 4);
	hash ^= (((unsigned int)hash) >> 10);

	return hash;
}

/// <summary>
/// 功能	 :	计算哈希值所在的下标
/// 参数	 :	pHandle				[in] 句柄
///			Capacity			[in] 哈希表容量
/// 返回值: 
/// </summary> 
static int hash_CalcHashIndex(int hash, int Capacity)
{
	return (hash)& (Capacity - 1);
}

/// <summary>
/// 功能	 :	扩大容量（如果当前节点的数量超过0.75倍的容量则扩充哈希表）
/// 参数	 :	pHandle				[in] 句柄
/// 返回值: 
/// </summary> 
static int hash_ExpandIfNecessary(AigHashHanle* pHandle)
{
	if (pHandle->Size > pHandle->Capacity * 3 / 4)
	{
		int NewBuckerCount		= pHandle->Capacity << 1;
		AigHashNode** pNewEntry = (AigHashNode**)AIG_FUNC_MALLOC(sizeof(AigHashNode*) * NewBuckerCount);
		AigHashNode* pTmp		= NULL;
		AigHashNode* pNext		= NULL;
		int Index				= 0;

		for (int i = 0; i < pHandle->Capacity; i++)
		{
			pTmp = pHandle->pEntry[i];
			while (pTmp != NULL)
			{
				//计算下标
				Index = hash_CalcHashIndex(pTmp->Hash, NewBuckerCount);

				pNext				= pTmp->pNext;
				pTmp->pNext			= pNewEntry[Index];
				pNewEntry[Index]	= pTmp;
				pTmp				= pNext;
			}
		}

		AIG_FUNC_FREE(pHandle->pEntry);
		pHandle->Capacity	= NewBuckerCount;
		pHandle->pEntry		= pNewEntry;
	}
	return 0;
}

/// <summary>
/// 功能	 :	创界节点
/// 参数	 :	pHandle				[in] 句柄
///			pKey				[in] 关键字
///			pValue				[in] 值
///			hash				[in] 哈希值2
/// 返回值: 
/// </summary> 
static AigHashNode* hash_CreatNode(AigHashHanle* pHandle, void* pKey, void* pValue, int hash)
{
	AigHashNode* pNode = (AigHashNode*)AIG_FUNC_MALLOC(sizeof(AigHashNode));
	void* pNewKey	= AIG_FUNC_MALLOC(pHandle->KeyLen);
	void* pNewValue = pHandle->ValueLen > 0 ? AIG_FUNC_MALLOC(pHandle->ValueLen) : NULL;

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
/// 功能	 :	销毁节点
/// 参数	 :	pNode				[in] 节点
/// 返回值: 
/// </summary> 
static void hash_DestroyNode(AigHashNode* pNode)
{
	AIG_FUNC_FREE(pNode->pKey);
	if (pNode->pValue)
		AIG_FUNC_FREE(pNode->pValue);

	AIG_FUNC_FREE(pNode);
}

/// <summary>
/// 功能	 :	判断关键字是否相同
/// 参数	 :	pHandle				[in] 句柄
///			pKey0				[in] 关键字1
///			hash0				[in] 哈希值1
///			pKey1				[in] 关键字2
///			hash1				[in] 哈希值2
/// 返回值: 
/// </summary> 
static int hash_IsEqualKeys(AigHashHanle* pHandle, void* pKey0, int hash0, void* pKey1, int hash1)
{
	//先判断哈希值,再调用回调函数判断
	if (hash0 != hash1)	//hash值不同
		return 0;

	return pHandle->pCmpFunc(pKey0, pKey1, pHandle->KeyLen) == 0;
}

/// <summary>
/// 功能	 :	创建哈希表
/// 参数	 :	iKeyLen				[in] 关键字长度
///			iValueLen			[in] 值长度
///			iHashCapacity		[in] 容量
///			pCmpFunc			[in] 比较函数
/// 返回值: 
/// </summary> 
void* hash_Creat(int iKeyLen, int iValueLen, int iHashCapacity, pfn_AIG_CMP_CALLBACK pCmpFunc, pfn_AIG_HASH_CALCHASH_CALLBACK pCalcHashFunc)
{
	if (iKeyLen <= 0 || iValueLen < 0 || iHashCapacity <= 0 || pCmpFunc == NULL)
		return NULL;

	AigHashHanle* pHandle = (AigHashHanle*)AIG_FUNC_MALLOC(sizeof(AigHashHanle));
	memset(pHandle, 0, sizeof(AigHashHanle));

	//计算容量
	pHandle->Capacity = hash_CalcCapacity(iHashCapacity);

	//申请指针数组内存
	pHandle->pEntry = (AigHashNode**)AIG_FUNC_MALLOC(sizeof(AigHashNode*) * pHandle->Capacity);
	memset(pHandle->pEntry, 0, sizeof(AigHashNode*) * pHandle->Capacity);

	//申请遍历用的Key，主要是防止给外部指针后，随意修改了key
	pHandle->pSeekKey = (unsigned char*)AIG_FUNC_MALLOC(iKeyLen);
	memset(pHandle->pSeekKey, 0, iKeyLen);

	//其他赋值
	pHandle->Size			= 0;
	pHandle->KeyLen			= iKeyLen;
	pHandle->ValueLen		= iValueLen;
	pHandle->pCmpFunc		= pCmpFunc;
	pHandle->pCalcHashFunc	= pCalcHashFunc;

	return pHandle;
}

/// <summary>
/// 功能	 :	销毁哈希表
/// 参数	 :	pHandle				[in-out] 句柄
/// 返回值: 
/// </summary> 
void hash_Destroy(void** pHandle)
{
	if (pHandle == NULL || *pHandle == NULL)
		return;

	AigHashHanle* pHashHandle = (AigHashHanle*)pHandle;
	hash_RemoveAll(*pHandle);
	AIG_FUNC_FREE(pHashHandle->pEntry);
	AIG_FUNC_FREE(pHashHandle->pSeekKey);
	AIG_FUNC_FREE(*pHandle);

	*pHandle = NULL;
}

/// <summary>
/// 功能	 :	插入节点
/// 参数	 :	pHandle				[in] 句柄
///			pKey				[in] 关键字
///			pValue				[in] 值
///			bIsReplace			[in] 如果已存在是否替换
/// 返回值: 
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

			//扩大容量
			hash_ExpandIfNecessary(pHashHandle);
			break;
		}
		//如果使用的是同一个Key则替换
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
/// 功能	 :	移除节点
/// 参数	 :	pHandle				[in] 句柄
///			pKey				[in] 关键字
/// 返回值: 
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
			//先将指针指向下一个再删除
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
/// 功能	 :	移除全部节点
/// 参数	 :	pHandle				[in] 句柄
/// 返回值: 
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
/// 功能	 :	获取当前节点的数量
/// 参数	 :	pHandle				[in]  句柄
/// 返回值: 
/// </summary> 
int hash_GetSize(void* pHandle)
{
	if (pHandle == 0)
		return eAEC_Err;

	AigHashHanle* pHashHandle = (AigHashHanle*)pHandle;
	return pHashHandle->Size;
}

/// <summary>
/// 功能	 :	遍历前重置
/// 参数	 :	pHandle				[in]  句柄
/// 返回值: 
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
/// 功能	 :	遍历下一个
/// 参数	 :	pHandle				[in]  句柄
///			out_pKey			[out] 关键字
///			out_pValue			[out] 值
/// 返回值: 
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

	//获取节点
	for (int i = 0; i < pHashHandle->SeekSubIndex && pCurrent != NULL; i++)
		pCurrent = pCurrent->pNext;

	//循环取到下一个正确节点
	while (pCurrent == NULL)
	{
		if (pHashHandle->SeekIndex == pHashHandle->Capacity - 1)
			return eAEC_End;

		pHashHandle->SeekSubIndex = 0;
		pHashHandle->SeekIndex++;

		pEntry = pHashHandle->pEntry[pHashHandle->SeekIndex];
		pCurrent = pEntry;
	}

	//赋值
	memcpy(pHashHandle->pSeekKey, pCurrent->pKey, pHashHandle->KeyLen);
	*out_pKey = pHashHandle->pSeekKey;
	if (out_pValue)
		*out_pValue = pCurrent->pValue;

	//指向下一个
	pHashHandle->SeekSubIndex++;
	return eAEC_Success;
}

/// <summary>
/// 功能	 :	查找
/// 参数	 :	pHandle				[in] 句柄
///			pKey				[in] 关键字
/// 返回值: 
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


//********************************字符串哈希算法********************************
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




