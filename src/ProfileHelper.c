#include "StringHelper.h"
#include "PathHelper.h"
#include "FileHelper.h"
#include "ProfileHelper.h"


typedef enum _enumAigProfileLineType
{
	eAPLType_Comment,	//ע��
	eAPLType_Group,		//��
	eAPLType_KeyValue,	//�ؼ��ֺ�ֵ
	eAPLType_UnKnown,	//δ֪
}enumAigProfileLineType;

/// <summary>
/// ����	 :	������
/// ����	 :	pLineBuf		�л���
///			sName			�ؼ�����
///			sValue			ֵ
///			iNameLen		�ؼ���������
///			iValueLen		ֵ����
/// ����ֵ: 
/// </summary>
static enumAigProfileLineType profile_ReadLine(char* pLineBuf, char* sName, char* sValue, int iNameLen, int iValueLen)
{
	//���㳤��
	string_LeftTrim(pLineBuf, AIG_STRING_EMPTY);
	if (strlen(pLineBuf) == 0)
		return eAPLType_UnKnown;

	//��ѯ�Ƿ�Ϊע����
	if (pLineBuf[0] == '#')
		return eAPLType_Comment;
	//�鿴�Ƿ��M
	if (string_SubstringByInterval(pLineBuf, '[', ']', sName, iNameLen) == eAEC_Success)
		return eAPLType_Group;
	//��ѯ�Ƿ�Ϊ�ؼ��ֺ�ֵ��
	if (string_SubstringByChr(pLineBuf, '=', sName, iNameLen, sValue, iValueLen) == eAEC_Success)
		return eAPLType_KeyValue;

	return eAPLType_UnKnown;
}



/// <summary>
/// ����	 :	��ȡ�����ļ��е�ֵ
/// ����	 :	pGroup				����
///			pKey				�ؼ�����
///			pDefault			Ĭ��ֵ
///			pReturnString		����ַ���
///			iReturnStringLen	����ַ�������
///			pProfilePath		�ļ�·��
/// ����ֵ: 
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

	//���û�ҵ�����Ĭ��ֵ����
	if (pDefault)
	{
		iLen = strlen(pDefault) + 1;
		iLen = iLen > iValueLen ? iValueLen : iLen;
		memcpy(pValue, pDefault, iLen);
	}

	//���ļ�
	if ((pFD = fopen(pProfilePath, "r")) == NULL)
		return eAEC_Open;
	
	//ѭ����ȡ������
	while (feof(pFD) == 0)
	{
		fgets(sBuf, sizeof(sBuf), pFD);
		eLineType = profile_ReadLine(sBuf, sName, sValue, sizeof(sName), sizeof(sValue));

		switch (eLineType)
		{
		case eAPLType_Comment:
			break;
		case eAPLType_Group:
			iInGroup = stricmp(sName, pGroup) == 0 ? 1 : 0;
			break;
		case eAPLType_KeyValue:
			if (iInGroup)
			{
				if (stricmp(sName, pKey) != 0)
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
/// ����	 :	��ȡ�����ļ��е�ֵ
/// ����	 :	pGroup				����
///			pKey				�ؼ�����
///			pDefault			Ĭ��ֵ
///			pProfilePath		�ļ�·��
/// ����ֵ: 
/// </summary>
int profile_GetInt(char* pGroup, char* pKey, int pDefault, char* pProfilePath)
{
	char sBuf[1024];
	if (profile_GetString(pGroup, pKey, NULL, sBuf, sizeof(sBuf), pProfilePath) == eAEC_Success)
		return atoi(sBuf);

	return pDefault;
}

/// <summary>
/// ����	 :	��ȡ�����ļ��е�ֵ
/// ����	 :	pGroup				����
///			pKey				�ؼ�����
///			pDefault			Ĭ��ֵ
///			pProfilePath		�ļ�·��
/// ����ֵ: 
/// </summary>
float profile_GetFloat(char* pGroup, char* pKey, float pDefault, char* pProfilePath)
{
	char sBuf[1024];
	if (profile_GetString(pGroup, pKey, NULL, sBuf, sizeof(sBuf), pProfilePath) == eAEC_Success)
		return atof(sBuf);

	return pDefault;
}

/// <summary>
/// ����	 :	���������ļ��е�ֵ
/// ����	 :	pGroup				����
///			pKey				�ؼ�����
///			pValue				ֵ
///			pProfilePath		�ļ�·��
/// ����ֵ: 
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

	//���ļ�
	if ((pFD = fopen(pProfilePath, "a+")) == NULL)
		return eAEC_Open;

	//�򿪱����ļ�
	file_GetBakFilePath(pProfilePath, "-aigbak", sTempFilePath, sizeof(sTempFilePath));
	if ((pTempFD = fopen(sTempFilePath, "w+")) == NULL)
		return eAEC_Open;
	
	//ѭ����ȡ������
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
				if (stricmp(sName, pGroup) == 0)
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
					if (stricmp(sName, pKey) != 0)
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

	//���û��д��ȥ����������������
	if (!iAlreadySet)
	{
		fprintf(pTempFD, "[%s]\n", pGroup);
		fprintf(pTempFD, "%s=%s\n", pKey, pValue);
	}

	//�ļ�����
	fclose(pFD);
	fclose(pTempFD);
	remove(pProfilePath);
	rename(sTempFilePath, pProfilePath);

	return eAEC_Success;
}

/// <summary>
/// ����	 :	���������ļ��е�ֵ
/// ����	 :	pGroup				����
///			pKey				�ؼ�����
///			pValue				ֵ
///			pProfilePath		�ļ�·��
/// ����ֵ: 
/// </summary>
int profile_SetInt(char* pGroup, char* pKey, int iValue, char* pProfilePath)
{
	char sBuf[100];
	sprintf(sBuf, "%d", iValue);
	return profile_SetString(pGroup, pKey, sBuf, pProfilePath);
}

/// <summary>
/// ����	 :	���������ļ��е�ֵ
/// ����	 :	pGroup				����
///			pKey				�ؼ�����
///			pValue				ֵ
///			pProfilePath		�ļ�·��
/// ����ֵ: 
/// </summary>
int profile_Setfloat(char* pGroup, char* pKey, float fValue, char* pProfilePath)
{
	char sBuf[100];
	sprintf(sBuf, "%f", fValue);
	return profile_SetString(pGroup, pKey, sBuf, pProfilePath);
}

