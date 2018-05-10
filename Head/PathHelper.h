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
/// 功能	 :	查看目录下文件和文件夹的数量
/// 参数	 :	pPath	 [in] 路径
/// 返回值:  数量
/// </summary>
int path_GetFilesNum(char* pPath);

/// <summary>
/// 功能	 :	查看目录下文件和文件夹的属性
/// 参数	 :	pPath	 [in] 路径
///			iOrder	 [in] 序号
///			aAttr	 [out]属性
/// 返回值:
/// </summary>
int path_GetFilesAttr(char* pPath, int iOrder, AigFileAttribute* aAttr);



/// <summary>
/// 功能	 :	是否为相对目录
/// 参数	 :	pPath	 [in] 路径
/// 返回值:
/// </summary>
int path_IsRelativePath(char* pPath);

/// <summary>
/// 功能	 :	获取绝对路径
/// 参数	 :	pPath			[in] 路径
///			pOutPath		[out]输出路径
///			iOutPathLen		[in] 输出路径长度
/// 返回值:
/// </summary>
int path_GetFullPath(char* pPath, char* pOutPath, int iOutPathLen);

#ifdef __cplusplus
}
#endif

#endif 
