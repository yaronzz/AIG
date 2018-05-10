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
int path_GetFilesNum(char* pPath);

/// <summary>
/// ����	 :	�鿴Ŀ¼���ļ����ļ��е�����
/// ����	 :	pPath	 [in] ·��
///			iOrder	 [in] ���
///			aAttr	 [out]����
/// ����ֵ:
/// </summary>
int path_GetFilesAttr(char* pPath, int iOrder, AigFileAttribute* aAttr);



/// <summary>
/// ����	 :	�Ƿ�Ϊ���Ŀ¼
/// ����	 :	pPath	 [in] ·��
/// ����ֵ:
/// </summary>
int path_IsRelativePath(char* pPath);

/// <summary>
/// ����	 :	��ȡ����·��
/// ����	 :	pPath			[in] ·��
///			pOutPath		[out]���·��
///			iOutPathLen		[in] ���·������
/// ����ֵ:
/// </summary>
int path_GetFullPath(char* pPath, char* pOutPath, int iOutPathLen);

#ifdef __cplusplus
}
#endif

#endif 
