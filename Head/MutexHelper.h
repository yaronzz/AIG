#if !defined __AIG_MUTEX_H__
#define __AIG_MUTEX_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"

/// <summary>
/// ����	 :	����������
/// ����	 :	pHandle			[in-out] ���
///			pMutexName		[in]	 ����������,���ڽ��̼以��
/// ����ֵ: 
/// </summary>
int mutex_Creat(void** pHandle, char* pMutexName);

/// <summary>
/// ����	 :	�򿪻�����
/// ����	 :	pHandle			[in-out] ���
///			pMutexName		[in]	 ����������,���ڽ��̼以��
/// ����ֵ: 
/// </summary>
int mutex_Open(void** pHandle, char* pMuetexName);

/// <summary>
/// ����	 :	�رջ�����
/// ����	 :	pHandle			[in-out] ���
/// ����ֵ: 
/// </summary>
void mutex_Close(void** pHandle);

/// <summary>
/// ����	 :	����
/// ����	 :	pHandle			[in] ���
/// ����ֵ: 
/// </summary>
int mutex_Lock(void* pHandle);

/// <summary>
/// ����	 :	����
/// ����	 :	pHandle			[in] ���
///			iMilliseconds	[in] �ȴ�ʱ�䣨���룩
/// ����ֵ: 
/// </summary>
int mutex_LockByTime(void* pHandle, unsigned long lMilliseconds);

/// <summary>
/// ����	 :	����
/// ����	 :	pHandle			[in] ���
/// ����ֵ: 
/// </summary>
int mutex_UnLock(void* pHandle);

#ifdef __cplusplus
}
#endif

#endif //__AIG_MUTEX_H__



