#if !defined __AIG_STRING_H__
#define __AIG_STRING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"

#define AIG_STRING_EMPTY "\t \n"	//空串标识 TAB\空格\换行


/// <summary>
/// 功能	 :	去掉字符序列左边的字符
/// 参数	 :	in_out_pStr		字符串输入与输出
///			remove_Chr		相应字符
/// 返回值:
/// </summary>
int string_LeftTrim(char* in_out_pStr, char* remove_Chr);

/// <summary>
/// 功能	 :	去掉字符序列右边的字符
/// 参数	 :	in_out_pStr		字符串输入与输出
///			remove_Chr		相应字符
/// 返回值:
/// </summary>
int string_RightTrim(char* in_out_pStr, char* remove_Chr);

/// <summary>
/// 功能	 :	去掉字符序列左右边的字符
/// 参数	 :	in_out_pStr		字符串输入与输出
///			remove_Chr		相应字符
/// 返回值:
/// </summary>
int string_Trim(char* in_out_pStr, char* remove_Chr);




/// <summary>
/// 功能	 :	计算字符串中字符的数量
/// 参数	 :	in_pStr			字符串
///			in_Chr			相应字符
/// 返回值:
/// </summary>
int string_CountChr(char* in_pStr, char in_Chr);

/// <summary>
/// 功能	 :	计算字符串中子串的数量
/// 参数	 :	in_pStr			字符串
///			in_Src			相应子串
/// 返回值:
/// </summary>
int string_CountStr(char* in_pStr, char* in_Src);




/// <summary>
/// 功能	 :	查找字符串中第一个匹配字符的下标
/// 参数	 :	in_pStr			字符串
///			in_Chr			相应字符
/// 返回值:  >= 0 存在
/// </summary>
int string_FindChr(char* in_pStr, char in_Chr);

/// <summary>
/// 功能	 :	查找字符串中第一个匹配子串的下标
/// 参数	 :	in_pStr			字符串
///			in_Src			相应子串
/// 返回值:  >= 0 存在
/// </summary>
int string_FindStr(char* in_pStr, char* in_Src);

/// <summary>
/// 功能	 :	查找字符串中从iFromIndex开始的匹配子串的下标
/// 参数	 :	in_pStr			字符串
///			iFromIndex		开始下标
///			in_Src			相应子串
/// 返回值:  >= 0 存在
/// </summary>
int string_FindStrFrom(char* in_pStr, int iFromIndex, char* in_Src);




/// <summary>
/// 功能	 :	字符串字符替换
/// 参数	 :	in_pStr			字符串
///			in_Src			源
///			in_Desc			替换的字符
/// 返回值:  
/// </summary>
int string_ReplaceChr(char *in_out_pStr, char in_Src, char in_Desc);

/// <summary>
/// 功能	 :	字符串子串替换
/// 参数	 :	in_pStr			字符串
///			in_Src			源
///			in_Desc			替换的字符
///			out_pResult		输出字符串
///			in_ResultLen	输出字符串长度
/// 返回值: 
/// </summary>
int string_ReplaceStr(char *in_pStr, char* in_Src, char* in_Desc, char* out_pResult, int in_ResultLen);




/// <summary>
/// 功能	 :	移除子串
/// 参数	 :	in_out_pStr		字符串
///			in_Src			子串
/// 返回值:  >= 0 存在
/// </summary>
int string_Remove(char *in_out_pStr, char* in_Src);

/// <summary>
/// 功能	 :	插入字符串
/// 参数	 :	in_pStr			字符串
///			in_iIndex		插入下标
///			in_Src			插入子串
///			out_pResult		输出字符串
///			in_ResultLen	输出字符串长度
/// 返回值: 
/// </summary>
int string_Insert(char* in_pStr, int in_iIndex, char* in_Src, char* out_pResult, int in_ResultLen);

/// <summary>
/// 功能	 :	字符串相接
/// 参数	 :	in_out_pResult	输出字符串
/// 返回值: 
/// </summary>
int string_Strcat(char* in_out_pResult, ...);

/// <summary>
/// 功能	 :	颠倒字符串顺序
/// 参数	 :	in_out_pResult	输出字符串
/// 返回值: 
/// </summary>
int string_MakeReverse(char* in_out_pStr);

/// <summary>
/// 功能	 :	截取字符串
/// 参数	 :	in_pStr			字符串
///			in_iIndex		开始下标
///			in_Length		长度
///			out_pResult		输出字符串
///			in_ResultLen	输出字符串长度
/// 返回值: 
/// </summary>
int string_Substring(char* in_pStr, int in_iIndex, int in_Length, char* out_pResult, int in_ResultLen);

/// <summary>
/// 功能	 :	截取區間內的字符串
/// 参数	 :	in_pStr			字符串
///			in_cStartChr	開始字符
///			in_cEndChr		結束字符
///			out_pResult		输出字符串
///			in_ResultLen	输出字符串长度
/// 返回值: 
/// </summary>
int string_SubstringByInterval(char* in_pStr, char in_cStartChr, char in_cEndChr, char* out_pResult, int in_ResultLen);

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
int string_SubstringByChr(char* in_pStr, char in_Chr, char* out_pDesc1, int in_Desc1Len, char* out_pDesc2, int in_Desc2Len);

/// <summary>
/// 功能	 :	类split功能,获取字段数量
/// 参数	 :	in_pStr			字符串
///			in_Chr			字符
/// 返回值: 
/// </summary>
int string_GetFieldNum(char* in_pStr, char in_Chr);

/// <summary>
/// 功能	 :	获取第N个字段
/// 参数	 :	in_pStr			字符串
///			in_Chr			字符
///			in_Order		字段序号
///			out_pResult		输出字符串
///			in_ResultLen	输出字符串长度
/// 返回值: 
/// </summary>
int string_GetFieldSting(char* in_pStr, char in_Chr, int in_Order, char* out_pResult, int in_ResultLen);

/// <summary>
/// 功能	 :	获取数字集合
/// 参数	 :	in_pStr			字符串
///			in_Chr			字符
///			pArray			集合
///			lArrayLength	集合大小
/// 返回值:  集合数量
/// </summary>
int string_GetFieldNumberSting(char* in_pStr, char in_Chr, long* pArray, long lArrayLength);




/// <summary>
/// 功能	 :	内存交换
/// 参数	 :	pMemA	 [in-out] 缓存1
///			pMemB	 [in-out] 缓存2
///			iSize	 [in]     长度
/// 返回值:
/// </summary>
void string_MemorySwap(void* pMemA, void* pMemB, int iSize);

/// <summary>
/// 功能	 :	内存比较
/// 参数	 :	pMemA	 [in] 缓存1
///			pMemB	 [in] 缓存2
///			iSize	 [in]     长度
/// 返回值:  0-相等 1A大 -1B大
/// </summary>
int string_MemoryCmp(void* pMemA, void* pMemB, int iSize);

/// <summary>
/// 功能	 :	内存复制
/// 参数	 :	pDesc	 [out] 输出缓存
///			pSrc	 [in]  来源
///			iSize	 [in]  长度
/// 返回值:
/// </summary>
void string_MemoryCopy(void* pDesc, void* pSrc, int iSize);

/// <summary>
/// 功能	 :	内存缓冲申请
/// 参数	 :	pBuffer:				在使用的内存缓冲
///			in_out_BufferLen:		在使用的内存缓冲大小
///			iNewLen:				新申请的大小
/// 返回值:  
/// </summary>
void* string_Malloc(void* pBuffer, int* in_out_BufferLen, int iNewLen);

/// <summary>
/// 功能	 :	内存缓冲重新申请
/// 参数	 :	pBuffer:				在使用的内存缓冲
///			in_out_BufferLen:		在使用的内存缓冲大小
///			iNewLen:				新申请的大小
/// 返回值:  
/// </summary>
void* string_Realloc(void* pBuffer, int* in_out_BufferLen, int iNewLen);

/// <summary>
/// 功能	 :	内存缓冲释放
/// 参数	 :	in_pStr:				在使用的内存缓冲
/// 返回值:  
/// </summary>
void string_Free(void** in_pStr);

/// <summary>
/// 功能	 :	判断字符串是否为空串
/// 参数	 :	in_pStr:				字符串
/// 返回值:  
/// </summary>
int string_IsNullOrEmpty(char *in_pStr);

/// <summary>
/// 功能	 :	计算字符串长度
/// 参数	 :	in_pStr					字符串
///			IsUnicode				是否为宽字符
/// 返回值:  
/// </summary>
int string_GetLen(char* in_pStr, int IsUnicode);






typedef enum _enumAigEncodingConvert
{
	eAEConv_AnsiToUnicode,
	eAEConv_UnicodeToAnsi,
}enumAigEncodingConvert;

/// <summary>
/// 功能	 :	编码转换
/// 参数	 :	pStr				字符串
///			pDesc				输出字符串
///			iDescLen			输出字符串长度
///			eType				转换类型
/// 返回值:  
/// </summary>
int string_ConvertEncodingFormat(char* pStr, char* pDesc, int iDescLen, enumAigEncodingConvert eType);



#ifdef __cplusplus
}
#endif

#endif  //__AIG_STRING_H__