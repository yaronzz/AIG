#if !defined __AIG_TIME_H__
#define __AIG_TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

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

typedef enum _enumAigTime2StringType
{
	eAT2SType_T1,					//20170710 113000
	eAT2SType_T2,					//2017-07-10 11-30-00
	eAT2SType_T3,					//2017-07-10 11:30:00
	eAT2SType_T4,					//2017年07月10日 11:30:00
	eAT2SType_T5,					///2017年07月10日 11点30分00秒
}enumAigTime2StringType;

typedef struct _AigTimingHandle
{
	char bStart;					//开始计时

#ifdef _WIN32
	LARGE_INTEGER StartTime;		//开始时间点
#elif defined(linux) || defined(__LUNX)
	struct timeval StartTime;		//开始时间点
#endif

}AigTimingHandle;


/// <summary>
/// 功能	 :	获取当前时间
/// 参数	 :	pTime		[out] 当前时间
/// 返回值:
/// </summary>
int time_GetCurrentTime(AigSystemTime* pTime);

/// <summary>
/// 功能	 :	获取每个月的日子数量
/// 参数	 :	bIsLeapYear	 [in] 是否为闰年
///			iMonth		 [in] 月份
/// 返回值:
/// </summary>
int time_GetMonthDayNum(int bIsLeapYear, int iMonth);

/// <summary>
/// 功能	 :	是否为闰年
/// 参数	 :	iYear		[in] 年份
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
void  time_FileTime2TimeT(void* aFileTime, time_t* pTimet);

/// <summary>
/// 功能	 :	Time_T转AigSystemTime
/// 参数	 :	ulTimestamp		[in] Time_T
///			out_pTime		[out]AigSystemTime
/// 返回值:
/// </summary>
int time_TimeT2AigSystemTime(time_t aTimet, AigSystemTime* pAigTime);

/// <summary>
/// 功能	 :	FILETIME转AigSystemTime
/// 参数	 :	aFileTime		 [in] FILETIME
///			pAigTime		 [out]AigSystemTime
/// 返回值:
/// </summary>
void time_FileTime2AigSystemTime(void* aFileTime, AigSystemTime* pAigTime);

/// <summary>
/// 功能	 :	AigSystemTime转字符串
/// 参数	 :	pAigTime		 [in] 时间
///			pString			 [out]输出字符串
///			iStringlen		 [in] 输出字符串长度
///			eType			 [in] 类型
/// 返回值:
/// </summary>
int time_AigSysTime2String(AigSystemTime* pAigTime, char* pString, int iStringlen, enumAigTime2StringType eType);



/// <summary>
/// 功能	 :  开始计时
/// 参数	 :	pHandle      [out] 计时句柄 
/// 返回值:  
/// </summary>
int time_StartAsyn(AigTimingHandle* pHandle);

/// <summary>
/// 功能	 :	结束计时
/// 参数	 :	pHandl		[in] 计时句柄
/// 返回值:  微秒
/// </summary>
long time_EndAsyn(AigTimingHandle* pHandle);

/// <summary>
/// 功能	 :  开始计时
/// 参数	 :	
/// 返回值:  
/// </summary>
void time_Start();

/// <summary>
/// 功能	 :	结束计时
/// 参数	 :	
/// 返回值:  微秒
/// </summary>
long time_End();


#ifdef __cplusplus
extern "C" {
#endif

#endif //__AIG_TIME_H__



