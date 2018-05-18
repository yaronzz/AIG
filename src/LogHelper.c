#include "TimeHelper.h"
#include "MutexHelper.h"
#include "LogHelper.h"

typedef struct _AigLogHandle
{
	FILE* pFD;
	void* pMutex;
}AigLogHandle;

/// <summary>
/// ����	 :	��־������
/// </summary>
static void* g_pLogMutex = NULL;

/// <summary>
/// ����	 :	�������־�ļ�
/// ����	 :	pLogFileName			[in] ��־�ļ���
///			pFormt					[in] ������ʽ
/// ����ֵ: 
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
	
	//����
	if (g_pLogMutex == NULL)
	{
		if (eAEC_AlreadyExist == mutex_Creat(&g_pLogMutex, pLogFileName))
			mutex_Open(&g_pLogMutex, pLogFileName);
	}

	if (mutex_LockByTime(g_pLogMutex, 1000) == eAEC_TimeOut)
		return eAEC_Err;

	//���ļ�
	if ((FP = fopen(pLogFileName, "a+")) == NULL)
	{
		mutex_UnLock(g_pLogMutex);
		return eAEC_Open;
	}

	//��ȡʱ��
	time_GetCurrentTime(&aAigTime);
	time_AigSysTime2String(&aAigTime, sBuff, sizeof(sBuff), eAT2SType_T3);
	fprintf(FP, "[%s] ", sBuff);

	//д��־
	memset(sBuff, 0x00, sizeof(sBuff));
	va_start(ap, pFormt);
	iBuffLen = vsnprintf(sBuff, sizeof(sBuff), pFormt, ap);
	va_end(ap);

	fwrite(sBuff, strlen(sBuff), 1, FP);
	fputc('\n', FP);
	fflush(FP);
	fclose(FP);

	//����
	mutex_UnLock(g_pLogMutex);
	return eAEC_Success;
}


/// <summary>
/// ����	 :	����־�ļ�
/// ����	 :	pLogFileName			[in]	 ��־�ļ���
///			pHandle					[in-out] ���
///			bIsClear				[in]	 �Ƿ������־
/// ����ֵ: 
/// </summary>
int log_Open(char* pLogFileName, void** pHandle, int bIsClear)
{
	if (pLogFileName == NULL || pHandle == NULL)
		return eAEC_Input;

	FILE* FP;
	void* pMutex;

	//���ļ�
	if (bIsClear == AIG_TRUE)
		FP = fopen(pLogFileName, "w+");
	else
		FP = fopen(pLogFileName, "a+");
	if (FP == NULL)
		return eAEC_Open;

	//����������
	if (mutex_Creat(&pMutex, NULL) != eAEC_Success)
	{
		fclose(FP);
		return eAEC_Err;
	}

	//��ֵ
	AigLogHandle* pLogHandle = (AigLogHandle*)malloc(sizeof(AigLogHandle));
	pLogHandle->pFD = FP;
	pLogHandle->pMutex = pMutex;

	return eAEC_Success;
}

/// <summary>
/// ����	 :	�ر���־�ļ�
/// ����ֵ: 
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
/// ����	 :	�����־
/// ����	 :	pHandle					[in] ���
///			pFormt					[in] ��ʽ
/// ����ֵ: 
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

	//����
	mutex_Lock(pLogHandle->pMutex);

	//��ȡʱ��
	time_GetCurrentTime(&aAigTime);
	time_AigSysTime2String(&aAigTime, sBuff, sizeof(sBuff), eAT2SType_T3);
	fprintf(pLogHandle->pFD, "[%s] ", sBuff);

	//д��־
	memset(sBuff, 0x00, sizeof(sBuff));
	va_start(ap, pFormt);
	iBuffLen = vsnprintf(sBuff, sizeof(sBuff), pFormt, ap);
	va_end(ap);

	fwrite(sBuff, strlen(sBuff), 1, pLogHandle->pFD);
	fputc('\n', pLogHandle->pFD);
	fflush(pLogHandle->pFD);

	//����
	mutex_UnLock(pLogHandle->pMutex);
	return eAEC_Success;
}