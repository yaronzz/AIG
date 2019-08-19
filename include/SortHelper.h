#if !defined __AIG_SORT_H__
#define __AIG_SORT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"


/// <summary>
/// ����	 :	ð������(��С����)
/// ����	 :	pArrary			[in-out] Ԫ������
///			arrary_num		[in]	 Ԫ�ظ���
///			element_size	[in]	 Ԫ�ش�С
///			in_pCmpFunc		[in]	 Ԫ�رȽϻص�����
/// ����ֵ: 
/// </summary>
int sort_Bubble(void* pArrary, int Arrary_num, int Element_size, pfn_AIG_CMP_CALLBACK in_pCmpFunc);

/// <summary>
/// ����	 :	��������(��С����)
/// ����	 :	pArrary			[in-out] Ԫ������
///			arrary_num		[in]	 Ԫ�ظ���
///			element_size	[in]	 Ԫ�ش�С
///			in_pCmpFunc		[in]	 Ԫ�رȽϻص�����
/// ����ֵ: 
/// </summary>
int sort_Insertion(void* pArrary, int Arrary_num, int Element_size, pfn_AIG_CMP_CALLBACK in_pCmpFunc);
       
/// <summary>
/// ����	 :	���ֲ�������(��С����)
/// ����	 :	pArrary			[in-out] Ԫ������
///			arrary_num		[in]	 Ԫ�ظ���
///			element_size	[in]	 Ԫ�ش�С
///			in_pCmpFunc		[in]	 Ԫ�رȽϻص�����
/// ����ֵ: 
/// </summary>
int sort_BinaryInsertion(void* pArrary, int Arrary_num, int Element_size, pfn_AIG_CMP_CALLBACK in_pCmpFunc);

/// <summary>
/// ����	 :	ϣ������(��С����)
/// ����	 :	pArrary			[in-out] Ԫ������
///			arrary_num		[in]	 Ԫ�ظ���
///			element_size	[in]	 Ԫ�ش�С
///			in_pCmpFunc		[in]	 Ԫ�رȽϻص�����
/// ����ֵ: 
/// </summary>
int sort_Shell(void* pArrary, int Arrary_num, int Element_size, pfn_AIG_CMP_CALLBACK in_pCmpFunc);
#ifdef __cplusplus
}
#endif

#endif  //__AIG_SORT_H__