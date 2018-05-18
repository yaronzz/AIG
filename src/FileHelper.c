#include "StringHelper.h"
#include "PathHelper.h"
#include "FileHelper.h"

/// <summary>
/// 功能	 :	新建目录
/// 参数	 :	pPath	 [in] 路径
/// 返回值:
/// </summary>
int file_Mkdirs(char* pPath)
{
	if (pPath == NULL)
		return eAEC_Input;

	//计算长度
	int iFlag = access(pPath, 0);
	int iLen = strlen(pPath);

	if (iLen > AIG_MAXLEN_FILEPATH)
		return eAEC_PathOver;
	if (iLen <= 0 || iFlag == 0)
		return eAEC_Success;

	//先递归创建前面的目录
	char sString[AIG_MAXLEN_FILEPATH];
	memcpy(sString, pPath, iLen + 1);
	string_ReplaceChr(sString, '/', '\\');

	char* pTmp = strrchr(sString, '\\');
	if (pTmp != NULL)
	{
		*pTmp = '\0';
		if (file_Mkdirs(sString) != eAEC_Success)
			return eAEC_Mkdir;
	}

	if (mkdir(pPath) != 0)
		return eAEC_Mkdir;

	return eAEC_Success;
}

/// <summary>
/// 功能	 :	获取文件的长度
/// 参数	 :	pPath	 [in] 路径
/// 返回值:
/// </summary>
long file_GetFileLen(char* pPath)
{
    if (pPath == NULL)
		return -1;

	if (file_IsFileExist(pPath) != AIG_TRUE)
        return -1;

    FILE* FP = fopen(pPath, "r+");
    if (FP == NULL)
        return -1;

	long lFileLen = 0;
    fseek(FP, 0, SEEK_END);
    lFileLen = ftell(FP);
    fclose(FP);

    return lFileLen;
}

/// <summary>
/// 功能	 :	设置文件权限
/// 参数	 :	pPath	 [in] 路径
/// 返回值:
/// </summary>
int file_SetFileRight(char *pPath, enumAigFileRight eType)
{
	if (pPath == NULL)
		return eAEC_Input;

#ifdef _WIN32
	DWORD aAttr = 0;
	if (eType & eAFileRight_ReadOnly)
		aAttr |= FILE_ATTRIBUTE_READONLY;
	if (eType & eAFileRight_Hide)
		aAttr |= FILE_ATTRIBUTE_HIDDEN;
	if (eType & eAFileRight_System)
		aAttr |= FILE_ATTRIBUTE_SYSTEM;

	SetFileAttributesA((LPCWSTR)pPath, aAttr);
#endif

	return 0;
}

/// <summary>
/// 功能	 :	查看文件是否存在
/// 参数	 :	pPath	 [in] 路径
/// 返回值:
/// </summary>
int file_IsFileExist(char* pPath)
{
	if (pPath == NULL)
		return AIG_FALSE;

	if(access(pPath, 0) == 0)
		return AIG_TRUE;

	return AIG_FALSE;
}

/// <summary>
/// 功能	 :	获取备份路径文件名
/// 参数	 :	pFilePath	 [in] 路径文件名
///			pBakString	 [in] 备份字符串
///			pOutPath	 [out]输出路径
///			iOutPathLen	 [in] 输出路径长度
/// 返回值:
/// </summary>
int file_GetBakFilePath(char* pFilePath, char* pBakString, char* pOutPath, int iOutPathLen)
{
	if (pFilePath == NULL || pBakString == NULL || pOutPath == NULL || iOutPathLen <= 0)
		return eAEC_Input;

	char sTempFileName[AIG_MAXLEN_FILENAME];
	char sTempFilePath[AIG_MAXLEN_FILEPATH];
	char sTempFileExtension[100];
	path_GetDirectoryName(pFilePath, sTempFilePath, sizeof(sTempFilePath));
	path_GetFileNameWithoutExtension(pFilePath, sTempFileName, sizeof(sTempFileName));
	path_GetExtensionName(pFilePath, sTempFileExtension, sizeof(sTempFileExtension));

	strcat(sTempFilePath, sTempFileName);
	strcat(sTempFilePath, pBakString);
	strcat(sTempFilePath, sTempFileExtension);

	int iLen = strlen(sTempFilePath) + 1;
	if (iLen > iOutPathLen)
		return eAEC_BufferOver;

	memcpy(pOutPath, sTempFilePath, iLen);
	return eAEC_Success;
}


