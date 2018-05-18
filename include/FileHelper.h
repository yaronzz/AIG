#if !defined __AIG_FILE_H__
#define __AIG_FILE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"


typedef enum _enumAigFileRight
{
	eAFileRight_ReadOnly	= 1,	//ֻ��
	eAFileRight_Hide		= 2, 	//����
	eAFileRight_System		= 4, 	//ϵͳ

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

/// <summary>
/// ����	 :	��ȡ����·���ļ���
/// ����	 :	pFilePath	 [in] ·���ļ���
///			pBakString	 [in] �����ַ���
///			pOutPath	 [out]���·��
///			iOutPathLen	 [in] ���·������
/// ����ֵ:
/// </summary>
int file_GetBakFilePath(char* pFilePath, char* pBakString, char* pOutPath, int iOutPathLen);


#ifdef __cplusplus
}
#endif

#endif  //__AIG_FILE_H__