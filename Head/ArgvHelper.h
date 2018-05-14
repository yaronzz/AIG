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
	char			sBuffer[AIG_MAXLEN_ARGVBUFF];			 //�ڴ�ռ�
	int				iBufferSize;							 //�ڴ�ռ�ĳ���
	char			*pTail;									 //ָ���ڴ�ռ�β��
	int				iRemain;								 //�ڴ�ռ仹ʣ�µĳ���	
	long			NumParams;								 //��ǰ��������
	AigParamPairPtr	pParamList[AIG_MAXLEN_ARGVNUM];
}AigArgvHandle;

int argv_ParseString(AigArgvHandle* pHandle, char* pString);

#ifdef __cplusplus
}
#endif

#endif  //__AIG_ARGV_H__