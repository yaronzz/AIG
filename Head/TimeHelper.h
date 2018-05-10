#if !defined __AIG_COMMON_H__
#define __AIG_COMMON_H__


#include "DefHelper.h"

typedef struct _AigSystemTime
{
	unsigned short Year;			//��
	unsigned short Month;			//��
	unsigned short Day;				//��
	unsigned short DayOfWeek;		//�ܼ�
	unsigned short Hour;			//ʱ
	unsigned short Minute;			//��
	unsigned short Second;			//��
	unsigned short Milliseconds;	//����
}AigSystemTime;

/// <summary>
/// ����	 :	��ȡÿ���µ���������
/// ����	 :	bIsLeapYear	 [in] �Ƿ�Ϊ����
///			iMonth		 [in] �·�
/// ����ֵ:
/// </summary>
int time_GetMonthDayNum(int bIsLeapYear, int iMonth);

/// <summary>
/// ����	 :	�Ƿ�Ϊ����
/// ����	 :	iYear	 [in] ���
/// ����ֵ:
/// </summary>
int time_IsLeapYear(int iYear);

/// <summary>
/// ����	 :	�����1970��1��1�յ� xx��1��1�յ�����
/// ����	 :	in_lYear	 [in] ���
/// ����ֵ:
/// </summary>
int time_GetUTCDayNum(int in_lYear);




/// <summary>
/// ����	 :	FILETIMEתpTimet
/// ����	 :	aFileTime		 [in] FILETIME
///			pTimet			 [out]pTimet
/// ����ֵ:
/// </summary>
void  time_FileTime2TimeT(FILETIME aFileTime, time_t* pTimet);

/// <summary>
/// ����	 :	Time_TתAigSystemTime
/// ����	 :	ulTimestamp	 [in] Time_T
///			out_pTime	 [out]AigSystemTime
/// ����ֵ:
/// </summary>
int time_TimeT2AigSystemTime(time_t aTimet, AigSystemTime* pAigTime);

/// <summary>
/// ����	 :	FILETIMEתAigSystemTime
/// ����	 :	aFileTime		 [in] FILETIME
///			pAigTime		 [out]AigSystemTime
/// ����ֵ:
/// </summary>
void time_FileTime2AigSystemTime(FILETIME aFileTime, AigSystemTime* pAigTime);

#ifdef __cplusplus
extern "C" {
#endif

#endif



