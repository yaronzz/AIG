#if !defined __AIG_ARGV_H__
#define __AIG_ARGV_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"
#include "StringHelper.h"

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

int argv_ParseString(AigArgvHandle* pHandle, char* pString);

#ifdef __cplusplus
}
#endif

#endif  //__AIG_ARGV_H__