#if !defined __AIG_FILE_H__
#define __AIG_FILE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"
#include "StringHelper.h"

typedef enum _enumAigFileRight
{
	eAFileRight_ReadOnly,	//只读
	eAFileRight_Hide, 		//隐藏

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





#ifdef __cplusplus
}
#endif

#endif  //__AIG_FILE_H__