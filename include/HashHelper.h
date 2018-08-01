#if !defined __AIG_HASH_H__
#define __AIG_HASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"

typedef int(*pfn_AIG_HASH_CALCHASH_CALLBACK)(void* pKey, int iKeyLen);		//�����ϣֵ

/// <summary>
/// ����	 :	������ϣ��
/// ����	 :	iKeyLen				[in] �ؼ��ֳ���
///			iValueLen			[in] ֵ����
///			iHashCapacity		[in] ����
///			pCmpFunc			[in] Key�ȽϺ���
///			pCalcHashFunc		[in] �����ϣֵ
/// ����ֵ: 
/// </summary> 
void* hash_Creat(int iKeyLen, int iValueLen, int iHashCapacity, pfn_AIG_CMP_CALLBACK pCmpFunc, pfn_AIG_HASH_CALCHASH_CALLBACK pCalcHashFunc);

/// <summary>
/// ����	 :	���ٹ�ϣ��
/// ����	 :	pHandle				[in-out] ���
/// ����ֵ: 
/// </summary> 
void hash_Destroy(void** pHandle);

/// <summary>
/// ����	 :	����ڵ�
/// ����	 :	pHandle				[in] ���
///			pKey				[in] �ؼ���
///			pValue				[in] ֵ
///			bIsReplace			[in] ����Ѵ����Ƿ��滻
/// ����ֵ: 
/// </summary> 
int hash_Insert(void* pHandle, void* pKey, void* pValue, int bIsReplace);

/// <summary>
/// ����	 :	�Ƴ��ڵ�
/// ����	 :	pHandle				[in] ���
///			pKey				[in] �ؼ���
/// ����ֵ: 
/// </summary> 
int hash_Remove(void* pHandle, void* pKey);

/// <summary>
/// ����	 :	�Ƴ�ȫ���ڵ�
/// ����	 :	pHandle				[in] ���
/// ����ֵ: 
/// </summary> 
int hash_RemoveAll(void* pHandle);

/// <summary>
/// ����	 :	��ȡ��ǰ�ڵ������
/// ����	 :	pHandle				[in]  ���
/// ����ֵ: 
/// </summary> 
int hash_GetSize(void* pHandle);

/// <summary>
/// ����	 :	����ǰ����
/// ����	 :	pHandle				[in]  ���
/// ����ֵ: 
/// </summary> 
int hash_SetOut(void* pHandle);

/// <summary>
/// ����	 :	������һ��
/// ����	 :	pHandle				[in]  ���
///			out_pKey			[out] �ؼ���
///			out_pValue			[out] ֵ
/// ����ֵ: 
/// </summary> 
int hash_GetNext(void* pHandle, void** out_pKey, void** out_pValue);

/// <summary>
/// ����	 :	����
/// ����	 :	pHandle				[in] ���
///			pKey				[in] �ؼ���
/// ����ֵ: 
/// </summary> 
void* hash_Find(void* pHandle, void* pKey);












#ifdef __cplusplus
}
#endif

#endif  //__AIG_HASH_H__