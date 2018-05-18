#if !defined __AIG_ARGV_H__
#define __AIG_ARGV_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"

#define AIG_MAXLEN_ARGVBUFF 2048
#define AIG_MAXLEN_ARGVNUM  256

typedef struct _AigParamPairPtr
{
	char* sName;
	char* sValue;
}AigParamPairPtr;

typedef struct _AigArgvHandle
{
	char			sBuffer[AIG_MAXLEN_ARGVBUFF];			 //内存空间
	int				iBufferSize;							 //内存空间的长度
	char			*pTail;									 //指向内存空间尾部
	int				iRemain;								 //内存空间还剩下的长度	
	long			NumParams;								 //当前参数数量
	AigParamPairPtr	pParamList[AIG_MAXLEN_ARGVNUM];
}AigArgvHandle;

/// <summary>
/// 功能	 :	解析字符串
/// 参数	 :	pHandle			[in-out]	句柄
///			pString			[in]		字符串
/// 返回值:  >= 0成功
/// </summary>
int argv_ParseString(AigArgvHandle* pHandle, char* pString);

/// <summary>
/// 功能	 :	解析Main参
/// 参数	 :	pHandle			[in-out]	句柄
///			argc			[in]		Main参数量
///			argv			[in]		Main参数组
/// 返回值:  >= 0成功
/// </summary>
int argv_ParseMainPara(AigArgvHandle* pHandle, int argc, char * argv[]);

#ifdef __cplusplus
}
#endif

#endif  //__AIG_ARGV_H__