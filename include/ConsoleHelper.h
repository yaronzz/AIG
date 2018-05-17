#if !defined __AIG_CONSOLE_H__
#define __AIG_CONSOLE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"

/// <summary>
/// ����	 :	��ȡ�������
/// ����	 :	iX			[out] ����X
///			iY			[out] ����Y
/// ����ֵ: 
/// </summary>
int console_GetPositionXY(int* iX, int* iY);

/// <summary>
/// ����	 :	���ù������
/// ����	 :	iX			[in] ����X
///			iY			[in] ����Y
/// ����ֵ: 
/// </summary>
int console_SetPositionXY(int iX, int iY);

/// <summary>
/// ����	 :	��������ʼ��
/// ����	 :	pHandle			[in-out] ���
///			pDesc			[in]	 ����
///			iMaxNum			[in]	 �������
///			iOnlyText		[in]	 ֻ��ʾ�ı�
/// ����ֵ: 
/// </summary>
int console_ProgressOpen(void** pHandle, char* pDesc, int iMaxNum, int iOnlyText);

/// <summary>
/// ����	 :	�������ͷ�
/// ����	 :	pHandle			[in-out] ���
/// ����ֵ: 
/// </summary>
void console_ProgressClose(void** pHandle);

/// <summary>
/// ����	 :	ˢ�½�����
/// ����	 :	pHandle			[in] ���
///			CurNum			[in] ��ǰ����
/// ����ֵ: 
/// </summary>
void console_ProgressRefresh(void* pHandle, int CurNum);

#ifdef __cplusplus
}
#endif

#endif  //__AIG_CONSOLE_H__