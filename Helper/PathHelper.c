#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "PathHelper.h"

/// <summary>
/// ����	 :	�鿴Ŀ¼���ļ����ļ��е�����
/// ����	 :	pPath	 [in] ·��
/// ����ֵ:
/// </summary>
int path_GetFilesNumInDirectory(char* pPath)
{
	if (pPath == NULL)
		return eAEC_Input;

	int iRet = 0;
	char sFilePath[AIG_MAXLEN_FILEPATH];

#ifdef WIN32 
	WIN32_FIND_DATA pFindData;
	sprintf(sFilePath, "%s\\*", pPath);
	HANDLE pHandle = FindFirstFileA(sFilePath, (LPWIN32_FIND_DATAA)&pFindData);

	while (pHandle != INVALID_HANDLE_VALUE)
	{
		if (strcmp((LPCCH)pFindData.cFileName, ".") != 0 && strcmp((LPCCH)pFindData.cFileName, "..") != 0)
			iRet++;
		if (!FindNextFileA(pHandle, (LPWIN32_FIND_DATAA)&pFindData))
			break;
	}
	FindClose(pHandle);
#endif

	return iRet;
}

/// <summary>
/// ����	 :	�鿴Ŀ¼���ļ����ļ��е�����
/// ����	 :	pPath	 [in] ·��
///			iOrder	 [in] ���
///			aAttr	 [out]����
/// ����ֵ:
/// </summary>
int path_GetFilesAttrInDirectory(char* pPath, int iOrder, AigFileAttribute* aAttr)
{
	if (pPath == NULL || iOrder < 0 || aAttr == NULL)
		return eAEC_Input;

	int iRet = -1;
	int iLen = 0;
	char sFilePath[AIG_MAXLEN_FILEPATH];
	memset(aAttr, 0, sizeof(AigFileAttribute));

#ifdef WIN32  
	WIN32_FIND_DATA pFindData;
	sprintf(sFilePath, "%s\\*", pPath);
	HANDLE pHandle = FindFirstFileA(sFilePath, (LPWIN32_FIND_DATAA)&pFindData);
	if (pHandle == INVALID_HANDLE_VALUE)
		return iRet;

	for (int iIndex = 0;; iIndex++)
	{
		if (strcmp((LPCCH)pFindData.cFileName, ".") == 0 || strcmp((LPCCH)pFindData.cFileName, "..") == 0)
			iIndex--;
		else if (iIndex == iOrder)
		{
			iRet = eAEC_Success;
			break;
		}

		if (!FindNextFileA(pHandle, (LPWIN32_FIND_DATAA)&pFindData))
			break;
	}

	if (iRet == eAEC_Success)
	{
		//���ָ�ֵ
		iLen = strlen((LPCCH)pFindData.cFileName);
		if (iLen > AIG_MAXLEN_FILENAME)
			return eAEC_BufferOver;
		memcpy(aAttr->FileName, pFindData.cFileName, iLen + 1);

		//�鿴��Ϣ
		aAttr->bIsDirectory	= pFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? AIG_TRUE : AIG_FALSE;
		time_FileTime2AigSystemTime((void*)&pFindData.ftCreationTime, &aAttr->CreatTime);
		time_FileTime2AigSystemTime((void*)&pFindData.ftLastAccessTime, &aAttr->LastAccessTime);
		time_FileTime2AigSystemTime((void*)&pFindData.ftLastWriteTime, &aAttr->LastWriteTime);
	}
	FindClose(pHandle);
#endif

	return iRet;
}



/// <summary>
/// ����	 :	�Ƿ�Ϊ���Ŀ¼
/// ����	 :	pPath	 [in] ·��
/// ����ֵ:
/// </summary>
int path_IsRelativePath(char* pPath)
{
	if (pPath == NULL)
		return AIG_FALSE;

	//c:\\TEST.txt
	char* pTmp = strchr(pPath, ':');
	if (pTmp != NULL)
		return AIG_FALSE;

	// \\\\192.168.71.2\\TEST.txt
	pTmp = strstr(pPath, "\\\\");
	if (pTmp == pPath)
		return AIG_FALSE;

	return AIG_TRUE;
}

/// <summary>
/// ����	 :	��ȡ��ǰ����Ŀ¼
/// ����	 :	pOutPath		[out]���·��
///			iOutPathLen		[in] ���·������
/// ����ֵ:
/// </summary>
int path_GetWorkPath(char* pOutPath, int iOutPathLen)
{
	if (pOutPath == NULL || iOutPathLen <= 0)
		return eAEC_Input;

	//��ȡ����Ŀ¼
	char sFullPath[AIG_MAXLEN_FILEPATH];

#ifdef _WIN32
	TCHAR tcFullPath[AIG_MAXLEN_FILEPATH];
	GetModuleFileName(NULL, tcFullPath, AIG_MAXLEN_FILEPATH);

	string_ConvertEncodingFormat((CHAR*)tcFullPath, sFullPath, AIG_MAXLEN_FILEPATH, eAEConv_UnicodeToAnsi);
	char *pTmp = strrchr(sFullPath, '\\');
	if (pTmp)
		*pTmp = '\0';

#elif linux || __LYNX
	getcwd(sFullPath, sizeof(sFullPath));
#endif

	int iLen = strlen(sFullPath) + 1;
	if( iLen == 0)
		return eAEC_Err;
	if (iLen > iOutPathLen)
		return eAEC_BufferOver;

	memcpy(pOutPath, sFullPath, iLen);
	return eAEC_Success;
}

/// <summary>
/// ����	 :	��ȡ����·��
/// ����	 :	pPath			[in] ·��
///			pOutPath		[out]���·��
///			iOutPathLen		[in] ���·������
/// ����ֵ:
/// </summary>
int path_GetFullPath(char* pPath, char* pOutPath, int iOutPathLen)
{
	if (pPath == NULL || pOutPath == NULL || iOutPathLen <= 0)
		return eAEC_Input;

	//��ѯ�Ƿ�Ϊ���·��
	int iLen;
	if (path_IsRelativePath(pPath) == AIG_FALSE)
	{
		iLen = strlen(pPath) + 1;
		if (iLen > iOutPathLen)
			return eAEC_BufferOver;

		memcpy(pOutPath, pPath, iLen);
		return eAEC_Success;
	}

	//��ȡ����Ŀ¼
	char sFullPath[AIG_MAXLEN_FILEPATH];
	int iCheck = path_GetWorkPath(sFullPath, sizeof(sFullPath));
	if (iCheck != eAEC_Success)
		return iCheck;

	iLen = strlen(sFullPath) + strlen(pPath) + 3;
	if (iLen > iOutPathLen)
		return eAEC_BufferOver;

	sprintf(pOutPath, "%s\\%s", sFullPath, pPath);
	return eAEC_Success;
}






/// <summary>
/// ����	 :	��ȡ·���е��ļ���
/// ����	 :	pFilePath		[in] ·���ļ���
///			pName			[out]����ļ���
///			iNameLen		[in] ����ļ�������
///	����	 :  C:\\JiYF\\BenXH\\BenXHCMS.xml --> BenXHCMS.xml
/// ����ֵ:
/// </summary>
int path_GetFileName(char* pFilePath, char* pName, int iNameLen)
{
	if (pFilePath == NULL || pName == NULL || iNameLen <= 0)
		return eAEC_Input;

	string_ReplaceChr(pFilePath, '/', '\\');

	char* pStart = strrchr(pFilePath, '\\');
	if (pStart == NULL)
		return eAEC_Input;

	pStart++;
	int iLen = strlen(pStart) + 1;
	if (iLen > iNameLen)
		return eAEC_BufferOver;

	memcpy(pName, pStart, iLen);
	return eAEC_Success;
}

/// <summary>
/// ����	 :	��ȡ·���е��ļ���(������չ��)
/// ����	 :	pFilePath		[in] ·���ļ���
///			pName			[out]����ļ���
///			iNameLen		[in] ����ļ�������
///	����	 :  C:\\JiYF\\BenXH\\BenXHCMS.xml --> BenXHCMS
/// ����ֵ:
/// </summary>
int path_GetFileNameWithoutExtension(char* pFilePath, char* pName, int iNameLen)
{
	char sFileName[AIG_MAXLEN_FILEPATH];
	int iCheck = path_GetFileName(pFilePath, sFileName, sizeof(sFileName));
	if (iCheck != eAEC_Success)
		return iCheck;

	char* pTmp = strchr(sFileName, '.');
	if (pTmp)
		*pTmp = '\0';

	int iLen = strlen(sFileName) + 1;
	if (iLen > iNameLen)
		return eAEC_BufferOver;

	memcpy(pName, sFileName, iLen);
	return eAEC_Success;
}

/// <summary>
/// ����	 :	��ȡ·���е��ļ���չ��
/// ����	 :	pFilePath		[in] ·���ļ���
///			pName			[out]����ļ���
///			iNameLen		[in] ����ļ�������
///	����	 :  C:\\JiYF\\BenXH\\BenXHCMS.xml --> .xml
/// ����ֵ:
/// </summary>
int path_GetExtensionName(char* pFilePath, char* pName, int iNameLen)
{
	char sFileName[AIG_MAXLEN_FILEPATH];
	int iCheck = path_GetFileName(pFilePath, sFileName, sizeof(sFileName));
	if (iCheck != eAEC_Success)
		return iCheck;

	char* pTmp = strchr(sFileName, '.');
	if (pTmp == NULL)
		return eAEC_Input;

	int iLen = strlen(pTmp) + 1;
	if (iLen > iNameLen)
		return eAEC_BufferOver;

	memcpy(pName, pTmp, iLen);
	return eAEC_Success;
}

/// <summary>
/// ����	 :	��ȡ·���е�·��
/// ����	 :	pFilePath		[in] ·���ļ���
///			pName			[out]����ļ���
///			iNameLen		[in] ����ļ�������
///	����	 :  C:\\JiYF\\BenXH\\BenXHCMS.xml --> C:\\JiYF\\BenXH\\
/// ����ֵ:
/// </summary>
int path_GetDirectoryName(char* pFilePath, char* pName, int iNameLen)
{
	if (pFilePath == NULL || pName == NULL || iNameLen <= 0)
		return eAEC_Input;

	string_ReplaceChr(pFilePath, '/', '\\');

	char* pStart = strrchr(pFilePath, '\\');
	if (pStart == NULL)
		return eAEC_Input;

	int iLen = pStart - pFilePath + 1;
	if (iLen > iNameLen)
		return eAEC_BufferOver;

	memcpy(pName, pFilePath, iLen);
	pName[iLen] = '\0';
	return eAEC_Success;
}