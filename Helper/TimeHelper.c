#include<time.h>

#include "TimeHelper.h"


static int AIG_MONTHDAYS[2][13] = {
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 },		//����
};

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
		return AIG_MONTHDAYS[1][iMonth];

	return AIG_MONTHDAYS[0][iMonth];
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
		if (time_GetMonthDayNum(time_IsLeapYear((int)lYear), i) > lTemp)
		{
			lMon = i;
			lDay = lTemp - time_GetMonthDayNum(time_IsLeapYear((int)lYear), i - 1) + 1;
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