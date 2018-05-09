#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "DefHelper.h"
#include "StringHelper.h"


/// <summary>
/// ����	 :	ȥ���ַ�������ߵ��ַ�
/// ����	 :	in_out_pStr		�ַ������������
///			remove_Chr		��Ӧ�ַ�
/// ����ֵ:
/// </summary>
int string_LeftTrim(char* in_out_pStr, char* remove_Chr)
{
	if (in_out_pStr == NULL || remove_Chr == NULL)
		return eAEC_Input;

	//��ȡ��ɾ�����ַ�������
	int iIndex = 0;
	int iLen = strlen(in_out_pStr);
	for (iIndex = 0; iIndex < iLen; iIndex++)
	{
		if (strchr(remove_Chr, in_out_pStr[iIndex]) == NULL)
			break;
	}

	//λ��
	int iOffset = iLen - iIndex;
	for (int i = 0; i < iOffset; i++)
	{
		in_out_pStr[i] = in_out_pStr[i + iIndex];
	}
	in_out_pStr[iOffset] = '\0';

	return eAEC_Success;
}

/// <summary>
/// ����	 :	ȥ���ַ������ұߵ��ַ�
/// ����	 :	in_out_pStr		�ַ������������
///			remove_Chr		��Ӧ�ַ�
/// ����ֵ:
/// </summary>
int string_RightTrim(char* in_out_pStr, char* remove_Chr)
{
	if (in_out_pStr == NULL || remove_Chr == NULL)
		return eAEC_Input;

	int iIndex = 0;
	int iLen = strlen(in_out_pStr);
	for (iIndex = iLen - 1; iIndex >= 0; iIndex--)
	{
		if (strchr(remove_Chr, in_out_pStr[iIndex]) == NULL)
			break;;
	}
	in_out_pStr[iIndex + 1] = '\0';

	return eAEC_Success;
}

/// <summary>
/// ����	 :	ȥ���ַ��������ұߵ��ַ�
/// ����	 :	in_out_pStr		�ַ������������
///			remove_Chr		��Ӧ�ַ�
/// ����ֵ:
/// </summary>
int string_Trim(char* in_out_pStr, char* remove_Chr)
{
	if (in_out_pStr == NULL || remove_Chr == NULL)
		return eAEC_Input;

	int iCheck;
	//ȥ����ߵĿո�,TAB�ͻ���
	if ((iCheck = string_LeftTrim(in_out_pStr, remove_Chr)) != eAEC_Success)
		return iCheck;
	//ȥ���ұߵĿո�,TAB�ͻ���
	if ((iCheck = string_RightTrim(in_out_pStr, remove_Chr)) != eAEC_Success)
		return iCheck;

	return eAEC_Success;
}



/// <summary>
/// ����	 :	�����ַ������ַ�������
/// ����	 :	in_pStr			�ַ���
///			in_Chr			��Ӧ�ַ�
/// ����ֵ:
/// </summary>
int string_CountChr(char* in_pStr, char in_Chr)
{
	if (in_pStr == NULL)
		return eAEC_Input;

	int iCount = 0;
	char* pTmp = in_pStr;
	while ((pTmp = strchr(pTmp, in_Chr)) != NULL)
	{
		iCount++;
		pTmp++;
	}
	return iCount;
}


/// <summary>
/// ����	 :	�����ַ������Ӵ�������
/// ����	 :	in_pStr			�ַ���
///			in_Src			��Ӧ�Ӵ�
/// ����ֵ:
/// </summary>
int string_CountStr(char* in_pStr, char* in_Src)
{
	if (in_pStr == NULL || in_Src == NULL)
		return eAEC_Input;

	int iCount = 0;
	int iLen = strlen(in_Src);
	char* pTmp = in_pStr;
	while ((pTmp = strstr(pTmp, in_Src)) != NULL)
	{
		iCount++;
		pTmp += iLen;
	}
	return iCount;
}

/// <summary>
/// ����	 :	�����ַ����е�һ��ƥ���ַ����±�
/// ����	 :	in_pStr			�ַ���
///			in_Chr			��Ӧ�ַ�
/// ����ֵ:  >= 0 ����
/// </summary>
int string_FindChr(char* in_pStr, char in_Chr)
{
	if (in_pStr == NULL)
		return -1;

	char* pTmp = strchr(in_pStr, in_Chr);
	if (pTmp == NULL)
		return -1;

	return pTmp - in_pStr;
}

/// <summary>
/// ����	 :	�����ַ����е�һ��ƥ���Ӵ����±�
/// ����	 :	in_pStr			�ַ���
///			in_Src			��Ӧ�Ӵ�
/// ����ֵ:  >= 0 ����
/// </summary>
int string_FindStr(char* in_pStr, char* in_Src)
{
	if (in_pStr == NULL || in_Src == NULL)
		return -1;;

	char* pTmp = strstr(in_pStr, in_Src);
	if (pTmp == NULL)
		return -1;

	return pTmp - in_pStr;

}

/// <summary>
/// ����	 :	�����ַ����д�iFromIndex��ʼ��ƥ���Ӵ����±�
/// ����	 :	in_pStr			�ַ���
///			iFromIndex		��ʼ�±�
///			in_Src			��Ӧ�Ӵ�
/// ����ֵ:  >= 0 ����
/// </summary>
int string_FindStrFrom(char* in_pStr, int iFromIndex, char* in_Src)
{
	if (in_pStr == NULL || in_Src == NULL || iFromIndex < 0)
		return -1;

	if (iFromIndex >= (int)strlen(in_pStr))
		return -1;

	char* pTmp = strstr(in_pStr + iFromIndex, in_Src);
	if (pTmp == NULL)
		return -1;

	return pTmp - in_pStr;
}



/// <summary>
/// ����	 :	�ַ����ַ��滻
/// ����	 :	in_pStr			�ַ���
///			in_Src			Դ
///			in_Desc			�滻���ַ�
/// ����ֵ:  
/// </summary>
int string_ReplaceChr(char *in_out_pStr, char in_Src, char in_Desc)
{
	if (in_out_pStr == NULL)
		return eAEC_Input;

	char* pTmp = in_out_pStr;
	while ((pTmp = strchr(pTmp, in_Src)) != NULL)
	{
		*pTmp = in_Desc;
		pTmp++;
	}
	return eAEC_Success;
}


/// <summary>
/// ����	 :	�ַ����Ӵ��滻
/// ����	 :	in_pStr			�ַ���
///			in_Src			Դ
///			in_Desc			�滻���ַ�
///			out_pResult		����ַ���
///			in_ResultLen	����ַ�������
/// ����ֵ:  
/// </summary>
int string_ReplaceStr(char *in_pStr, char* in_Src, char* in_Desc, char* out_pResult, int in_ResultLen)
{
	if (in_pStr == NULL || in_Src == NULL || out_pResult == NULL || in_ResultLen <= 0)
		return eAEC_Input;

	memset(out_pResult, 0, in_ResultLen);

	//���㳤��
	int iLen_pStr = strlen(in_pStr);
	int iLen_src = strlen(in_Src);
	int iLen_desc = in_Desc ? strlen(in_Desc) : 0;
	int iLen_add = iLen_desc - iLen_src > 0 ? iLen_desc - iLen_src : 0;

	//�������յ��ַ�������
	int iCount = string_CountStr(in_pStr, in_Src);
	int iLen_result = iLen_pStr + 1 + iCount * iLen_add;
	if (iLen_result > in_ResultLen)
		return eAEC_BufferOver;

	int iCopyLen = 0;
	int iResultLen = 0;
	int iIndex = 0;
	int iFromIndex = 0;
	while ((iIndex = string_FindStrFrom(in_pStr, iFromIndex, in_Src)) >= 0)
	{
		//[in_pStr + iFromIndex] --Copy--> [out_pResult]
		iCopyLen = iIndex - iFromIndex;
		memcpy(out_pResult + iResultLen, in_pStr + iFromIndex, iCopyLen);
		iResultLen += iCopyLen;

		//[in_Desc] --Copy--> [out_pResult]
		if (iLen_desc > 0)
		{
			memcpy(out_pResult + iResultLen, in_Desc, iLen_desc);
			iResultLen += iLen_desc;
		}

		iFromIndex += iCopyLen + iLen_src;
	}

	memcpy(out_pResult + iResultLen, in_pStr + iFromIndex, iLen_pStr - iFromIndex);
	return eAEC_Success;
}



/// <summary>
/// ����	 :	�Ƴ��Ӵ�
/// ����	 :	in_out_pStr		�ַ���
///			in_Src			�Ӵ�
/// ����ֵ:  >= 0 ����
/// </summary>
int string_Remove(char *in_out_pStr, char* in_Src)
{
	if (in_out_pStr == NULL || in_Src == NULL)
		return eAEC_Input;

	int iLen = strlen(in_out_pStr) + 1;
	char* pBuf = (char*)string_Malloc(NULL, NULL, iLen);
	
	string_ReplaceStr(in_out_pStr, in_Src, NULL, pBuf, iLen);
	memcpy(in_out_pStr, pBuf, iLen);
	free(pBuf);
	return eAEC_Success;
}

/// <summary>
/// ����	 :	�����ַ���
/// ����	 :	in_pStr			�ַ���
///			in_iIndex		�����±�
///			in_Src			�����Ӵ�
///			out_pResult		����ַ���
///			in_ResultLen	����ַ�������
/// ����ֵ: 
/// </summary>
int string_Insert(char* in_pStr, int in_iIndex, char* in_Src, char* out_pResult, int in_ResultLen)
{
	if (in_pStr == NULL || in_Src == NULL || in_iIndex < 0 || out_pResult == NULL || in_ResultLen <= 0)
		return eAEC_Input;

	memset(out_pResult, 0, in_ResultLen);

	//���㳤��
	int iLen_pStr = strlen(in_pStr);
	int iLen_src = strlen(in_Src);
	int iLen_result = iLen_pStr + iLen_src + 1;
	if (iLen_result > in_ResultLen)
		return eAEC_BufferOver;

	//�������λ��
	in_iIndex = in_iIndex > iLen_pStr ? iLen_pStr : in_iIndex;

	memcpy(out_pResult, in_pStr, in_iIndex);
	memcpy(out_pResult + in_iIndex, in_Src, iLen_src);
	memcpy(out_pResult + in_iIndex + iLen_src, in_pStr + in_iIndex, iLen_pStr - in_iIndex);
	return eAEC_Success;
}



/// <summary>
/// ����	 :	�ַ������
/// ����	 :	in_out_pResult	����ַ���
/// ����ֵ: 
/// </summary>
int string_Strcat(char* in_out_pResult, ...)
{
	if (in_out_pResult == NULL)
		return eAEC_Input;

	//���㳤��
	char* pString;
	va_list pList;
	va_start(pList, in_out_pResult);
	while (1)
	{
		pString = va_arg(pList, char*);
		if (pString == NULL)
			break;

		strcat(in_out_pResult, pString);
	}

	return eAEC_Success;
}

/// <summary>
/// ����	 :	�ߵ��ַ���˳��
/// ����	 :	in_out_pResult	����ַ���
/// ����ֵ: 
/// </summary>
int string_MakeReverse(char* in_out_pStr)
{
	if (in_out_pStr == NULL)
		return eAEC_Input;

	char cSrc;
	int iLen = strlen(in_out_pStr);
	for (int i = 0; i < iLen / 2; i++)
	{
		cSrc = in_out_pStr[i];
		in_out_pStr[i] = in_out_pStr[iLen - i - 1];
		in_out_pStr[iLen - i - 1] = cSrc;
	}

	return eAEC_Success;
}

/// <summary>
/// ����	 :	��ȡ�ַ���
/// ����	 :	in_pStr			�ַ���
///			in_iIndex		��ʼ�±�
///			in_Length		����
///			out_pResult		����ַ���
///			in_ResultLen	����ַ�������
/// ����ֵ: 
/// </summary>
int string_Substring(char* in_pStr, int in_iIndex, int in_Length, char* out_pResult, int in_ResultLen)
{
	if (in_pStr == NULL || in_iIndex < 0 || in_Length <= 0 || in_ResultLen < in_Length || out_pResult == NULL)
		return eAEC_Input;

	memset(out_pResult, 0, in_ResultLen);

	//���㳤��
	int iLen_pStr = strlen(in_pStr);
	if (iLen_pStr <= in_iIndex)
		return eAEC_Input;

	int iLen = strlen(in_pStr + in_iIndex);
	in_Length = in_Length > iLen ? iLen : in_Length;

	memcpy(out_pResult, in_pStr + in_iIndex, in_Length);
	out_pResult[in_Length - 1] = '\0';
	return eAEC_Success;
}


/// <summary>
/// ����	 :	��split����,��ȡ�ֶ�����
/// ����	 :	in_pStr			�ַ���
///			in_Chr			�ַ�
/// ����ֵ: 
/// </summary>
int string_GetFieldNum(char* in_pStr, char in_Chr)
{
	if (in_pStr == NULL)
		return 0;

	if (strlen(in_pStr) == 0)
		return 0;

	return string_CountChr(in_pStr, in_Chr) + 1;
}

/// <summary>
/// ����	 :	��ȡ��N���ֶ�
/// ����	 :	in_pStr			�ַ���
///			in_Chr			�ַ�
///			in_Order		�ֶ����
///			out_pResult		����ַ���
///			in_ResultLen	����ַ�������
/// ����ֵ: 
/// </summary>
int string_GetFieldSting(char* in_pStr, char in_Chr, int in_Order, char* out_pResult, int in_ResultLen)
{
	if (in_pStr == NULL || in_Order < 0 || out_pResult == NULL || in_ResultLen <= 0)
		return eAEC_Input;

	memset(out_pResult, 0, in_ResultLen);
	int iCount = string_GetFieldNum(in_pStr, in_Chr);
	if (in_Order >= iCount)
		return -1;

	//��ȡ��ʼλ�úͽ���λ��
	char* pStart = in_pStr;
	char* pTmp = in_pStr;
	for (int i = 0; i <= in_Order; i++)
	{
		pStart = pTmp;
		pTmp = strchr(pTmp, in_Chr);
		if (pTmp == NULL)
		{
			pTmp = in_pStr + strlen(in_pStr)+1;
			break;
		}
		pTmp++;
	}

	//���㳤��
	int iLen = pTmp == NULL ? 1 : pTmp - pStart;
	if (iLen > in_ResultLen)
		return eAEC_Creat;

	strncpy(out_pResult, pStart, iLen - 1);
	out_pResult[iLen - 1] = '\0';
	return eAEC_Success;
}

/// <summary>
/// ����	 :	��ȡ���ּ���
/// ����	 :	in_pStr			�ַ���
///			in_Chr			�ַ�
///			pArray			����
///			lArrayLength	���ϴ�С
/// ����ֵ:  ��������
/// </summary>
int string_GetFieldNumberSting(char* in_pStr, char in_Chr, long* pArray, long lArrayLength)
{
	long i, lValue, lCount, bValid;
	lCount = 0;
	lValue = 0;
	bValid = 0;

	if (in_pStr == NULL || strlen(in_pStr) <= 0 || pArray == NULL || lArrayLength <= 0)
		return eAEC_Input;

	memset(pArray, 0x00, sizeof(long)*lArrayLength);
	for (i = 0; i<1024; i++)
	{
		if (!in_pStr[i])
			break;
		if (lCount >= lArrayLength)
			break;
		switch (in_pStr[i])
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			bValid++;
			lValue *= 10;
			lValue += (in_pStr[i] - '0');
			break;
		default:
			if (in_Chr == in_pStr[i])
			{
				if (bValid)
				{
					pArray[lCount] = lValue;
					lCount++;
				}
				bValid = 0;
				lValue = 0;
			}
			break;
		}
	}
	if (bValid)
	{
		if (lCount<lArrayLength)
		{
			pArray[lCount] = lValue;
			lCount++;
		}
	}
	return lCount;
}




/// <summary>
/// ����	 :	�ڴ滺������
/// ����	 :	pBuffer:				��ʹ�õ��ڴ滺��
///			in_out_BufferLen:		��ʹ�õ��ڴ滺���С
///			iNewLen:				������Ĵ�С
/// ����ֵ:  
/// </summary>
void* string_Malloc(void* pBuffer, int* in_out_BufferLen, int iNewLen)
{
	if (iNewLen < 0)
		return NULL;

	void* pRet = pBuffer;
	int iLen = in_out_BufferLen ? *in_out_BufferLen : 0;
	if (iLen < iNewLen)
	{
		if (pRet)
			free(pRet);
		pRet = malloc(iNewLen);
		iLen = iNewLen;
	}

	memset(pRet, 0, iLen);
	if (in_out_BufferLen)
		*in_out_BufferLen = iLen;
	return pRet;
}

/// <summary>
/// ����	 :	�ڴ滺����������
/// ����	 :	pBuffer:				��ʹ�õ��ڴ滺��
///			in_out_BufferLen:		��ʹ�õ��ڴ滺���С
///			iNewLen:				������Ĵ�С
/// ����ֵ:  
/// </summary>
void* string_Realloc(void* pBuffer, int* in_out_BufferLen, int iNewLen)
{
	if (in_out_BufferLen ==	NULL || *in_out_BufferLen < 0 || iNewLen < 0)
		return NULL;

	void* pTmp = pBuffer;
	void* pRet = pBuffer;
	int iLen = *in_out_BufferLen;
	if (iLen < iNewLen)
	{
		pRet = malloc(iNewLen);
		iLen = iNewLen;

		memset(pRet, 0, iNewLen);
		if (pTmp)
		{
			memcpy(pRet, pTmp, *in_out_BufferLen);
			free(pTmp);
		}
	}

	*in_out_BufferLen = iLen;
	return pRet;
}

/// <summary>
/// ����	 :	�ڴ滺���ͷ�
/// ����	 :	in_pStr:				��ʹ�õ��ڴ滺��
/// ����ֵ:  
/// </summary>
void string_Free(void** in_pStr)
{
	if (*in_pStr)
	{
		free(*in_pStr);
		*in_pStr = NULL;
	}
}

/// <summary>
/// ����	 :	�ж��ַ����Ƿ�Ϊ�մ�
/// ����	 :	in_pStr:				�ַ���
/// ����ֵ:  
/// </summary>
int string_IsNullOrEmpty(char *in_pStr)
{
	if (in_pStr == NULL)
		return AIG_TRUE;

	int iLen = strlen(in_pStr);
	if (iLen == 0)
		return AIG_TRUE;
	for (int i = 0; i < iLen; i++)
	{
		if (strchr(AIG_STRING_EMPTY, in_pStr[i]) == NULL)
			return AIG_FALSE;
	}
	return AIG_TRUE;
}

/// <summary>
/// ����	 :	�����ַ�������
/// ����	 :	in_pStr				�ַ���
///			IsUnicode			�Ƿ�Ϊ���ַ�
/// ����ֵ:  
/// </summary>
int string_GetLen(char* in_pStr, int IsUnicode)
{
	if (in_pStr == NULL)
		return 0;

	if (IsUnicode == AIG_FALSE)
		return strlen(in_pStr);
	else
#ifdef _WIN32
		return wcslen((unsigned short*)in_pStr);
#endif

	return 0;
}

