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
int path_GetFilesNumInDirectory(char* pPath);

/// <summary>
/// 功能	 :	查看目录下文件和文件夹的属性
/// 参数	 :	pPath	 [in] 路径
///			iOrder	 [in] 序号
///			aAttr	 [out]属性
/// 返回值:
/// </summary>
int path_GetFilesAttrInDirectory(char* pPath, int iOrder, AigFileAttribute* aAttr);



/// <summary>
/// 功能	 :	是否为相对目录
/// 参数	 :	pPath	 [in] 路径
/// 返回值:
/// </summary>
int path_IsRelativePath(char* pPath);

/// <summary>
/// 功能	 :	获取当前工作目录
/// 参数	 :	pOutPath		[out]输出路径
///			iOutPathLen		[in] 输出路径长度
/// 返回值:
/// </summary>
int path_GetWorkPath(char* pOutPath, int iOutPathLen);

/// <summary>
/// 功能	 :	获取绝对路径
/// 参数	 :	pPath			[in] 路径
///			pOutPath		[out]输出路径
///			iOutPathLen		[in] 输出路径长度
/// 返回值:
/// </summary>
int path_GetFullPath(char* pPath, char* pOutPath, int iOutPathLen);



/// <summary>
/// 功能	 :	获取路径中的文件名
/// 参数	 :	pFilePath		[in] 路径文件名
///			pName			[out]输出文件名
///			iNameLen		[in] 输出文件名长度
///	例子	 :  C:\\JiYF\\BenXH\\BenXHCMS.xml --> BenXHCMS.xml
/// 返回值:
/// </summary>
int path_GetFileName(char* pFilePath, char* pName, int iNameLen);

/// <summary>
/// 功能	 :	获取路径中的文件名(不带扩展名)
/// 参数	 :	pFilePath		[in] 路径文件名
///			pName			[out]输出文件名
///			iNameLen		[in] 输出文件名长度
///	例子	 :  C:\\JiYF\\BenXH\\BenXHCMS.xml --> BenXHCMS
/// 返回值:
/// </summary>
int path_GetFileNameWithoutExtension(char* pFilePath, char* pName, int iNameLen);

/// <summary>
/// 功能	 :	获取路径中的文件扩展名
/// 参数	 :	pFilePath		[in] 路径文件名
///			pName			[out]输出文件名
///			iNameLen		[in] 输出文件名长度
///	例子	 :  C:\\JiYF\\BenXH\\BenXHCMS.xml --> .xml
/// 返回值:
/// </summary>
int path_GetExtensionName(char* pFilePath, char* pName, int iNameLen);

/// <summary>
/// 功能	 :	获取路径中的路径
/// 参数	 :	pFilePath		[in] 路径文件名
///			pName			[out]输出文件名
///			iNameLen		[in] 输出文件名长度
///	例子	 :  C:\\JiYF\\BenXH\\BenXHCMS.xml --> C:\\JiYF\\BenXH\\
/// 返回值:
/// </summary>
int path_GetDirectoryName(char* pFilePath, char* pName, int iNameLen);

#ifdef __cplusplus
}
#endif

#endif 
