#if !defined __AIG_FILE_H__
#define __AIG_FILE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"


typedef enum _enumAigFileRight
{
	eAFileRight_ReadOnly	= 1,	//只读
	eAFileRight_Hide		= 2, 	//隐藏
	eAFileRight_System		= 4, 	//系统

}enumAigFileRight;

/// <summary>
/// 功能	 :	新建目录
/// 参数	 :	pPath	 [in] 路径
/// 返回值:
/// </summary>
int file_Mkdirs(char* pPath);

/// <summary>
/// 功能	 :	获取文件的长度
/// 参数	 :	pPath	 [in] 路径
/// 返回值:
/// </summary>
long file_GetFileLen(char* pPath);

/// <summary>
/// 功能	 :	设置文件权限
/// 参数	 :	pPath	 [in] 路径
/// 返回值:
/// </summary>
int file_SetFileRight(char *pPath, enumAigFileRight eType);

/// <summary>
/// 功能	 :	查看文件是否存在
/// 参数	 :	pPath	 [in] 路径
/// 返回值:
/// </summary>
int file_IsFileExist(char* pPath);

/// <summary>
/// 功能	 :	获取备份路径文件名
/// 参数	 :	pFilePath	 [in] 路径文件名
///			pBakString	 [in] 备份字符串
///			pOutPath	 [out]输出路径
///			iOutPathLen	 [in] 输出路径长度
/// 返回值:
/// </summary>
int file_GetBakFilePath(char* pFilePath, char* pBakString, char* pOutPath, int iOutPathLen);


#ifdef __cplusplus
}
#endif

#endif  //__AIG_FILE_H__