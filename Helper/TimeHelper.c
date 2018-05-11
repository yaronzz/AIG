#include "TimeHelper.h"

/// <summary>
/// ����	 :  ��ʱ���ڴ滺��
/// </summary>
static AigTimingHandle g_TimingHandle;

/// <summary>
/// ����	 :  ÿ���·��Ѿ���ȥ����������
/// </summary>
static int AIG_MONTHDAYS[2][13] = {
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 },		//����
};

/// <summary>
/// ����	 :	��ȡ��ǰʱ��
/// ����	 :	pTime		[out] ��ǰʱ��
/// ����ֵ:
/// </summary>
int time_GetCurrentTime(AigSystemTime* pTime)
{
	if (pTime == NULL)
		return eAEC_Input;

	time_t aRawTime;
	time(&aRawTime);
	time_TimeT2AigSystemTime(aRawTime, pTime);
	return eAEC_Success;
}

/// <summary>
/// ����	 :	��ȡÿ���µ���������
/// ����	 :	bIsLeapYear	 [in] �Ƿ�Ϊ����
///			iMonth		 [in] �·�
/// ����ֵ:
/// </summary>
int time_GetMonthDayNum(int bIsLeapYear, int iMonth)
{
	if (iMonth <= 0 || iMonth > 12)
		return 0;

	if (bIsLeapYear != AIG_FALSE)
		return AIG_MONTHDAYS[1][iMonth] - AIG_MONTHDAYS[1][iMonth - 1];

	return AIG_MONTHDAYS[0][iMonth] - AIG_MONTHDAYS[0][iMonth - 1];
}

/// <summary>
/// ����	 :	�Ƿ�Ϊ����
/// ����	 :	iYear	 [in] ���
/// ����ֵ:
/// </summary>
int time_IsLeapYear(int iYear)
{
	if ((iYear % 4 == 0) && (iYear % 100 != 0) || (iYear % 400 == 0))
		return AIG_TRUE;
	return AIG_FALSE;
}

/// <summary>
/// ����	 :	�����1970��1��1�յ� xx��1��1�յ�����
/// ����	 :	in_lYear	 [in] ���
/// ����ֵ:
/// </summary>
int time_GetUTCDayNum(int in_lYear)
{
	in_lYear -= 1;
	return in_lYear * 365 + (in_lYear / 4 - in_lYear / 100 + in_lYear / 400) - 719162;
}




/// <summary>
/// ����	 :	FILETIMEתpTimet
/// ����	 :	aFileTime		 [in] FILETIME
///			pTimet			 [out]pTimet
/// ����ֵ:
/// </summary>
void time_FileTime2TimeT(void* aFileTime, time_t* pTimet)
{
#ifdef _WIN32
	LONGLONG lTemp = 0;
	ULARGE_INTEGER ui;
	FILETIME* pFileTime = (FILETIME*)aFileTime;

	ui.LowPart	= pFileTime->dwLowDateTime;
	ui.HighPart = pFileTime->dwHighDateTime;
	lTemp		= ((LONGLONG)pFileTime->dwHighDateTime << 32) + pFileTime->dwLowDateTime;
	*pTimet		= ((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
#endif
}

/// <summary>
/// ����	 :	Time_TתAigSystemTime
/// ����	 :	aTimet		 [in] Time_T
///			pAigTime	 [out]AigSystemTime
/// ����ֵ:
/// </summary>
int time_TimeT2AigSystemTime(time_t aTimet, AigSystemTime* pAigTime)
{
	long long lTemp = 0;
	long long lYear = 0;
	long long lMon = 0;
	long long lDay = 0;
	long long lHour = 0;
	long long lMin = 0;
	long long lSec = 0;
	long long lWeekDay = 0;
	long long lDayCount = 0;
	long long lYearCount = 0;

	aTimet += 8 * 3600;					// ʱ���ȼ�8Сʱת��Ϊ����ʱ��

	lTemp = aTimet % 86400;				// ������(24*3600)����
	lHour = lTemp / 3600;				// ʱ
	lTemp = lTemp % 3600;
	lMin = lTemp / 60;					// ��
	lSec = lTemp % 60;					// ��

	lDayCount = aTimet / 86400;			// ��1970.1.1��in_ulUTC������
	lWeekDay = (lDayCount + 4) % 7;		// ���ڼ�
	lYearCount = lDayCount / 365;		// ���µ�����
	lYear = lYearCount + 1970;
	while (1)
	{
		if (time_GetUTCDayNum((int)lYear) > lDayCount)
			break;
		lYear++;
	}
	lYear -= 1;

	lTemp = lDayCount - time_GetUTCDayNum((int)lYear);
	for (int i = 0; i < 13; i++)
	{
		if (AIG_MONTHDAYS[time_IsLeapYear((int)lYear)][i] > lTemp)
		{
			lMon = i;
			lDay = lTemp - AIG_MONTHDAYS[time_IsLeapYear((int)lYear)][i - 1] + 1;
			break;
		}
	}

	pAigTime->Year			= (unsigned short)lYear;
	pAigTime->Month			= (unsigned short)lMon;
	pAigTime->Day			= (unsigned short)lDay;
	pAigTime->Hour			= (unsigned short)lHour;
	pAigTime->Minute		= (unsigned short)lMin;
	pAigTime->Second		= (unsigned short)lSec;
	pAigTime->DayOfWeek		= (unsigned short)lWeekDay;
	pAigTime->Milliseconds	= 0;
	return eAEC_Success;
}

/// <summary>
/// ����	 :	FILETIMEתAigSystemTime
/// ����	 :	aFileTime		 [in] FILETIME
///			pAigTime		 [out]AigSystemTime
/// ����ֵ:
/// </summary>
void time_FileTime2AigSystemTime(void* aFileTime, AigSystemTime* pAigTime)
{
	time_t aTimeT;
	time_FileTime2TimeT(aFileTime, &aTimeT);
	time_TimeT2AigSystemTime(aTimeT, pAigTime);
}

static void time_ZeroFill(char* pTmp, int iNum)
{
	*pTmp = ((iNum) % 10) + '0';
}

/// <summary>
/// ����	 :	AigSystemTimeת�ַ���
/// ����	 :	pAigTime		 [in] ʱ��
///			pString			 [out]����ַ���
///			iStringlen		 [in] ����ַ�������
///			eType			 [in] ����
/// ����ֵ:
/// </summary>
int time_AigSysTime2String(AigSystemTime* pAigTime, char* pString, int iStringlen, enumAigTime2StringType eType)
{
	char sYear[5];
	char sMonth[3];
	char sDay[3];
	char sHour[3];
	char sMinute[3];
	char sSecond[3];
	char sBuf[50] = "\0";

	memset(sYear, 0, sizeof(sYear));
	time_ZeroFill(sYear + 0, pAigTime->Year / 1000);
	time_ZeroFill(sYear + 1, pAigTime->Year / 100);
	time_ZeroFill(sYear + 2, pAigTime->Year / 10);
	time_ZeroFill(sYear + 3, pAigTime->Year);

	memset(sMonth, 0, sizeof(sMonth));
	time_ZeroFill(sMonth + 0, pAigTime->Month / 10);
	time_ZeroFill(sMonth + 1, pAigTime->Month);

	memset(sDay, 0, sizeof(sDay));
	time_ZeroFill(sDay + 0, pAigTime->Day / 10);
	time_ZeroFill(sDay + 1, pAigTime->Day);

	memset(sHour, 0, sizeof(sHour));
	time_ZeroFill(sHour + 0, pAigTime->Hour / 10);
	time_ZeroFill(sHour + 1, pAigTime->Hour);

	memset(sMinute, 0, sizeof(sMinute));
	time_ZeroFill(sMinute + 0, pAigTime->Minute / 10);
	time_ZeroFill(sMinute + 1, pAigTime->Minute);

	memset(sSecond, 0, sizeof(sSecond));
	time_ZeroFill(sSecond + 0, pAigTime->Second / 10);
	time_ZeroFill(sSecond + 1, pAigTime->Second);

	switch (eType)
	{
	case eAT2SType_T1://20170710 113000
		sprintf(sBuf, "%s%s%s %s%s%s", sYear, sMonth, sDay, sHour, sMinute, sSecond);
		break;
	case eAT2SType_T2://2017-07-10 11-30-00
		sprintf(sBuf, "%s-%s-%s %s-%s-%s", sYear, sMonth, sDay, sHour, sMinute, sSecond);
		break;
	case eAT2SType_T3://2017-07-10 11:30:00
		sprintf(sBuf, "%s-%s-%s %s:%s:%s", sYear, sMonth, sDay, sHour, sMinute, sSecond);
		break;
	case eAT2SType_T4://2017��07��10�� 11:30:00
		sprintf(sBuf, "%s��%s��%s�� %s:%s:%s", sYear, sMonth, sDay, sHour, sMinute, sSecond);
		break;
	case eAT2SType_T5://2017��07��10�� 11��30��00��
		sprintf(sBuf, "%s��%s��%s�� %s��%s��%s��", sYear, sMonth, sDay, sHour, sMinute, sSecond);
		break;
	}

	int iLen = strlen(sBuf) + 1;
	if (iLen > iStringlen)
		return eAEC_BufferOver;

	memcpy(pString, sBuf, iLen);
	return eAEC_Success;
}










/// <summary>
/// ����	 :  ��ʼ��ʱ
/// ����	 :	pHandle      [out] ��ʱ��� 
/// ����ֵ:  
/// </summary>
int time_StartAsyn(AigTimingHandle* pHandle)
{
	if (pHandle == NULL)
		return eAEC_Input;

	memset(pHandle, 0, sizeof(AigTimingHandle));
	pHandle->bStart = 1;

#ifdef _WIN32
	QueryPerformanceCounter(&pHandle->StartTime);
#elif defined(linux) || defined(__LUNX)
	gettimeofday(&pHandle->StartTime);
#endif

	return eAEC_Success;
}

/// <summary>
/// ����	 :	������ʱ
/// ����	 :	pHandl		[in] ��ʱ���
/// ����ֵ:  ΢��
/// </summary>
long time_EndAsyn(AigTimingHandle* pHandle)
{
	long lRet = 0;
	if (!pHandle->bStart)
		return 0;

#ifdef _WIN32
	LARGE_INTEGER aPerfFreq = { 0 };
	LARGE_INTEGER aNow = { 0 };

	QueryPerformanceFrequency(&aPerfFreq);
	QueryPerformanceCounter(&aNow);
	lRet = (long)(((aNow.QuadPart - pHandle->StartTime.QuadPart) * 1000000) / aPerfFreq.QuadPart);

#elif defined(linux) || defined(__LUNX)
	struct timeval aNow;

	gettimeofday(&aNow, NULL);
	lRet = aNow.tv_sec * 1000 * 1000 + aNow.tv_usec - (pHandle->StartTime.tv_sec * 1000 * 1000 + pHandle->StartTime.tv_usec);
#endif

	return lRet;
}

/// <summary>
/// ����	 :  ��ʼ��ʱ
/// ����	 :	
/// ����ֵ:  
/// </summary>
void time_Start()
{
	time_StartAsyn(&g_TimingHandle);
}

/// <summary>
/// ����	 :	������ʱ
/// ����	 :	
/// ����ֵ:  ΢��
/// </summary>
long time_End()
{
	return time_EndAsyn(&g_TimingHandle);
}



