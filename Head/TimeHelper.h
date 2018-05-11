#if !defined __AIG_TIME_H__
#define __AIG_TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

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

typedef enum _enumAigTime2StringType
{
	eAT2SType_T1,					//20170710 113000
	eAT2SType_T2,					//2017-07-10 11-30-00
	eAT2SType_T3,					//2017-07-10 11:30:00
	eAT2SType_T4,					//2017��07��10�� 11:30:00
	eAT2SType_T5,					///2017��07��10�� 11��30��00��
}enumAigTime2StringType;

typedef struct _AigTimingHandle
{
	char bStart;					//��ʼ��ʱ

#ifdef _WIN32
	LARGE_INTEGER StartTime;		//��ʼʱ���
#elif defined(linux) || defined(__LUNX)
	struct timeval StartTime;		//��ʼʱ���
#endif

}AigTimingHandle;


/// <summary>
/// ����	 :	��ȡ��ǰʱ��
/// ����	 :	pTime		[out] ��ǰʱ��
/// ����ֵ:
/// </summary>
int time_GetCurrentTime(AigSystemTime* pTime);

/// <summary>
/// ����	 :	��ȡÿ���µ���������
/// ����	 :	bIsLeapYear	 [in] �Ƿ�Ϊ����
///			iMonth		 [in] �·�
/// ����ֵ:
/// </summary>
int time_GetMonthDayNum(int bIsLeapYear, int iMonth);

/// <summary>
/// ����	 :	�Ƿ�Ϊ����
/// ����	 :	iYear		[in] ���
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
void  time_FileTime2TimeT(void* aFileTime, time_t* pTimet);

/// <summary>
/// ����	 :	Time_TתAigSystemTime
/// ����	 :	ulTimestamp		[in] Time_T
///			out_pTime		[out]AigSystemTime
/// ����ֵ:
/// </summary>
int time_TimeT2AigSystemTime(time_t aTimet, AigSystemTime* pAigTime);

/// <summary>
/// ����	 :	FILETIMEתAigSystemTime
/// ����	 :	aFileTime		 [in] FILETIME
///			pAigTime		 [out]AigSystemTime
/// ����ֵ:
/// </summary>
void time_FileTime2AigSystemTime(void* aFileTime, AigSystemTime* pAigTime);

/// <summary>
/// ����	 :	AigSystemTimeת�ַ���
/// ����	 :	pAigTime		 [in] ʱ��
///			pString			 [out]����ַ���
///			iStringlen		 [in] ����ַ�������
///			eType			 [in] ����
/// ����ֵ:
/// </summary>
int time_AigSysTime2String(AigSystemTime* pAigTime, char* pString, int iStringlen, enumAigTime2StringType eType);



/// <summary>
/// ����	 :  ��ʼ��ʱ
/// ����	 :	pHandle      [out] ��ʱ��� 
/// ����ֵ:  
/// </summary>
int time_StartAsyn(AigTimingHandle* pHandle);

/// <summary>
/// ����	 :	������ʱ
/// ����	 :	pHandl		[in] ��ʱ���
/// ����ֵ:  ΢��
/// </summary>
long time_EndAsyn(AigTimingHandle* pHandle);

/// <summary>
/// ����	 :  ��ʼ��ʱ
/// ����	 :	
/// ����ֵ:  
/// </summary>
void time_Start();

/// <summary>
/// ����	 :	������ʱ
/// ����	 :	
/// ����ֵ:  ΢��
/// </summary>
long time_End();


#ifdef __cplusplus
extern "C" {
#endif

#endif //__AIG_TIME_H__



