#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <time.h>
#include <io.h>
#include <direct.h>
#endif

#if defined(__linux) || defined(linux) || defined(__LYNX)
#include <unistd.h>
#include <dirent.h>
#include <stdarg.h>
#include <time.h>
#include <strings.h>
#include <sys/stat.h>
#endif

#include "StringHelper.h"


/// <summary>
/// 功能	 :	去掉字符序列左边的字符
/// 参数	 :	in_out_pStr		字符串输入与输出
///			remove_Chr		相应字符
/// 返回值:
/// </summary>
int string_LeftTrim(char* in_out_pStr, char* remove_Chr)
{
	if (in_out_pStr == NULL || remove_Chr == NULL)
		return eAEC_Input;

	//获取待删除的字符串长度
	int iIndex = 0;
	int iLen = strlen(in_out_pStr);
	for (iIndex = 0; iIndex < iLen; iIndex++)
	{
		if (strchr(remove_Chr, in_out_pStr[iIndex]) == NULL)
			break;
	}

	//位移
	int iOffset = iLen - iIndex;
	for (int i = 0; i < iOffset; i++)
	{
		in_out_pStr[i] = in_out_pStr[i + iIndex];
	}
	in_out_pStr[iOffset] = '\0';

	return eAEC_Success;
}

/// <summary>
/// 功能	 :	去掉字符序列右边的字符
/// 参数	 :	in_out_pStr		字符串输入与输出
///			remove_Chr		相应字符
/// 返回值:
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
/// 功能	 :	去掉字符序列左右边的字符
/// 参数	 :	in_out_pStr		字符串输入与输出
///			remove_Chr		相应字符
/// 返回值:
/// </summary>
int string_Trim(char* in_out_pStr, char* remove_Chr)
{
	if (in_out_pStr == NULL || remove_Chr == NULL)
		return eAEC_Input;

	int iCheck;
	//去除左边的空格,TAB和换行
	if ((iCheck = string_LeftTrim(in_out_pStr, remove_Chr)) != eAEC_Success)
		return iCheck;
	//去除右边的空格,TAB和换行
	if ((iCheck = string_RightTrim(in_out_pStr, remove_Chr)) != eAEC_Success)
		return iCheck;

	return eAEC_Success;
}



/// <summary>
/// 功能	 :	计算字符串中字符的数量
/// 参数	 :	in_pStr			字符串
///			in_Chr			相应字符
/// 返回值:
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
/// 功能	 :	计算字符串中子串的数量
/// 参数	 :	in_pStr			字符串
///			in_Src			相应子串
/// 返回值:
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
/// 功能	 :	查找字符串中第一个匹配字符的下标
/// 参数	 :	in_pStr			字符串
///			in_Chr			相应字符
/// 返回值:  >= 0 存在
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
/// 功能	 :	查找字符串中第一个匹配子串的下标
/// 参数	 :	in_pStr			字符串
///			in_Src			相应子串
/// 返回值:  >= 0 存在
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
/// 功能	 :	查找字符串中从iFromIndex开始的匹配子串的下标
/// 参数	 :	in_pStr			字符串
///			iFromIndex		开始下标
///			in_Src			相应子串
/// 返回值:  >= 0 存在
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
/// 功能	 :	字符串字符替换
/// 参数	 :	in_pStr			字符串
///			in_Src			源
///			in_Desc			替换的字符
/// 返回值:  
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
/// 功能	 :	字符串子串替换
/// 参数	 :	in_pStr			字符串
///			in_Src			源
///			in_Desc			替换的字符
///			out_pResult		输出字符串
///			in_ResultLen	输出字符串长度
/// 返回值:  
/// </summary>
int string_ReplaceStr(char *in_pStr, char* in_Src, char* in_Desc, char* out_pResult, int in_ResultLen)
{
	if (in_pStr == NULL || in_Src == NULL || out_pResult == NULL || in_ResultLen <= 0)
		return eAEC_Input;

	memset(out_pResult, 0, in_ResultLen);

	//计算长度
	int iLen_pStr = strlen(in_pStr);
	int iLen_src = strlen(in_Src);
	int iLen_desc = in_Desc ? strlen(in_Desc) : 0;
	int iLen_add = iLen_desc - iLen_src > 0 ? iLen_desc - iLen_src : 0;

	//计算最终的字符串长度
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
/// 功能	 :	移除子串
/// 参数	 :	in_out_pStr		字符串
///			in_Src			子串
/// 返回值:  >= 0 存在
/// </summary>
int string_Remove(char *in_out_pStr, char* in_Src)
{
	if (in_out_pStr == NULL || in_Src == NULL)
		return eAEC_Input;

	int iLen = strlen(in_out_pStr) + 1;
	char* pBuf = (char*)string_Malloc(NULL, NULL, iLen);
	
	string_ReplaceStr(in_out_pStr, in_Src, NULL, pBuf, iLen);
	memcpy(in_out_pStr, pBuf, iLen);
	AIG_FUNC_FREE(pBuf);
	return eAEC_Success;
}

/// <summary>
/// 功能	 :	插入字符串
/// 参数	 :	in_pStr			字符串
///			in_iIndex		插入下标
///			in_Src			插入子串
///			out_pResult		输出字符串
///			in_ResultLen	输出字符串长度
/// 返回值: 
/// </summary>
int string_Insert(char* in_pStr, int in_iIndex, char* in_Src, char* out_pResult, int in_ResultLen)
{
	if (in_pStr == NULL || in_Src == NULL || in_iIndex < 0 || out_pResult == NULL || in_ResultLen <= 0)
		return eAEC_Input;

	memset(out_pResult, 0, in_ResultLen);

	//计算长度
	int iLen_pStr = strlen(in_pStr);
	int iLen_src = strlen(in_Src);
	int iLen_result = iLen_pStr + iLen_src + 1;
	if (iLen_result > in_ResultLen)
		return eAEC_BufferOver;

	//计算插入位置
	in_iIndex = in_iIndex > iLen_pStr ? iLen_pStr : in_iIndex;

	memcpy(out_pResult, in_pStr, in_iIndex);
	memcpy(out_pResult + in_iIndex, in_Src, iLen_src);
	memcpy(out_pResult + in_iIndex + iLen_src, in_pStr + in_iIndex, iLen_pStr - in_iIndex);
	return eAEC_Success;
}



/// <summary>
/// 功能	 :	字符串相接
/// 参数	 :	in_out_pResult	输出字符串
/// 返回值: 
/// </summary>
int string_Strcat(char* in_out_pResult, ...)
{
	if (in_out_pResult == NULL)
		return eAEC_Input;

	//计算长度
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
	va_end(pList);

	return eAEC_Success;
}

/// <summary>
/// 功能	 :	颠倒字符串顺序
/// 参数	 :	in_out_pResult	输出字符串
/// 返回值: 
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
/// 功能	 :	截取字符串
/// 参数	 :	in_pStr			字符串
///			in_iIndex		开始下标
///			in_Length		长度
///			out_pResult		输出字符串
///			in_ResultLen	输出字符串长度
/// 返回值: 
/// </summary>
int string_Substring(char* in_pStr, int in_iIndex, int in_Length, char* out_pResult, int in_ResultLen)
{
	if (in_pStr == NULL || in_iIndex < 0 || in_Length <= 0 || in_ResultLen < in_Length || out_pResult == NULL)
		return eAEC_Input;

	memset(out_pResult, 0, in_ResultLen);

	//计算长度
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
/// 功能	 :	截取區間內的字符串
/// 参数	 :	in_pStr			字符串
///			in_cStartChr	開始字符
///			in_cEndChr		結束字符
///			out_pResult		输出字符串
///			in_ResultLen	输出字符串长度
/// 返回值: 
/// </summary>
int string_SubstringByInterval(char* in_pStr, char in_cStartChr, char in_cEndChr, char* out_pResult, int in_ResultLen)
{
	if (in_pStr == NULL || out_pResult == NULL || in_ResultLen <= 0)
		return eAEC_Input;

	char* pStart = strchr(in_pStr, in_cStartChr);
	char* pEnd = strchr(in_pStr, in_cEndChr);
	if (pStart == NULL || pEnd == NULL)
		return eAEC_Err;

	//如果開始字符和結束字符一樣的話，則結束字符要找第二個
	if (in_cStartChr == in_cEndChr)
	{
		pEnd = strchr(pStart + 1, in_cEndChr);
		if (pEnd == NULL)
			return eAEC_Err;
	}

	//計算長度
	int iLen = pEnd - pStart;
	if (iLen > in_ResultLen)
		return eAEC_BufferOver;

	memcpy(out_pResult, pStart + 1, iLen - 1);
	out_pResult[iLen - 1] = '\0';

	return eAEC_Success;
}

/// <summary>
/// 功能	 :	截取字符兩邊的字符串
/// 参数	 :	in_pStr			字符串
///			in_Chr			中間字符
///			out_pDesc1		输出字符串1
///			in_Desc1Len		输出字符串1长度
///			out_pDesc2		输出字符串2
///			in_Desc2Len		输出字符串2长度
/// 返回值: 
/// </summary>
int string_SubstringByChr(char* in_pStr, char in_Chr, char* out_pDesc1, int in_Desc1Len, char* out_pDesc2, int in_Desc2Len)
{
	if (in_pStr == NULL || out_pDesc1 == NULL || in_Desc1Len <= 0 || out_pDesc2 == NULL || in_Desc2Len <= 0)
		return eAEC_Input;

	char* pTemp = strchr(in_pStr, in_Chr);
	if (pTemp == NULL)
		return eAEC_Err;

	int iLen1 = pTemp - in_pStr + 1;
	int iLen2 = strlen(in_pStr) - iLen1 + 1;
	if (iLen1 > in_Desc1Len || iLen2 > in_Desc2Len)
		return eAEC_BufferOver;

	memcpy(out_pDesc1, in_pStr, iLen1 - 1);
	memcpy(out_pDesc2, pTemp + 1, iLen2 - 1);
	out_pDesc1[iLen1 - 1] = '\0';
	out_pDesc2[iLen2 - 1] = '\0';

	return eAEC_Success;
}


/// <summary>
/// 功能	 :	类split功能,获取字段数量
/// 参数	 :	in_pStr			字符串
///			in_Chr			字符
/// 返回值: 
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
/// 功能	 :	获取第N个字段
/// 参数	 :	in_pStr			字符串
///			in_Chr			字符
///			in_Order		字段序号
///			out_pResult		输出字符串
///			in_ResultLen	输出字符串长度
/// 返回值: 
/// </summary>
int string_GetFieldSting(char* in_pStr, char in_Chr, int in_Order, char* out_pResult, int in_ResultLen)
{
	if (in_pStr == NULL || in_Order < 0 || out_pResult == NULL || in_ResultLen <= 0)
		return eAEC_Input;

	memset(out_pResult, 0, in_ResultLen);
	int iCount = string_GetFieldNum(in_pStr, in_Chr);
	if (in_Order >= iCount)
		return -1;

	//获取起始位置和结束位置
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

	//计算长度
	int iLen = pTmp == NULL ? 1 : pTmp - pStart;
	if (iLen > in_ResultLen)
		return eAEC_Creat;

	strncpy(out_pResult, pStart, iLen - 1);
	out_pResult[iLen - 1] = '\0';
	return eAEC_Success;
}

/// <summary>
/// 功能	 :	获取数字集合
/// 参数	 :	in_pStr			字符串
///			in_Chr			字符
///			pArray			集合
///			lArrayLength	集合大小
/// 返回值:  集合数量
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
/// 功能	 :	内存交换
/// 参数	 :	pMemA	 [in-out] 缓存1
///			pMemB	 [in-out] 缓存2
///			iSize	 [in]     长度
/// 返回值:
/// </summary>
void string_MemorySwap(void* pMemA, void* pMemB, int iSize)
{
	unsigned char* pEleA = pMemA;
	unsigned char* pEleB = pMemB;
	unsigned char Tmp;

	while (iSize-- > 0)
	{
		Tmp = *pEleA;
		*pEleA++ = *pEleB;
		*pEleB++ = Tmp;
	}
}

/// <summary>
/// 功能	 :	内存比较
/// 参数	 :	pMemA	 [in] 缓存1
///			pMemB	 [in] 缓存2
///			iSize	 [in]     长度
/// 返回值:  0-相等 1A大 -1B大
/// </summary>
int string_MemoryCmp(void* pMemA, void* pMemB, int iSize)
{
	unsigned char* pEleA = pMemA;
	unsigned char* pEleB = pMemB;

	while (iSize-- > 0)
	{
		if (*pEleA == *pEleB)
		{
			pEleA++;
			pEleB++;
			continue;
		}

		return *pEleA > *pEleB ? 1 : -1;
	}

	return 0;
}

/// <summary>
/// 功能	 :	内存复制
/// 参数	 :	pDesc	 [out] 输出缓存
///			pSrc	 [in]  来源
///			iSize	 [in]  长度
/// 返回值:
/// </summary>
void string_MemoryCopy(void* pDesc, void* pSrc, int iSize)
{
	unsigned char* pEleA = pDesc;
	unsigned char* pEleB = pSrc;

	while (iSize-- > 0)
		*pEleA++ = *pEleB++;
}

/// <summary>
/// 功能	 :	内存缓冲申请
/// 参数	 :	pBuffer:				在使用的内存缓冲
///			in_out_BufferLen:		在使用的内存缓冲大小
///			iNewLen:				新申请的大小
/// 返回值:  
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
			AIG_FUNC_FREE(pRet);
		pRet = AIG_FUNC_MALLOC(iNewLen);
		iLen = iNewLen;
	}

	memset(pRet, 0, iLen);
	if (in_out_BufferLen)
		*in_out_BufferLen = iLen;
	return pRet;
}

/// <summary>
/// 功能	 :	内存缓冲重新申请
/// 参数	 :	pBuffer:				在使用的内存缓冲
///			in_out_BufferLen:		在使用的内存缓冲大小
///			iNewLen:				新申请的大小
/// 返回值:  
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
		pRet = AIG_FUNC_MALLOC(iNewLen);
		iLen = iNewLen;

		memset(pRet, 0, iNewLen);
		if (pTmp)
		{
			memcpy(pRet, pTmp, *in_out_BufferLen);
			AIG_FUNC_FREE(pTmp);
		}
	}

	*in_out_BufferLen = iLen;
	return pRet;
}

/// <summary>
/// 功能	 :	内存缓冲释放
/// 参数	 :	in_pStr:				在使用的内存缓冲
/// 返回值:  
/// </summary>
void string_Free(void** in_pStr)
{
	if (*in_pStr)
	{
		AIG_FUNC_FREE(*in_pStr);
		*in_pStr = NULL;
	}
}

/// <summary>
/// 功能	 :	判断字符串是否为空串
/// 参数	 :	in_pStr:				字符串
/// 返回值:  
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
/// 功能	 :	计算字符串长度
/// 参数	 :	in_pStr				字符串
///			IsUnicode			是否为宽字符
/// 返回值:  
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

/// <summary>
/// 功能	 :	字符串比较（不区分大小写）
/// 参数	 :	in_pStr1				字符串1
///			in_pStr2				符串2
/// 返回值:  
/// </summary>
int string_Stricmp(char* in_pStr1, char* in_pStr2)
{
#ifdef _WIN32
	return stricmp(in_pStr1,in_pStr2);
#endif

#if defined(__linux) || defined(linux) || defined(__LYNX)
	return strcasecmp(in_pStr1,in_pStr2);
#endif

}




/// <summary>
/// 功能	 :	编码转换
/// 参数	 :	pStr				字符串
///			pDesc				输出字符串
///			iDescLen			输出字符串长度
///			eType				转换类型
/// 返回值:  
/// </summary>
int string_ConvertEncodingFormat(char* pStr, char* pDesc, int iDescLen, enumAigEncodingConvert eType)
{
	if (pStr == NULL || pDesc == NULL || iDescLen <= 0)
		return eAEC_Input;

	int iLen;

#ifdef _WIN32
	switch (eType)
	{
	case eAEConv_AnsiToUnicode:
		iLen = MultiByteToWideChar(CP_ACP, 0, pStr, strlen(pStr), NULL, 0);
		if (iLen > iDescLen)
			return eAEC_BufferOver;

		MultiByteToWideChar(CP_ACP, 0, pStr, strlen(pStr), (LPWSTR)pDesc, iDescLen);
		pDesc[iLen] = '\0';
		break;
	case eAEConv_UnicodeToAnsi:
		iLen = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pStr, wcslen((LPCWSTR)pStr), NULL, 0, NULL, NULL);
		if (iLen > iDescLen)
			return eAEC_BufferOver;

		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pStr, wcslen((LPCWSTR)pStr), pDesc, iDescLen, NULL, NULL);
		pDesc[iLen] = '\0';
		break;
	}
#endif

	return eAEC_Success;
}