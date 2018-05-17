#include "MutexHelper.h"

/// <summary>
/// ����	 :	����������
/// ����	 :	pHandle			[in-out] ���
///			pMutexName		[in]	 ����������,���ڽ��̼以��
/// ����ֵ: 
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
/// ����	 :	�򿪻�����
/// ����	 :	pHandle			[in-out] ���
///			pMutexName		[in]	 ����������,���ڽ��̼以��
/// ����ֵ: 
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
/// ����	 :	�رջ�����
/// ����	 :	pHandle			[in-out] ���
/// ����ֵ: 
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
/// ����	 :	����
/// ����	 :	pHandle			[in] ���
///			iMilliseconds	[in] �ȴ�ʱ�䣨���룩
/// ����ֵ: 
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
/// ����	 :	����
/// ����	 :	pHandle			[in] ���
/// ����ֵ: 
/// </summary>
int mutex_Lock(void* pHandle)
{

#ifdef _WIN32
	return mutex_LockByTime(pHandle, INFINITE);
#endif

	return eAEC_Err;
}

/// <summary>
/// ����	 :	����
/// ����	 :	pHandle			[in] ���
/// ����ֵ: 
/// </summary>
int mutex_UnLock(void* pHandle)
{

#ifdef _WIN32
	ReleaseMutex(pHandle);
#endif

	return eAEC_Success;
}

