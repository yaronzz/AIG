#if !defined __AIG_MUTEX_H__
#define __AIG_MUTEX_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"

/// <summary>
/// 功能	 :	创建互斥锁
/// 参数	 :	pHandle			[in-out] 句柄
///			pMutexName		[in]	 互斥量名称,用于进程间互斥
/// 返回值: 
/// </summary>
int mutex_Creat(void** pHandle, char* pMutexName);

/// <summary>
/// 功能	 :	打开互斥锁
/// 参数	 :	pHandle			[in-out] 句柄
///			pMutexName		[in]	 互斥量名称,用于进程间互斥
/// 返回值: 
/// </summary>
int mutex_Open(void** pHandle, char* pMuetexName);

/// <summary>
/// 功能	 :	关闭互斥锁
/// 参数	 :	pHandle			[in-out] 句柄
/// 返回值: 
/// </summary>
void mutex_Close(void** pHandle);

/// <summary>
/// 功能	 :	上锁
/// 参数	 :	pHandle			[in] 句柄
/// 返回值: 
/// </summary>
int mutex_Lock(void* pHandle);

/// <summary>
/// 功能	 :	上锁
/// 参数	 :	pHandle			[in] 句柄
///			iMilliseconds	[in] 等待时间（毫秒）
/// 返回值: 
/// </summary>
int mutex_LockByTime(void* pHandle, unsigned long lMilliseconds);

/// <summary>
/// 功能	 :	解锁
/// 参数	 :	pHandle			[in] 句柄
/// 返回值: 
/// </summary>
int mutex_UnLock(void* pHandle);

#ifdef __cplusplus
}
#endif

#endif //__AIG_MUTEX_H__



