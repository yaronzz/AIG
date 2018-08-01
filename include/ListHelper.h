#if !defined __AIG_LIST_H__
#define __AIG_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"


/// <summary>
/// ����	 :	�½�����
/// ����	 :	iRecordLen		[in] �ڵ����ݳ���
///			pCmpFunc		[in] ����ʱ�ıȽϺ���
/// ����ֵ: 
/// </summary> 
void* list_Creat(int iRecordLen, pfn_AIG_CMP_CALLBACK pCmpFunc);

/// <summary>
/// ����	 :	��������
/// ����	 :	pHandle			[in] ���
/// ����ֵ: 
/// </summary> 
void list_Destroy(void** pHandle);

/// <summary>
/// ����	 :	��ӽڵ�
/// ����	 :	pHandle			[in] ���
///			pRecord			[in] �ڵ�����
/// ����ֵ: 
/// </summary> 
int list_Add(void* pHandle, void* pRecord);

/// <summary>
/// ����	 :	����ڵ�
/// ����	 :	pHandle			[in] ���
///			pRecord			[in] �ڵ�����
///			iIndex			[in] �ڵ��±�
/// ����ֵ: 
/// </summary> 
int list_Insert(void* pHandle, void* pRecord, int iIndex);





/// <summary>
/// ����	 :	ɾ���ڵ�
/// ����	 :	pHandle			[in] ���
///			iIndex			[in] �ڵ��±�
/// ����ֵ: 
/// </summary> 
int list_Remove(void* pHandle, int iIndex);

/// <summary>
/// ����	 :	ɾ��ȫ���ڵ�
/// ����	 :	pHandle			[in] ���
/// ����ֵ: 
/// </summary> 
int list_RemoveAll(void* pHandle);




/// <summary>
/// ����	 :	��ȡ�ڵ�����
/// ����	 :	pHandle			[in] ���
/// ����ֵ: 
/// </summary> 
int list_GetSize(void* pHandle);

/// <summary>
/// ����	 :	��ȡ�ڵ�����
/// ����	 :	pHandle			[in] ���
///			iIndex			[in] �ڵ��±�
/// ����ֵ: 
/// </summary> 
void* list_GetAt(void* pHandle, int iIndex);

/// <summary>
/// ����	 :	���ҽڵ��±�
/// ����	 :	pHandle			[in] ���
///			pFind			[in] ���ҵĽڵ�
///			iOrder			[in] �ڼ���ƥ��Ľڵ�
/// ����ֵ: 
/// </summary> 
int list_Find(void* pHandle, void* pFind, int iOrder);



#ifdef __cplusplus
}
#endif

#endif  //__AIG_LIST_H__