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
int path_GetFilesNum(char* pPath)
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
int path_GetFilesAttr(char* pPath, int iOrder, AigFileAttribute* aAttr)
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

#ifdef _WIN32
	TCHAR tcFullPath[AIG_MAXLEN_FILEPATH];
	GetModuleFileName(NULL, tcFullPath, AIG_MAXLEN_FILEPATH);
	string_ConvertEncodingFormat((CHAR*)tcFullPath, sFullPath, AIG_MAXLEN_FILEPATH, eAEConv_UnicodeToAnsi);
	char *pTmp = strrchr(sFullPath, '\\');
	*pTmp = '\0';
#endif

	iLen = strlen(sFullPath) + strlen(pPath) + 3;
	if (iLen > iOutPathLen)
		return eAEC_BufferOver;
	sprintf(pOutPath, "%s\\%s", sFullPath, pPath);
	return eAEC_Success;
}