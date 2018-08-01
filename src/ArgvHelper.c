#include "StringHelper.h"
#include "ArgvHelper.h"

/// <summary>
/// 功能	 :	句柄初始化
/// 参数	 :	pHandle			[in—out]	 句柄
/// 返回值:  
/// </summary>
static void argv_HandleInit(AigArgvHandle* pHandle)
{
	memset(pHandle, 0x00, sizeof(AigArgvHandle));
	pHandle->iBufferSize	= AIG_MAXLEN_ARGVBUFF;
	pHandle->pTail			= pHandle->sBuffer;
	pHandle->iRemain		= AIG_MAXLEN_ARGVBUFF;
}

/// <summary>
/// 功能	 :	获取参数数量
/// 参数	 :	sString			[in]	 字符串
/// 返回值:  
/// </summary>
static int argv_GetFieldNum(char* sString)
{
	int iNumInterval1 = string_CountChr(sString, '\'');
	int iNumInterval2 = string_CountChr(sString, '"');
	int iNumField	  = string_CountChr(sString, ' ');

	if (iNumInterval1 == 0 && iNumInterval2 == 0)
		return iNumField + 1;

	//如果为单数则错误
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
/// 功能	 :	获取第N个字段
/// 参数	 :	sString			[in]	 字符串
///			iOrder			[in]	 序号
///			pField			[in-out] 输出字段
///			iFieldLen		[in]	 输出字段长度
/// 返回值:  >= 0成功
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

	//如果为单数则错误
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
					//如果最后一个字符是'或者"，则需要去掉
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
/// 功能	 :	解析字符串
/// 参数	 :	pHandle			[in-out]	 句柄
///			pString			[in]		字符串
/// 返回值:  >= 0成功
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

	//初始化
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

		//赋值
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
/// 功能	 :	解析Main参
/// 参数	 :	pHandle			[in-out]	 句柄
///			argc			[in]		 Main参数量
///			argv			[in]		 Main参数组
/// 返回值:  >= 0成功
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