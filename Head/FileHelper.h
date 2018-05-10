#if !defined __AIG_FILE_H__
#define __AIG_FILE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"
#include "StringHelper.h"

typedef enum _enumAigFileRight
{
	eAFileRight_ReadOnly,	//ֻ��
	eAFileRight_Hide, 		//����

}enumAigFileRight;

/// <summary>
/// ����	 :	�½�Ŀ¼
/// ����	 :	pPath	 [in] ·��
/// ����ֵ:
/// </summary>
int file_Mkdirs(char* pPath);

/// <summary>
/// ����	 :	��ȡ�ļ��ĳ���
/// ����	 :	pPath	 [in] ·��
/// ����ֵ:
/// </summary>
long file_GetFileLen(char* pPath);

/// <summary>
/// ����	 :	�����ļ�Ȩ��
/// ����	 :	pPath	 [in] ·��
/// ����ֵ:
/// </summary>
int file_SetFileRight(char *pPath, enumAigFileRight eType);

/// <summary>
/// ����	 :	�鿴�ļ��Ƿ����
/// ����	 :	pPath	 [in] ·��
/// ����ֵ:
/// </summary>
int file_IsFileExist(char* pPath);





#ifdef __cplusplus
}
#endif

#endif  //__AIG_FILE_H__