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
	char			sBuffer[AIG_MAXLEN_ARGVBUFF];			 //�ڴ�ռ�
	int				iBufferSize;							 //�ڴ�ռ�ĳ���
	char			*pTail;									 //ָ���ڴ�ռ�β��
	int				iRemain;								 //�ڴ�ռ仹ʣ�µĳ���	
	long			NumParams;								 //��ǰ��������
	AigParamPairPtr	pParamList[AIG_MAXLEN_ARGVNUM];
}AigArgvHandle;

/// <summary>
/// ����	 :	�����ַ���
/// ����	 :	pHandle			[in-out]	���
///			pString			[in]		�ַ���
/// ����ֵ:  >= 0�ɹ�
/// </summary>
int argv_ParseString(AigArgvHandle* pHandle, char* pString);

/// <summary>
/// ����	 :	����Main��
/// ����	 :	pHandle			[in-out]	���
///			argc			[in]		Main������
///			argv			[in]		Main������
/// ����ֵ:  >= 0�ɹ�
/// </summary>
int argv_ParseMainPara(AigArgvHandle* pHandle, int argc, char * argv[]);

#ifdef __cplusplus
}
#endif

#endif  //__AIG_ARGV_H__