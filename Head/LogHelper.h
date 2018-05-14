#if !defined __AIG_LOG_H__
#define __AIG_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"
#include "TimeHelper.h"
#include "MutexHelper.h"
/// <summary>
/// ����	 :	�������־�ļ�
/// ����	 :	pLogFileName			[in] ��־�ļ���
///			pFormt					[in] ������ʽ
/// ����ֵ: 
/// </summary>
int log_WriteToFile(char* pLogFileName, const char* pFormt, ...);

/// <summary>
/// ����	 :	����־�ļ�
/// ����	 :	pLogFileName			[in]	 ��־�ļ���
///			pHandle					[in-out] ���
///			bIsClear				[in]	 �Ƿ������־
/// ����ֵ: 
/// </summary>
int log_Open(char* pLogFileName, void** pHandle, int bIsClear);

/// <summary>
/// ����	 :	�ر���־�ļ�
/// ����ֵ: 
/// </summary>
void log_Close(void** pHandle);

/// <summary>
/// ����	 :	�����־
/// ����	 :	pHandle					[in] ���
///			pFormt					[in] ��ʽ
/// ����ֵ: 
/// </summary>
int log_Write(void* pHandle, const char* pFormt, ...);

#ifdef __cplusplus
}
#endif

#endif  //__AIG_LOG_H__