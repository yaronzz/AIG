#if !defined __AIG_PROFILE_H__
#define __AIG_PROFILE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"
#include "StringHelper.h"
#include "PathHelper.h"
#include "FileHelper.h"

/// <summary>
/// 功能	 :	获取配置文件中的值
/// 参数	 :	pGroup				组名
///			pKey				关键字名
///			pDefault			默认值
///			pReturnString		输出字符串
///			iReturnStringLen	输出字符串长度
///			pProfilePath		文件路径
/// 返回值: 
/// </summary>
int   profile_GetString(char* pGroup, char* pKey, char* pDefault, char* pValue, int iValueLen, char* pProfilePath);
int   profile_GetInt(char* pGroup, char* pKey, int pDefault, char* pProfilePath);
float profile_GetFloat(char* pGroup, char* pKey, float pDefault, char* pProfilePath);

/// <summary>
/// 功能	 :	设置配置文件中的值
/// 参数	 :	pGroup				组名
///			pKey				关键字名
///			pValue				值
///			pProfilePath		文件路径
/// 返回值: 
/// </summary>
int profile_SetString(char* pGroup, char* pKey, char* pValue, char* pProfilePath);
int profile_SetInt(char* pGroup, char* pKey, int iValue, char* pProfilePath);
int profile_Setfloat(char* pGroup, char* pKey, float fValue, char* pProfilePath);

#ifdef __cplusplus
}
#endif

#endif  //__AIG_PROFILE_H__