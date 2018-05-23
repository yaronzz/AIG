#include "StringHelper.h"
#include "ArgvHelper.h"

/// <summary>
/// ����	 :	�����ʼ��
/// ����	 :	pHandle			[in��out]	 ���
/// ����ֵ:  
/// </summary>
static void argv_HandleInit(AigArgvHandle* pHandle)
{
	memset(pHandle, 0x00, sizeof(AigArgvHandle));
	pHandle->iBufferSize	= AIG_MAXLEN_ARGVBUFF;
	pHandle->pTail			= pHandle->sBuffer;
	pHandle->iRemain		= AIG_MAXLEN_ARGVBUFF;
}

/// <summary>
/// ����	 :	��ȡ��������
/// ����	 :	sString			[in]	 �ַ���
/// ����ֵ:  
/// </summary>
static int argv_GetFieldNum(char* sString)
{
	int iNumInterval1 = string_CountChr(sString, '\'');
	int iNumInterval2 = string_CountChr(sString, '"');
	int iNumField	  = string_CountChr(sString, ' ');

	if (iNumInterval1 == 0 && iNumInterval2 == 0)
		return iNumField + 1;

	//���Ϊ���������
	if (iNumInterval1 % 2 != 0 || iNumInterval2 % 2 != 0)
		return 0;

	int iCount		= 0;
	int iBegain		= -1;
	int iEnd		= -1;	
	int iTotalLen	= strlen(sString);
	for (int i = 0; i <= iTotalLen; i++)
	{
		if (i == iTotalLen)
		{
			if (iBegain != -1)
			{
				iEnd = i - 1;
				iCount++;
				iBegain = -1;
			}
			break;
		}

		switch (sString[i])
		{
		case '\'':
		case '"':
			if (iBegain == -1)
				iBegain = i + 1;
			i = strchr(sString + i + 1, sString[i]) - sString;
			break;
		case ' ':
			if (iBegain != -1)
			{
				iEnd = i - 1;
				iCount++;
				iBegain = -1;
			}
			break;

		default:
			if (iBegain == -1)
				iBegain = i;
			break;
		}
	}

	return iCount;
}

/// <summary>
/// ����	 :	��ȡ��N���ֶ�
/// ����	 :	sString			[in]	 �ַ���
///			iOrder			[in]	 ���
///			pField			[in-out] ����ֶ�
///			iFieldLen		[in]	 ����ֶγ���
/// ����ֵ:  >= 0�ɹ�
/// </summary>
static int argv_GetField(char* sString, int iOrder, char* pField, int iFieldLen)
{
	int iNumInterval1 = string_CountChr(sString, '\'');
	int iNumInterval2 = string_CountChr(sString, '"');
	int iNumField	  = string_CountChr(sString, ' ');

	if (iNumInterval1 == 0 && iNumInterval2 == 0)
	{
		return string_GetFieldSting(sString, ' ', iOrder, pField, iFieldLen);
	}

	//���Ϊ���������
	if (iNumInterval1 % 2 != 0 || iNumInterval2 % 2 != 0)
		return eAEC_Input;

	char sChr;
	int iCount		= 0;
	int iBegain		= -1;
	int iEnd		= -1;	
	int iTotalLen	= strlen(sString);
	for (int i = 0; i <= iTotalLen; i++)
	{
		sChr = i == iTotalLen ? ' ' : sString[i];

		switch (sChr)
		{
		case '\'':
		case '"':
			if (iBegain == -1)
				iBegain = i + 1;
			i = strchr(sString + i + 1, sString[i]) - sString;
			break;
		case ' ':
			if (iBegain != -1)
			{
				iEnd = i - 1;
				if (iCount != iOrder)
				{
					iCount++;
					iBegain = -1;
				}
				else
				{
					//������һ���ַ���'����"������Ҫȥ��
					if (iEnd > 0 && (sString[iEnd] == '\'' || sString[iEnd] == '"'))
						iEnd -= 1;

					memcpy(pField, sString + iBegain, iEnd - iBegain + 1);
					pField[iEnd - iBegain + 1] = '\0';
					return eAEC_Success;
				}
			}
			break;

		default:
			if (iBegain == -1)
				iBegain = i;
			break;
		}
	}

	return eAEC_Err;
}


/// <summary>
/// ����	 :	�����ַ���
/// ����	 :	pHandle			[in-out]	 ���
///			pString			[in]		�ַ���
/// ����ֵ:  >= 0�ɹ�
/// </summary>
int argv_ParseString(AigArgvHandle* pHandle, char* pString)
{
	if (pHandle == NULL || pString == NULL)
		return eAEC_Input;

	int iNum;
	int iLen;
	int iIndex;
	char* pCur;
	char sField[1024];
	char* pName;
	char* pValue;

	//��ʼ��
	if (pHandle->iBufferSize != AIG_MAXLEN_ARGVBUFF)
		argv_HandleInit(pHandle);
	if (pHandle->iRemain <= 0)
		return eAEC_BufferOver;

	pCur = pHandle->pTail;
	iNum = argv_GetFieldNum(pString);
	for (int i = 0; i < iNum; i++)
	{
		memset(sField, 0, sizeof(sField));
		argv_GetField(pString, i, sField, sizeof(sField));
		
		iLen = strlen(sField) + 1;
		if (iLen > pHandle->iRemain)
			return eAEC_BufferOver;

		//��ֵ
		iIndex = pHandle->NumParams;
		pName = pHandle->sBuffer + pHandle->iBufferSize - pHandle->iRemain;
		pHandle->pParamList[iIndex].sName = pName;
		memcpy(pName, sField, iLen);

		pValue = strchr(pName, '=');
		if (pValue)
		{
			*pValue = '\0';
			pHandle->pParamList[iIndex].sValue = pValue + 1;
		}

		pHandle->NumParams++;
		pHandle->iRemain -= iLen;
	}

	return eAEC_Success;
}

/// <summary>
/// ����	 :	����Main��
/// ����	 :	pHandle			[in-out]	 ���
///			argc			[in]		 Main������
///			argv			[in]		 Main������
/// ����ֵ:  >= 0�ɹ�
/// </summary>
int argv_ParseMainPara(AigArgvHandle* pHandle, int argc, char * argv[])
{
	if (pHandle == NULL || argc < 0 )
		return eAEC_Input;

	int iCheck;
	for (int i = 0; i < argc; i++)
	{
		iCheck = argv_ParseString(pHandle, argv[i]);
		if (iCheck != eAEC_Success)
			return iCheck;
	}

	return eAEC_Success;
}