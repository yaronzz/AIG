#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <time.h>
#include <io.h>
#include <direct.h>
#endif

#if defined(__linux) || defined(linux) || defined(__LYNX)
#include <unistd.h>
#include <dirent.h>
#include <stdarg.h>
#include <time.h>
#include <strings.h>
#include <sys/stat.h>
#endif

#include "StringHelper.h"
#include "PathHelper.h"
#include "FileHelper.h"
#include "ProfileHelper.h"


typedef enum _enumAigProfileLineType
{
	eAPLType_Comment,	//注释
	eAPLType_Group,		//组
	eAPLType_KeyValue,	//关键字和值
	eAPLType_UnKnown,	//未知
}enumAigProfileLineType;

/// <summary>
/// 功能	 :	解析行
/// 参数	 :	pLineBuf		行缓存
///			sName			关键字名
///			sValue			值
///			iNameLen		关键字名长度
///			iValueLen		值长度
/// 返回值: 
/// </summary>
static enumAigProfileLineType profile_ReadLine(char* pLineBuf, char* sName, char* sValue, int iNameLen, int iValueLen)
{
	//计算长度
	string_LeftTrim(pLineBuf, AIG_STRING_EMPTY);
	if (strlen(pLineBuf) == 0)
		return eAPLType_UnKnown;

	//查询是否为注释行
	if (pLineBuf[0] == '#')
		return eAPLType_Comment;
	//查看是否為組
	if (string_SubstringByInterval(pLineBuf, '[', ']', sName, iNameLen) == eAEC_Success)
		return eAPLType_Group;
	//查询是否为关键字和值行
	if (string_SubstringByChr(pLineBuf, '=', sName, iNameLen, sValue, iValueLen) == eAEC_Success)
		return eAPLType_KeyValue;

	return eAPLType_UnKnown;
}



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
int profile_GetString(char* pGroup, char* pKey, char* pDefault, char* pValue, int iValueLen, char* pProfilePath)
{
	if (pGroup == NULL || pKey == NULL || pValue == NULL || iValueLen <= 0 || pProfilePath == NULL)
		return eAEC_Input;

	FILE* pFD;
	int iLen;
	int iInGroup = 0;
	char sName[256];
	char sValue[256];
	char sBuf[2048];
	enumAigProfileLineType eLineType;

	//如果没找到则以默认值设置
	if (pDefault)
	{
		iLen = strlen(pDefault) + 1;
		iLen = iLen > iValueLen ? iValueLen : iLen;
		memcpy(pValue, pDefault, iLen);
	}

	//打开文件
	if ((pFD = fopen(pProfilePath, "r")) == NULL)
		return eAEC_Open;
	
	//循环读取行数据
	while (feof(pFD) == 0)
	{
		fgets(sBuf, sizeof(sBuf), pFD);
		eLineType = profile_ReadLine(sBuf, sName, sValue, sizeof(sName), sizeof(sValue));

		switch (eLineType)
		{
		case eAPLType_Comment:
			break;
		case eAPLType_Group:
			iInGroup = string_Stricmp(sName, pGroup) == 0 ? 1 : 0;
			break;
		case eAPLType_KeyValue:
			if (iInGroup)
			{
				if (string_Stricmp(sName, pKey) != 0)
					break;

				fclose(pFD);
				iLen = strlen(sValue) + 1;
				if (iLen > iValueLen)
					return eAEC_BufferOver;

				string_RightTrim(sValue, "\n");
				memcpy(pValue, sValue, iLen);
				return eAEC_Success;
			}
			break;
		case eAPLType_UnKnown:
			break;
		}
	}

	
	fclose(pFD);
	return eAEC_Err;
}

/// <summary>
/// 功能	 :	获取配置文件中的值
/// 参数	 :	pGroup				组名
///			pKey				关键字名
///			pDefault			默认值
///			pProfilePath		文件路径
/// 返回值: 
/// </summary>
int profile_GetInt(char* pGroup, char* pKey, int pDefault, char* pProfilePath)
{
	char sBuf[1024];
	if (profile_GetString(pGroup, pKey, NULL, sBuf, sizeof(sBuf), pProfilePath) == eAEC_Success)
		return atoi(sBuf);

	return pDefault;
}

/// <summary>
/// 功能	 :	获取配置文件中的值
/// 参数	 :	pGroup				组名
///			pKey				关键字名
///			pDefault			默认值
///			pProfilePath		文件路径
/// 返回值: 
/// </summary>
float profile_GetFloat(char* pGroup, char* pKey, float pDefault, char* pProfilePath)
{
	char sBuf[1024];
	if (profile_GetString(pGroup, pKey, NULL, sBuf, sizeof(sBuf), pProfilePath) == eAEC_Success)
		return atof(sBuf);

	return pDefault;
}

/// <summary>
/// 功能	 :	设置配置文件中的值
/// 参数	 :	pGroup				组名
///			pKey				关键字名
///			pValue				值
///			pProfilePath		文件路径
/// 返回值: 
/// </summary>
int profile_SetString(char* pGroup, char* pKey, char* pValue, char* pProfilePath)
{
	if (pGroup == NULL || pKey == NULL || pValue == NULL || pProfilePath == NULL)
		return eAEC_Input;

	FILE* pFD;
	FILE* pTempFD;
	int iAlreadySet = 0;
	int iInGroup = 0;
	char sName[256];
	char sValue[256];
	char sBuf[2048];
	enumAigProfileLineType eLineType;
	char sTempFilePath[AIG_MAXLEN_FILEPATH];

	//打开文件
	if ((pFD = fopen(pProfilePath, "a+")) == NULL)
		return eAEC_Open;

	//打开备份文件
	file_GetBakFilePath(pProfilePath, "-aigbak", sTempFilePath, sizeof(sTempFilePath));
	if ((pTempFD = fopen(sTempFilePath, "w+")) == NULL)
		return eAEC_Open;
	
	//循环读取行数据
	while (feof(pFD) == 0)
	{
		fgets(sBuf, sizeof(sBuf), pFD);

		if (!iAlreadySet)
		{
			eLineType = profile_ReadLine(sBuf, sName, sValue, sizeof(sName), sizeof(sValue));
			switch (eLineType)
			{
			case eAPLType_Comment:
				break;
			case eAPLType_Group:
				if (string_Stricmp(sName, pGroup) == 0)
					iInGroup = 1;
				else if (iInGroup)
				{
					fprintf(pTempFD, "%s=%s\n", sName, pValue);
					iAlreadySet = 1;
				}
				break;
			case eAPLType_KeyValue:
				if (iInGroup)
				{
					if (string_Stricmp(sName, pKey) != 0)
						break;

					sprintf(sBuf, "%s=%s\n", sName, pValue);
					iAlreadySet = 1;
				}
				break;
			case eAPLType_UnKnown:
				break;
			}
		}

		fwrite(sBuf, strlen(sBuf), 1, pTempFD);
	}

	//如果没有写进去，则在这里新增加
	if (!iAlreadySet)
	{
		fprintf(pTempFD, "[%s]\n", pGroup);
		fprintf(pTempFD, "%s=%s\n", pKey, pValue);
	}

	//文件重置
	fclose(pFD);
	fclose(pTempFD);
	remove(pProfilePath);
	rename(sTempFilePath, pProfilePath);

	return eAEC_Success;
}

/// <summary>
/// 功能	 :	设置配置文件中的值
/// 参数	 :	pGroup				组名
///			pKey				关键字名
///			pValue				值
///			pProfilePath		文件路径
/// 返回值: 
/// </summary>
int profile_SetInt(char* pGroup, char* pKey, int iValue, char* pProfilePath)
{
	char sBuf[100];
	sprintf(sBuf, "%d", iValue);
	return profile_SetString(pGroup, pKey, sBuf, pProfilePath);
}

/// <summary>
/// 功能	 :	设置配置文件中的值
/// 参数	 :	pGroup				组名
///			pKey				关键字名
///			pValue				值
///			pProfilePath		文件路径
/// 返回值: 
/// </summary>
int profile_Setfloat(char* pGroup, char* pKey, float fValue, char* pProfilePath)
{
	char sBuf[100];
	sprintf(sBuf, "%f", fValue);
	return profile_SetString(pGroup, pKey, sBuf, pProfilePath);
}

