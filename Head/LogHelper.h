#if !defined __AIG_LOG_H__
#define __AIG_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"
#include "TimeHelper.h"
#include "MutexHelper.h"
/// <summary>
/// 功能	 :	输出到日志文件
/// 参数	 :	pLogFileName			[in] 日志文件名
///			pFormt					[in] 参数格式
/// 返回值: 
/// </summary>
int log_WriteToFile(char* pLogFileName, const char* pFormt, ...);

/// <summary>
/// 功能	 :	打开日志文件
/// 参数	 :	pLogFileName			[in]	 日志文件名
///			pHandle					[in-out] 句柄
///			bIsClear				[in]	 是否清空日志
/// 返回值: 
/// </summary>
int log_Open(char* pLogFileName, void** pHandle, int bIsClear);

/// <summary>
/// 功能	 :	关闭日志文件
/// 返回值: 
/// </summary>
void log_Close(void** pHandle);

/// <summary>
/// 功能	 :	输出日志
/// 参数	 :	pHandle					[in] 句柄
///			pFormt					[in] 格式
/// 返回值: 
/// </summary>
int log_Write(void* pHandle, const char* pFormt, ...);

#ifdef __cplusplus
}
#endif

#endif  //__AIG_LOG_H__