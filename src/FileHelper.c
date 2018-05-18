#include "StringHelper.h"
#include "PathHelper.h"
#include "FileHelper.h"

/// <summary>
/// ����	 :	�½�Ŀ¼
/// ����	 :	pPath	 [in] ·��
/// ����ֵ:
/// </summary>
int file_Mkdirs(char* pPath)
{
	if (pPath == NULL)
		return eAEC_Input;

	//���㳤��
	int iFlag = access(pPath, 0);
	int iLen = strlen(pPath);

	if (iLen > AIG_MAXLEN_FILEPATH)
		return eAEC_PathOver;
	if (iLen <= 0 || iFlag == 0)
		return eAEC_Success;

	//�ȵݹ鴴��ǰ���Ŀ¼
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
/// ����	 :	��ȡ�ļ��ĳ���
/// ����	 :	pPath	 [in] ·��
/// ����ֵ:
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
/// ����	 :	�����ļ�Ȩ��
/// ����	 :	pPath	 [in] ·��
/// ����ֵ:
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
/// ����	 :	�鿴�ļ��Ƿ����
/// ����	 :	pPath	 [in] ·��
/// ����ֵ:
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
/// ����	 :	��ȡ����·���ļ���
/// ����	 :	pFilePath	 [in] ·���ļ���
///			pBakString	 [in] �����ַ���
///			pOutPath	 [out]���·��
///			iOutPathLen	 [in] ���·������
/// ����ֵ:
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


