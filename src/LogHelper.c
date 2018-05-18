#include "TimeHelper.h"
#include "MutexHelper.h"
#include "LogHelper.h"

typedef struct _AigLogHandle
{
	FILE* pFD;
	void* pMutex;
}AigLogHandle;

/// <summary>
/// 功能	 :	日志互斥锁
/// </summary>
static void* g_pLogMutex = NULL;

/// <summary>
/// 功能	 :	输出到日志文件
/// 参数	 :	pLogFileName			[in] 日志文件名
///			pFormt					[in] 参数格式
/// 返回值: 
/// </summary>
int log_WriteToFile(char* pLogFileName, const char* pFormt, ...)
{
	if (pLogFileName == NULL || pFormt == NULL)
		return eAEC_Input;

	FILE* FP;
	va_list ap;
	int iBuffLen;
	char sBuff[2048];
	AigSystemTime aAigTime;
	
	//上锁
	if (g_pLogMutex == NULL)
	{
		if (eAEC_AlreadyExist == mutex_Creat(&g_pLogMutex, pLogFileName))
			mutex_Open(&g_pLogMutex, pLogFileName);
	}

	if (mutex_LockByTime(g_pLogMutex, 1000) == eAEC_TimeOut)
		return eAEC_Err;

	//打开文件
	if ((FP = fopen(pLogFileName, "a+")) == NULL)
	{
		mutex_UnLock(g_pLogMutex);
		return eAEC_Open;
	}

	//获取时间
	time_GetCurrentTime(&aAigTime);
	time_AigSysTime2String(&aAigTime, sBuff, sizeof(sBuff), eAT2SType_T3);
	fprintf(FP, "[%s] ", sBuff);

	//写日志
	memset(sBuff, 0x00, sizeof(sBuff));
	va_start(ap, pFormt);
	iBuffLen = vsnprintf(sBuff, sizeof(sBuff), pFormt, ap);
	va_end(ap);

	fwrite(sBuff, strlen(sBuff), 1, FP);
	fputc('\n', FP);
	fflush(FP);
	fclose(FP);

	//解锁
	mutex_UnLock(g_pLogMutex);
	return eAEC_Success;
}


/// <summary>
/// 功能	 :	打开日志文件
/// 参数	 :	pLogFileName			[in]	 日志文件名
///			pHandle					[in-out] 句柄
///			bIsClear				[in]	 是否清空日志
/// 返回值: 
/// </summary>
int log_Open(char* pLogFileName, void** pHandle, int bIsClear)
{
	if (pLogFileName == NULL || pHandle == NULL)
		return eAEC_Input;

	FILE* FP;
	void* pMutex;

	//打开文件
	if (bIsClear == AIG_TRUE)
		FP = fopen(pLogFileName, "w+");
	else
		FP = fopen(pLogFileName, "a+");
	if (FP == NULL)
		return eAEC_Open;

	//创建互斥量
	if (mutex_Creat(&pMutex, NULL) != eAEC_Success)
	{
		fclose(FP);
		return eAEC_Err;
	}

	//赋值
	AigLogHandle* pLogHandle = (AigLogHandle*)malloc(sizeof(AigLogHandle));
	pLogHandle->pFD = FP;
	pLogHandle->pMutex = pMutex;

	return eAEC_Success;
}

/// <summary>
/// 功能	 :	关闭日志文件
/// 返回值: 
/// </summary>
void log_Close(void** pHandle)
{
	if (pHandle != NULL && *pHandle != NULL)
	{
		AigLogHandle* pLogHandle = (AigLogHandle*)pHandle;
		fclose(pLogHandle->pFD);
		mutex_Close(pLogHandle->pMutex);
		free(pLogHandle);
		*pHandle = NULL;
	}
}

/// <summary>
/// 功能	 :	输出日志
/// 参数	 :	pHandle					[in] 句柄
///			pFormt					[in] 格式
/// 返回值: 
/// </summary>
int log_Write(void* pHandle, const char* pFormt, ...)
{
	if (pHandle == NULL || pFormt == NULL)
		return eAEC_Input;

	AigLogHandle* pLogHandle = (AigLogHandle*)pHandle;
	va_list ap;
	int iBuffLen;
	char sBuff[2048];
	AigSystemTime aAigTime;

	//加锁
	mutex_Lock(pLogHandle->pMutex);

	//获取时间
	time_GetCurrentTime(&aAigTime);
	time_AigSysTime2String(&aAigTime, sBuff, sizeof(sBuff), eAT2SType_T3);
	fprintf(pLogHandle->pFD, "[%s] ", sBuff);

	//写日志
	memset(sBuff, 0x00, sizeof(sBuff));
	va_start(ap, pFormt);
	iBuffLen = vsnprintf(sBuff, sizeof(sBuff), pFormt, ap);
	va_end(ap);

	fwrite(sBuff, strlen(sBuff), 1, pLogHandle->pFD);
	fputc('\n', pLogHandle->pFD);
	fflush(pLogHandle->pFD);

	//解锁
	mutex_UnLock(pLogHandle->pMutex);
	return eAEC_Success;
}