#if !defined __AIG_SEARCH_H__
#define __AIG_SEARCH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"

/// <summary>
/// ����	 :	˳�����
/// ����	 :	pArrary			[in]	 Ԫ������
///			arrary_num		[in]	 Ԫ�ظ���
///			element_size	[in]	 Ԫ�ش�С
///			pFindEle		[in]	 ���ҵ�Ԫ��
///			in_pCmpFunc		[in]	 Ԫ�رȽϻص�����
/// ����ֵ:  >= 0�ɹ�
/// </summary>
int search_Sequence(void* pArrary, int Arrary_num, int Element_size, void* pFindEle, pfn_AIG_CMP_CALLBACK in_pCmpFunc);

/// <summary>
/// ����	 :	���ֲ���
/// ����	 :	pArrary			[in]	 ˳��Ԫ������
///			arrary_num		[in]	 Ԫ�ظ���
///			element_size	[in]	 Ԫ�ش�С
///			pFindEle		[in]	 ���ҵ�Ԫ��
///			in_pCmpFunc		[in]	 Ԫ�رȽϻص�����
/// ����ֵ:  >= 0�ɹ�
/// </summary>
int search_Binary(void* pArrary, int Arrary_num, int Element_size, void* pFindEle, pfn_AIG_CMP_CALLBACK in_pCmpFunc);

#ifdef __cplusplus
}
#endif

#endif  //__AIG_SEARCH_H__