#if !defined __AIG_PATH_H__
#define __AIG_PATH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"
#include "TimeHelper.h"
#include "StringHelper.h"

typedef struct _AigFileAttribute
{
	int bIsDirectory;
	AigSystemTime CreatTime;
	AigSystemTime LastAccessTime;
	AigSystemTime LastWriteTime;
	char FileName[AIG_MAXLEN_FILENAME];

}AigFileAttribute;

/// <summary>
/// ����	 :	�鿴Ŀ¼���ļ����ļ��е�����
/// ����	 :	pPath	 [in] ·��
/// ����ֵ:  ����
/// </summary>
int path_GetFilesNumInDirectory(char* pPath);

/// <summary>
/// ����	 :	�鿴Ŀ¼���ļ����ļ��е�����
/// ����	 :	pPath	 [in] ·��
///			iOrder	 [in] ���
///			aAttr	 [out]����
/// ����ֵ:
/// </summary>
int path_GetFilesAttrInDirectory(char* pPath, int iOrder, AigFileAttribute* aAttr);



/// <summary>
/// ����	 :	�Ƿ�Ϊ���Ŀ¼
/// ����	 :	pPath	 [in] ·��
/// ����ֵ:
/// </summary>
int path_IsRelativePath(char* pPath);

/// <summary>
/// ����	 :	��ȡ��ǰ����Ŀ¼
/// ����	 :	pOutPath		[out]���·��
///			iOutPathLen		[in] ���·������
/// ����ֵ:
/// </summary>
int path_GetWorkPath(char* pOutPath, int iOutPathLen);

/// <summary>
/// ����	 :	��ȡ����·��
/// ����	 :	pPath			[in] ·��
///			pOutPath		[out]���·��
///			iOutPathLen		[in] ���·������
/// ����ֵ:
/// </summary>
int path_GetFullPath(char* pPath, char* pOutPath, int iOutPathLen);



/// <summary>
/// ����	 :	��ȡ·���е��ļ���
/// ����	 :	pFilePath		[in] ·���ļ���
///			pName			[out]����ļ���
///			iNameLen		[in] ����ļ�������
///	����	 :  C:\\JiYF\\BenXH\\BenXHCMS.xml --> BenXHCMS.xml
/// ����ֵ:
/// </summary>
int path_GetFileName(char* pFilePath, char* pName, int iNameLen);

/// <summary>
/// ����	 :	��ȡ·���е��ļ���(������չ��)
/// ����	 :	pFilePath		[in] ·���ļ���
///			pName			[out]����ļ���
///			iNameLen		[in] ����ļ�������
///	����	 :  C:\\JiYF\\BenXH\\BenXHCMS.xml --> BenXHCMS
/// ����ֵ:
/// </summary>
int path_GetFileNameWithoutExtension(char* pFilePath, char* pName, int iNameLen);

/// <summary>
/// ����	 :	��ȡ·���е��ļ���չ��
/// ����	 :	pFilePath		[in] ·���ļ���
///			pName			[out]����ļ���
///			iNameLen		[in] ����ļ�������
///	����	 :  C:\\JiYF\\BenXH\\BenXHCMS.xml --> .xml
/// ����ֵ:
/// </summary>
int path_GetExtensionName(char* pFilePath, char* pName, int iNameLen);

/// <summary>
/// ����	 :	��ȡ·���е�·��
/// ����	 :	pFilePath		[in] ·���ļ���
///			pName			[out]����ļ���
///			iNameLen		[in] ����ļ�������
///	����	 :  C:\\JiYF\\BenXH\\BenXHCMS.xml --> C:\\JiYF\\BenXH\\
/// ����ֵ:
/// </summary>
int path_GetDirectoryName(char* pFilePath, char* pName, int iNameLen);

#ifdef __cplusplus
}
#endif

#endif 
