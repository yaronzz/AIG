#include "MutexHelper.h"

/// <summary>
/// 功能	 :	创建互斥锁
/// 参数	 :	pHandle			[in-out] 句柄
///			pMutexName		[in]	 互斥量名称,用于进程间互斥
/// 返回值: 
/// </summary>
int mutex_Creat(void** pHandle, char* pMutexName)
{
	if (pHandle == NULL)
		return eAEC_Input;

#ifdef _WIN32
	HANDLE hMutex = CreateMutex(NULL, FALSE, pMutexName);
	DWORD dwRet = GetLastError();
	if (hMutex == NULL || ERROR_ALREADY_EXISTS == dwRet)
	{
		CloseHandle(hMutex);
		return eAEC_AlreadyExist;
	}

	*pHandle = hMutex;
	return eAEC_Success;
#endif

	return eAEC_Err;
}

/// <summary>
/// 功能	 :	打开互斥锁
/// 参数	 :	pHandle			[in-out] 句柄
///			pMutexName		[in]	 互斥量名称,用于进程间互斥
/// 返回值: 
/// </summary>
int mutex_Open(void** pHandle, char* pMuetexName)
{
	if (pHandle == NULL)
		return eAEC_Input;

#ifdef _WIN32
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, pMuetexName);
	if (hMutex == NULL)
	{
		CloseHandle(hMutex);
		return eAEC_Err;
	}

	*pHandle = hMutex;
	return eAEC_Success;
#endif

	return eAEC_Err;
}

/// <summary>
/// 功能	 :	关闭互斥锁
/// 参数	 :	pHandle			[in-out] 句柄
/// 返回值: 
/// </summary>
void mutex_Close(void** pHandle)
{
	if (*pHandle != NULL)
	{
#ifdef _WIN32
		CloseHandle(*pHandle);
		*pHandle = NULL;
#endif
	}
}

/// <summary>
/// 功能	 :	上锁
/// 参数	 :	pHandle			[in] 句柄
///			iMilliseconds	[in] 等待时间（毫秒）
/// 返回值: 
/// </summary>
int mutex_LockByTime(void* pHandle, unsigned long lMilliseconds)
{
#ifdef _WIN32
	DWORD dwRet = WaitForSingleObject(pHandle, lMilliseconds);
	if (dwRet == WAIT_TIMEOUT)
		return eAEC_TimeOut;
#endif

	return eAEC_Success;
}

/// <summary>
/// 功能	 :	上锁
/// 参数	 :	pHandle			[in] 句柄
/// 返回值: 
/// </summary>
int mutex_Lock(void* pHandle)
{

#ifdef _WIN32
	return mutex_LockByTime(pHandle, INFINITE);
#endif

	return eAEC_Err;
}

/// <summary>
/// 功能	 :	解锁
/// 参数	 :	pHandle			[in] 句柄
/// 返回值: 
/// </summary>
int mutex_UnLock(void* pHandle)
{

#ifdef _WIN32
	ReleaseMutex(pHandle);
#endif

	return eAEC_Success;
}

