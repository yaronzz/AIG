#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

#include "FileHelper.h"

//Ԫ�رȽϻص�������0���,>0 A>B,<0 A<B��
static int	file_CMPString(void* in_ElementA, void* in_ElementB)
{
	char* pStrA = (char*)in_ElementA;
	char* pStrB = (char*)in_ElementB;
	return strcmp(pStrA, pStrB);
}

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

	switch (eType)
	{
	case eAFileRight_ReadOnly://ֻ��
#ifdef _WIN32
		SetFileAttributes((LPCWSTR)pPath,FILE_ATTRIBUTE_READONLY);
#endif
		break;
	case eAFileRight_Hide://����
#ifdef _WIN32
		SetFileAttributes((LPCWSTR)pPath, FILE_ATTRIBUTE_HIDDEN);
#endif
		break;
	}

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


//����Ŀ¼
int file_BakDir(char* pSrcPath, char* pDescPath)
{
	if (pSrcPath == NULL || pDescPath == NULL)
		return eAEC_Input;

	int iRet = 0;
	char* pBuff = (char*)malloc(AIG_MAXLEN_FILEPATH * 2);
	if (pBuff == NULL)
		return eAEC_Malloc;

#ifdef WIN32
	if (file_IsFileExist(pSrcPath) != AIG_TRUE)
	{
		iRet = eAEC_NoDir;
		goto RETURN;
	}
	if (file_IsFileExist(pDescPath) != AIG_TRUE)		//������Ŀ¼���������½�
		file_Mkdirs(pDescPath);

	sprintf(pBuff, "xcopy %s %s /e", pSrcPath, pDescPath);	//ʹ��ϵͳ����������Ŀ¼
	system(pBuff);
#endif

RETURN:
	if (pBuff)
		free(pBuff);
	return iRet;
}





/***************************************************************************************************************************
����·�����ļ�������չ��
***************************************************************************************************************************/
//��ȡ�ļ�����Ŀ¼
char* file_GetDirectoryName(char* pPath)
{
	//C:\\JiYF\\BenXH\\BenXHCMS.xml --> C:\\JiYF\\BenXH/
	if (pPath == NULL)
		return NULL;

	char* pBuf = (char*)malloc(strlen(pPath) + 1);
	if (pBuf == NULL)
		return NULL;

	sprintf(pBuf, pPath);
	string_ReplaceChr(pBuf, '/', '\\');

	char* pTmp = strrchr(pBuf, '\\');
	if (pTmp)
		*(pTmp + 1) = 0;
	else
	{
		free(pBuf);
		pBuf = (char*)malloc(3);
		sprintf(pBuf, ".\\");
	}
	return pBuf;
}

//��ȡ�ļ���
char* file_GetFileName(char* pPath)
{
	//C:\\JiYF\\BenXH\\BenXHCMS.xml --> BenXHCMS.xml
	if (pPath == NULL)
		return NULL;

	char* pBuf = (char*)malloc(strlen(pPath) + 1);
	if (pBuf == NULL)
		return NULL;

	sprintf(pBuf, pPath);
	string_ReplaceChr(pBuf, '/', '\\');

	char* pTmp = strrchr(pBuf, '\\');
	if (pTmp)
	{
		pTmp++;

		char* pRet = (char*)malloc(strlen(pTmp) + 1);
		if (pRet == NULL)
			goto RETURN;

		sprintf(pRet, pTmp);
		free(pBuf);
		return pRet;
	}
	
	return pBuf;

RETURN:
	if (pBuf)
		free(pBuf);
	return NULL;
}

//��ȡ�ļ���(������չ��)
char* file_GetFileNameWithoutExtension(char* pPath)
{
	//C:\\JiYF\\BenXH\\BenXHCMS.xml --> BenXHCMS
	char* pBuf = file_GetFileName(pPath);
	if (pBuf == NULL)
		return NULL;

	char* pTmp = strchr(pBuf, '.');
	if (pTmp != NULL)
		*pTmp = 0;

	return pBuf;
}

//��ȡ�ļ���չ��
char* file_GetExtension(char* pPath)
{
	//C:\\JiYF\\BenXH\\BenXHCMS.xml --> .xml
	char* pBuf = file_GetFileName(pPath);
	if (pBuf == NULL)
		return NULL;

	char* pTmp = strchr(pBuf, '.');
	if (pTmp == NULL)
		goto RETURN;

	char* pRet = (char*)malloc(strlen(pTmp));
	if (pRet == NULL)
		goto RETURN;

	sprintf(pRet, pTmp);
	free(pBuf);
	return pRet;

	RETURN:
	free(pBuf);
	return NULL;
}

//��ȡ��Ŀ¼
char* file_GetPathRoot(char* pPath)
{
	//C:\\JiYF\\BenXH\\BenXHCMS.xml --> C:/
	char* pBuf = file_GetDirectoryName(pPath);
	if (pBuf == NULL)
		return NULL;

	int iTmp = string_FindStr(pBuf, ":\\");
	if (iTmp < 0)
		goto RETURN;

	char* pTmp = pBuf + iTmp + 2;
	*pTmp = 0;

	return pBuf;

RETURN:
	free(pBuf);
	return NULL;
}
//
///*************************************************************************************************************
//    ���ܣ������ļ�����
//    �ļ�������ʽ��
//                #��ע/����
//                ��xxx��
//                 xxx = yyy
//	�ڴ滺�壺˫������
//			1��С������
//			2����������
//*************************************************************************************************************/
//
//typedef struct __PROFILE_OBJ
//{
//    char* pObjName;		//������
//    char* pValue;		//ֵ
//	char* pComment;		//ע��
//}PROFILE_OBJ;
//
//typedef struct __PROFILE_GROUP
//{
//    char* pGroupName;	//С����
//    void* pObjList;		//��������
//}PROFILE_GROUP;
//
//typedef struct __PROFILE_HANDLE
//{
//	char* pFileName;
//	void* pGroupList;
//}PROFILE_HANDLE;
//
////Ԫ�رȽϻص�������0���,>0 A>B,<0 A<B��
//static int	CMP_ProfileGroup(void* in_ElementA, void* in_ElementB)
//{
//    PROFILE_GROUP* pStrA = (PROFILE_GROUP*)in_ElementA;
//    PROFILE_GROUP* pStrB = (PROFILE_GROUP*)in_ElementB;
//	if (pStrA->pGroupName == NULL && pStrB->pGroupName == NULL)
//		return 0;
//    if (pStrA->pGroupName == NULL)
//        return -1;
//	if (pStrB->pGroupName == NULL)
//        return 1;
//    return strcmp(pStrA->pGroupName, pStrB->pGroupName);
//}
//
////Ԫ�رȽϻص�������0���,>0 A>B,<0 A<B��
//static int	CMP_ProfileObj(void* in_ElementA, void* in_ElementB)
//{
//	PROFILE_OBJ* pStrA = (PROFILE_OBJ*)in_ElementA;
//	PROFILE_OBJ* pStrB = (PROFILE_OBJ*)in_ElementB;
//	return strcmp(pStrA->pObjName, pStrB->pObjName);
//}
//
////Ԫ���ͷŻص�����
//static int EARSE_Profile(void* pData)
//{
//    if (pData)
//        free(pData);
//    return 0;
//}
//
//static void FreeObj(PROFILE_OBJ* pObj)
//{
//    if (pObj)
//    {
//        if (pObj->pObjName)free(pObj->pObjName);
//        if (pObj->pValue)free(pObj->pValue);
//		if (pObj->pComment)free(pObj->pComment);
//    }
//}
//
//static void FreeGroup(PROFILE_GROUP* pGroup)
//{
//    if (pGroup)
//    {
//        if (pGroup->pGroupName)free(pGroup->pGroupName);
//        dlist_Uninit(&pGroup->pObjList, EARSE_Profile);
//    }
//}
//
//static void* AddGroup(void* pGroupList,char* pGroupName)
//{
//	PROFILE_GROUP* pNewGroup = (PROFILE_GROUP*)malloc(sizeof(PROFILE_GROUP));
//	if (pNewGroup == NULL)
//		return NULL;
//
//	pNewGroup->pGroupName = pGroupName;
//
//	PROFILE_GROUP* pOldGroup = dlist_Find(pGroupList, pNewGroup,NULL);
//	if (pOldGroup)
//	{
//		free(pGroupName);
//		free(pNewGroup);
//		return pOldGroup->pObjList;
//	}
//	else
//	{
//		dlist_Init(&pNewGroup->pObjList, CMP_ProfileObj);
//		dlist_Put(pGroupList, pNewGroup);
//	}
//	return pNewGroup->pObjList;
//}
//
//static void* AddObj(void* pObjList, char* pObjName, char*pValue,char* pComment)
//{
//	PROFILE_OBJ* pNewObj = (PROFILE_OBJ*)malloc(sizeof(PROFILE_OBJ));
//	if (pNewObj == NULL)
//		return NULL;
//
//	pNewObj->pObjName = pObjName;
//	pNewObj->pValue = pValue;
//	pNewObj->pComment = pComment;
//	
//	PROFILE_OBJ* pOldObj = dlist_Find(pObjList, pNewObj,NULL);
//	if (pOldObj)
//	{
//		free(pOldObj->pValue);
//		pOldObj->pValue = pValue;
//		if (pComment)
//		{
//			if (pOldObj->pComment)
//				free(pOldObj->pComment);
//			pOldObj->pComment = pComment;
//		}
//
//		free(pObjName);
//		free(pNewObj);
//	}
//	else
//		dlist_Put(pObjList, pNewObj);
//	return pNewObj;
//}
//
////���������ݣ�-1���� 0С�� 1����
//static int ParseLine(char* pLineBuff, char** pName, char** pValue,char** pComment)
//{
//	//�Ƿ�Ϊ����
//	string_Trim(pLineBuff, NULL);
//	if(string_FindChr(AIG_FILE_PROFILE_NOTE_FLAG, pLineBuff[0]) == 0)
//		return -1;
//
//	//�Ƿ�ΪС��
//	int iLen = 0,iStart;
//	if ((iStart = string_FindChr(pLineBuff, '[')) == 0)
//	{
//		iLen = string_FindChr(pLineBuff, ']');
//		iLen = iLen == -1 ? strlen(pLineBuff) : iLen - iStart - 1;
//		*pName = string_Substring(pLineBuff, iStart + 1, iLen);
//		if (*pName == NULL)
//			return -1;
//		string_Trim(*pName, NULL);
//		return 0;
//	}
//
//	//�Ƿ�Ϊ����
//	if (string_GetFieldNum(pLineBuff, '=') != 2)
//		return -1;
//
//	*pName = string_GetFieldSting(pLineBuff, '=', 0);
//	*pComment = NULL;
//
//	char* pValueAndComment = string_GetFieldSting(pLineBuff, '=', 1);
//	if ((iLen = string_FindStr(pValueAndComment, "//")) != -1)
//	{
//		*pValue = string_Substring(pValueAndComment, 0, iLen);
//		*pComment = string_Substring(pValueAndComment, iLen + 1, strlen(pValueAndComment) - iLen );
//	}
//	else
//		*pValue = pValueAndComment;
//	if (string_IsValid(*pName) == 0)
//	{
//		free(*pName);
//		free(*pValue);
//		*pName = NULL;
//		*pValue = NULL;
//		return -1;
//	}
//	string_Trim(*pName, NULL);
//	return 1;
//}
//
////�����ļ�
//static int ParseProfile(char* pFileName, void* pGroupList)
//{
//	int iCheck,iRet = 0;
//	FILE* FP = NULL;
//	char* pLineBuff = NULL,*pName,*pValue,*pComment;
//	if ((pLineBuff = (char*)malloc(AIG_FILE_PROFILE_LINE_MAXLEN)) == NULL)
//	{
//		iRet = eAEC_Malloc;
//		goto RETURN;
//	}
//
//	//�����������ļ�����·���Ƿ���ȷ
//	if (_access(pFileName, 0) != 0)
//	{
//		if ((FP = fopen(pFileName, "w+")) == NULL)
//			iRet = eAEC_Creat;
//		if (FP)
//			fclose(FP);
//		FP = NULL;
//		remove(pFileName);
//		goto RETURN;
//	}
//	
//	//���ļ���ȡ�����ļ�
//	if ((FP = fopen(pFileName, "r+")) == NULL)	
//	{
//		iRet = eAEC_Open;
//		goto RETURN;
//	}
//
//	//�����һ������
//	void* pObjList = NULL;
//	pObjList = AddGroup(pGroupList, NULL);
//
//	while (feof(FP) == 0)
//	{
//		pLineBuff[0] = '\0';
//		fgets(pLineBuff, AIG_FILE_PROFILE_LINE_MAXLEN, FP);
//		if ((iCheck = ParseLine(pLineBuff, &pName, &pValue, &pComment)) == -1)
//			continue;
//		if (iCheck == 0)//С��
//			pObjList = AddGroup(pGroupList, pName);
//		if (iCheck == 1)//����
//			AddObj(pObjList, pName, pValue, pComment);
//	}
//
//	dlist_Setout(pObjList);
//RETURN:
//	if (FP)
//		fclose(FP);
//	if (pLineBuff)
//		free(pLineBuff);
//	return 0;
//}
//
//
///// <summary>
////��д�����ļ�
////������pHandle	�ļ����
////	   pGroup   С����(������ʾ)
////     pKey     �ؼ���
////	   pValue   �ַ���ֵ
////     fValue   ����ֵ
////     fDefault Ĭ��ֵ(��û���ҵ��ؼ���ʱ��ؼ��ֺ�û��ֵʱ,��Ĭ��ֵ����)
///// </summary>
//
////��ʼ��
//int file_InitProfile(void** pHandle, char* pFileName)
//{
//	if (pFileName == NULL)
//		return eAEC_Input;
//
//	//�����ڴ滺��
//	PROFILE_HANDLE *pProfileHandle = (PROFILE_HANDLE*)malloc(sizeof(PROFILE_HANDLE));
//	if (pProfileHandle == NULL)
//		return eAEC_Malloc;
//
//	//��ʼ�����
//    memset(pProfileHandle, 0, sizeof(PROFILE_HANDLE));
//    if (dlist_Init(&pProfileHandle->pGroupList, CMP_ProfileGroup) != 0)
//    {
//        free(pProfileHandle);
//        return -1;
//    }
//    //�������ļ�
//    int iCheck;
//	if ((iCheck = ParseProfile(pFileName, pProfileHandle->pGroupList)) != 0)
//	{
//        dlist_Uninit(&pProfileHandle->pGroupList, NULL);
//        free(pProfileHandle);
//        return iCheck;
//	}
//	
//	pProfileHandle->pFileName = (char*)malloc(strlen(pFileName) + 1);
//	sprintf(pProfileHandle->pFileName, "%s", pFileName);
//    *pHandle = pProfileHandle;
//	return eAEC_Success;
//}
//
////���ʼ��
//int file_UnintProfile(void** pHandle)
//{
//    if (*pHandle == NULL)
//		return eAEC_Input;
//
//    PROFILE_HANDLE *pProfileHandle = *pHandle;
//
//    PROFILE_OBJ*   pObj;
//    PROFILE_GROUP* pGroup;
//    dlist_Setout(pProfileHandle->pGroupList);
//    while (dlist_GetNext(pProfileHandle->pGroupList, &pGroup) == 0)
//    {
//        dlist_Setout(pGroup->pObjList);
//        while (dlist_GetNext(pGroup->pObjList, &pObj) == 0)
//            FreeObj(pObj);
//		dlist_Uninit(&pGroup->pObjList, EARSE_Profile);
//		FreeGroup(pGroup);
//    }
//
//    free(pProfileHandle->pFileName);
//    dlist_Uninit(&pProfileHandle->pGroupList, EARSE_Profile);
//
//    free(pProfileHandle);
//    *pHandle = NULL;
//	return eAEC_Success;
//}
//
////����
//int file_SaveProfile(void* pHandle)
//{
//	if (pHandle == NULL)
//		return eAEC_Input;
//
//	PROFILE_HANDLE *pProfileHandle = pHandle;
//	return file_SaveAsProfile(pHandle, pProfileHandle->pFileName);
//}
//
//
////���Ϊ
//int   file_SaveAsProfile(void* pHandle, char* pFileName)
//{
//	if (pHandle == NULL)
//		return eAEC_Input;
//
//	PROFILE_HANDLE *pProfileHandle = pHandle;
//	FILE* FP = fopen(pFileName, "w+");
//	if (FP == NULL)
//		return eAEC_Open;
//
//	PROFILE_OBJ*   pObj;
//	PROFILE_GROUP* pGroup;
//	dlist_Setout(pProfileHandle->pGroupList);
//	while (dlist_GetNext(pProfileHandle->pGroupList, &pGroup) == 0)
//	{
//		if (pGroup->pGroupName)
//			fprintf(FP, "\n[%s]\n", pGroup->pGroupName);
//
//		dlist_Setout(pGroup->pObjList);
//		while (dlist_GetNext(pGroup->pObjList, &pObj) == 0)
//		{
//			fprintf(FP, "%s = ", pObj->pObjName);
//			if (pObj->pValue)
//				fprintf(FP, "%s	", pObj->pValue);
//			if (pObj->pComment)
//				fprintf(FP, "//%s", pObj->pComment);
//			fputc('\n', FP);
//		}
//	}
//	fclose(FP);
//	return eAEC_Success;
//}
//
////д���ַ���ֵ
//int   file_WriteProfileString(void* pHandle, char* pGroup, char* pKey, char* pValue, char* pComment)
//{
//	if (pHandle == NULL || pKey == NULL)
//		return eAEC_Input;
//
//	char* in_GroupName = NULL, *in_Key = NULL, *in_Value = NULL,*in_pComment = NULL;
//	if (pGroup)
//	{
//		in_GroupName = (char*)malloc(strlen(pGroup) + 1);
//		sprintf(in_GroupName, "%s", pGroup);
//	}
//	if (pValue)
//	{
//		in_Value = (char*)malloc(strlen(pValue) + 1);
//		sprintf(in_Value, "%s", pValue);
//	}
//	if (pComment)
//	{
//		in_pComment = (char*)malloc(strlen(pComment) + 1);
//		sprintf(in_pComment, "%s", pComment);
//	}
//
//	in_Key = (char*)malloc(strlen(pKey) + 1);
//	sprintf(in_Key, "%s", pKey);
//
//	int iRet = eAEC_Success;
//	PROFILE_HANDLE *pProfileHandle = pHandle;
//	void* pObjList = AddGroup(pProfileHandle->pGroupList, in_GroupName);
//	if (pObjList == NULL)
//	{
//		iRet = -1;
//		goto RETURN;
//	}
//	if (AddObj(pObjList, in_Key, in_Value, in_pComment) == NULL)
//		iRet = -1;
//
//RETURN:
//	if (iRet != eAEC_Success)
//	{
//		if (in_GroupName)free(in_GroupName);
//		if (in_Key)free(in_Key);
//		if (in_Value)free(in_Value);
//	}
//	return eAEC_Success;
//}
//
////д�븡����(С�����6λ)
//int   file_WriteProfileFloat(void* pHandle, char* pGroup, char* pKey, float fValue, char* pComment)
//{
//	if (pHandle == NULL || pKey == NULL)
//		return eAEC_Input;
//
//	char pValue[20];
//	sprintf(pValue, "%f", fValue);
//	int iPointIndex = string_FindChr(pValue, '.');
//	if (iPointIndex != -1)
//		string_RightTrim(pValue, "0");
//
//	int iCheck = file_WriteProfileString(pHandle, pGroup, pKey, pValue, pComment);
//	return iCheck;
//}
//
////��ȡ�ַ���ֵ
//char* file_ReadProfileString(void* pHandle, char* pGroup, char* pKey)					
//{
//	if (pHandle == NULL || pKey == NULL)
//		return NULL;
//
//	PROFILE_HANDLE *pProfileHandle = pHandle;
//	PROFILE_GROUP aGroup;
//	aGroup.pGroupName = pGroup;
//	PROFILE_GROUP* pOldGroup = dlist_Find(pProfileHandle->pGroupList, &aGroup,NULL);
//	if (pOldGroup == NULL)
//		return NULL;
//
//	PROFILE_OBJ aObj;
//	aObj.pObjName = pKey;
//	PROFILE_OBJ* pOldObj = dlist_Find(pOldGroup->pObjList, &aObj,NULL);
//	if (pOldObj == NULL || pOldObj->pValue == NULL)
//		return NULL;
//	else
//	{
//		int iLen = strlen(pOldObj->pValue)+1;
//		char*pRet = (char*)malloc(iLen);
//		sprintf(pRet, "%s", pOldObj->pValue);
//		return pRet;
//	}
//	return NULL;
//}
//
////��ȡ������
//float file_ReadProfileFloat(void* pHandle, char* pGroup, char* pKey)
//{
//	char* pValue = file_ReadProfileString(pHandle, pGroup, pKey);
//	if (pValue == NULL)
//		return -1;
//	float fDefault = (float)atof(pValue);
//	free(pValue);
//	return fDefault;
//}
//
////ɾ��ĳһ���ؼ���
//int file_RemoveProfileKey(void* pHandle, char* pGroup, char* pKey)
//{
//	if (pHandle == NULL || pKey == NULL)
//		return eAEC_Input;
//
//	PROFILE_HANDLE *pProfileHandle = pHandle;
//	PROFILE_GROUP aGroup;
//	aGroup.pGroupName = pGroup;
//	int GroupIndex;
//	PROFILE_GROUP* pOldGroup = dlist_Find(pProfileHandle->pGroupList, &aGroup, &GroupIndex);
//	if (pOldGroup == NULL)
//		return -1;
//
//	PROFILE_OBJ aObj;
//	aObj.pObjName = pKey;
//	int Index;
//	PROFILE_OBJ* pOldObj = dlist_Find(pOldGroup->pObjList, &aObj,&Index);
//	if (pOldObj == NULL)
//		return -1;
//	else
//	{
//		free(pOldObj->pObjName);
//		if (pOldObj->pValue)
//			free(pOldObj->pValue);
//		dlist_RemoveAt(pOldGroup->pObjList, Index, NULL);
//		if (dlist_GetSize(pOldGroup->pObjList) <= 0)		//���С�����Ѿ�û��Key��,��ɾ��С��
//		{
//			dlist_Uninit(pOldGroup->pObjList, NULL);
//			FreeGroup(pOldGroup);
//			dlist_RemoveAt(pProfileHandle->pGroupList, GroupIndex, NULL);
//		}
//	}
//	return eAEC_Success;
//}
//
////ɾ��ȫ���ؼ���
//int file_RemoveProfileAllKey(void* pHandle)
//{
//	if (pHandle == NULL)
//		return eAEC_Input;
//
//	PROFILE_HANDLE *pProfileHandle = pHandle;
//
//	PROFILE_OBJ*   pObj;
//	PROFILE_GROUP* pGroup;
//	dlist_Setout(pProfileHandle->pGroupList);
//	while (dlist_GetNext(pProfileHandle->pGroupList, &pGroup) == 0)
//	{
//		dlist_Setout(pGroup->pObjList);
//		while (dlist_GetNext(pGroup->pObjList, &pObj) == 0)
//			FreeObj(pObj);
//		dlist_Uninit(&pGroup->pObjList, EARSE_Profile);
//		FreeGroup(pGroup);
//	}
//
//	free(pProfileHandle->pFileName);
//	dlist_RemoveAll(&pProfileHandle->pGroupList, EARSE_Profile);
//
//	return eAEC_Success;
//}
//
////ɾ��С��
//int  file_RemoveProfileGroup(void* pHandle, char* pGroup)
//{
//	if (pHandle == NULL)
//		return eAEC_Input;
//
//	PROFILE_HANDLE *pProfileHandle = pHandle;
//	PROFILE_GROUP aGroup;
//	aGroup.pGroupName = pGroup;
//	int GroupIndex;
//	PROFILE_GROUP* pOldGroup = dlist_Find(pProfileHandle->pGroupList, &aGroup, &GroupIndex);
//	if (pOldGroup == NULL)
//		return -1;
//
//	PROFILE_OBJ* pObj;
//	dlist_Setout(pOldGroup->pObjList);
//	while (dlist_GetNext(pOldGroup->pObjList, &pObj) == 0)
//		FreeObj(pObj);
//	dlist_Uninit(&pOldGroup->pObjList, EARSE_Profile);
//	FreeGroup(pOldGroup);
//	dlist_RemoveAt(pProfileHandle->pGroupList, GroupIndex, NULL);
//
//	return eAEC_Success;
//}
