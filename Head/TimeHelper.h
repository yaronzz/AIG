#if !defined __AIG_COMMON_H__
#define __AIG_COMMON_H__


#include "DefHelper.h"

typedef struct _AigSystemTime
{
	unsigned short Year;			//年
	unsigned short Month;			//月
	unsigned short Day;				//日
	unsigned short DayOfWeek;		//周几
	unsigned short Hour;			//时
	unsigned short Minute;			//分
	unsigned short Second;			//秒
	unsigned short Milliseconds;	//毫秒
}AigSystemTime;

/// <summary>
/// 功能	 :	获取每个月的日子数量
/// 参数	 :	bIsLeapYear	 [in] 是否为闰年
///			iMonth		 [in] 月份
/// 返回值:
/// </summary>
int time_GetMonthDayNum(int bIsLeapYear, int iMonth);

/// <summary>
/// 功能	 :	是否为闰年
/// 参数	 :	iYear	 [in] 年份
/// 返回值:
/// </summary>
int time_IsLeapYear(int iYear);

/// <summary>
/// 功能	 :	计算从1970年1月1日到 xx年1月1日的天数
/// 参数	 :	in_lYear	 [in] 年份
/// 返回值:
/// </summary>
int time_GetUTCDayNum(int in_lYear);




/// <summary>
/// 功能	 :	FILETIME转pTimet
/// 参数	 :	aFileTime		 [in] FILETIME
///			pTimet			 [out]pTimet
/// 返回值:
/// </summary>
void  time_FileTime2TimeT(FILETIME aFileTime, time_t* pTimet);

/// <summary>
/// 功能	 :	Time_T转AigSystemTime
/// 参数	 :	ulTimestamp	 [in] Time_T
///			out_pTime	 [out]AigSystemTime
/// 返回值:
/// </summary>
int time_TimeT2AigSystemTime(time_t aTimet, AigSystemTime* pAigTime);

/// <summary>
/// 功能	 :	FILETIME转AigSystemTime
/// 参数	 :	aFileTime		 [in] FILETIME
///			pAigTime		 [out]AigSystemTime
/// 返回值:
/// </summary>
void time_FileTime2AigSystemTime(FILETIME aFileTime, AigSystemTime* pAigTime);

#ifdef __cplusplus
extern "C" {
#endif

#endif



