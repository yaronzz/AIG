#include "ArgvHelper.h"

static void argv_HandleInit(AigArgvHandle* pHandle)
{
	memset(pHandle, 0x00, sizeof(AigArgvHandle));
	pHandle->iBufferSize = AIG_MAXLEN_ARGVBUFF;
	pHandle->pTail = pHandle->sBuffer;
	pHandle->iRemain = AIG_MAXLEN_ARGVBUFF;
}

static void argv_GetField(char* sString, int iOrder, char* pField)
{
	int iLen;
	int iTotalLen;
	int iIndex;
	int iStart, iEnd;
	int iIsInInterval;

	iIndex = 0;
	iStart = -1;
	iEnd = -1;
	iTotalLen = strlen(sString);
	iIsInInterval = 0;
	for (int i = 0; i < iTotalLen; i++)
	{
		switch (sString[i])
		{
		//在''和""之间的空格不用拆分
		case '\'':
		case '"':
			if (iIsInInterval)
			{
				iEnd = i - 1;
				iIsInInterval = 0;
				if (i == iTotalLen - 1 && iIndex == iOrder)
				{
					iLen = iEnd - (iStart - 1);
					memcpy(pField, sString + iStart, sizeof(char) * iLen);
					pField[iLen] = '\0';
				}
				break;
			}
			else
			{
				iStart = i + 1;
				iIsInInterval = 1;
				break;
			}
		default:
			if ((!iIsInInterval && sString[i] == ' ') || i == iTotalLen - 1)
			{
				if (iIndex == iOrder)
				{
					iLen = iEnd - (iStart - 1);
					memcpy(pField, sString + iStart, sizeof(char) * iLen);
					pField[iLen] = '\0';
					break;
				}

				iIndex++;
				iStart = i + 1;

			}
		}
	}
	
	long lCount, lFallIn;
	long lBegin, lEnd, lLastCharValid;
	unsigned long i, lTotal;

	//lCount = 0;
	//lTotal = strlen(sString);
	//lBegin = -1;
	//lEnd = -1;
	//lFallIn = 0;
	//lLastCharValid = 1;
	//for (i = 0; i<lTotal; i++)
	//{
	//	switch (sString[i])
	//	{
	//	case '\'':
	//	case '"':
	//		if (lFallIn)
	//		{
	//			lEnd = i - 1;
	//			lFallIn = 0;
	//			if (i<lTotal - 1)
	//			{
	//				break;
	//			}
	//			else
	//			{
	//				lLastCharValid = 0;
	//			}
	//		}
	//		else
	//		{
	//			if (lBegin == -1) // 2009-4-24
	//				lBegin = i + 1;
	//			lFallIn = 1;
	//			break;
	//		}
	//	default:
	//		// 2009-4-24
	//		if (!lFallIn&&sString[i] == cDivider
	//			|| i == (lTotal - 1))
	//		{
	//			if (lBegin != -1) /* 2006-6-9 */
	//			{
	//				if (i == lTotal - 1
	//					&& lLastCharValid)
	//					lEnd = i;
	//				lCount++;

	//				lBegin = -1;
	//				lEnd = -1;
	//			}
	//			else if (i == lTotal - 1 && sString[i] != cDivider)
	//			{
	//				// 2009-6-25 只有一个有效字符的情况
	//				lBegin = i;
	//				lEnd = i;

	//				lCount++;
	//			}
	//		}
	//		if (-1 == lBegin
	//			&& sString[i] != cDivider)
	//			lBegin = i;
	//		if (-1 != lBegin)
	//			lEnd = i;
	//		break;
	//	}
	//}
	return lCount;
}



int argv_ParseString(AigArgvHandle* pHandle, char* pString)
{
	if (pHandle == NULL || pString == NULL)
		return eAEC_Input;

	char* pCur;

	//初始化
	if (pHandle->iBufferSize != AIG_MAXLEN_ARGVBUFF)
		argv_HandleInit(pHandle);

	pCur = pHandle->pTail;



	return eAEC_Success;
}
