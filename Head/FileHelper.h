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
/// 功能：递归新建目录
/// 返回值：非0表示失败
/// </summary>
int file_Mkdirs(char* pPath);

/// <summary>
/// 功能：获取文件大小
/// 返回值：小于0表示失败
/// </summary>
long file_GetFileLen(char* pPath);

/// <summary>
/// 功能：设置文件属性
/// 返回值：非0表示错误
/// </summary>
int file_SetFileAttributes(char *pPath, enumAigFileRight eType);

/// <summary>
/// 功能：文件是否存在
///	返回值：AIG_TRUE-存在
/// </summary>
int file_IsFileExist(char* pPath);




//备份目录
int file_BakDir(char* pSrcPath, char* pDescPath);


/// <summary>
/// 功能：获取绝对路径
/// 参数：pFilePath:			原始路径
///	说明：返回值需要人工释放
/// </summary>
char* file_GetFullPath(char* pFilePath);


/***************************************************************************************************************************
关于路径和文件名、扩展名
***************************************************************************************************************************/
char* file_GetDirectoryName(char* pPath);				//获取文件所在目录
char* file_GetFileName(char* pPath);					//获取文件名
char* file_GetFileNameWithoutExtension(char* pPath);	//获取文件名(不带扩展名)
char* file_GetExtension(char* pPath);					//获取文件扩展名
char* file_GetPathRoot(char* pPath);					//获取根目录



/***************************************************************************************************************************
功能：配置文件操作
文件内容样式：
            #备注/解释
            【xxx】
             xxx = yyy
***************************************************************************************************************************/
#define AIG_FILE_PROFILE_LINE_MAXLEN	1024	//配置文件的行最大长度
#define AIG_FILE_PROFILE_NOTE_FLAG		"#;；"	//配置文件的注释行标志
//读写配置文件
//参数：pHandle	文件句柄
//	   pGroup   小组名(【】表示)
//     pKey     关键字
//	   pValue   字符串值
//     fValue   整型值
//     fDefault 默认值(当没有找到关键字时或关键字后没有值时,以默认值返回)
//返回值：0正确
int   file_InitProfile(void** pHandle,char* pFileName);														//初始化
int   file_UnintProfile(void** pHandle);																	//逆初始化

int   file_SaveProfile(void* pHandle);																		//保存
int   file_SaveAsProfile(void* pHandle, char* pFileName);													//另存为

int   file_WriteProfileString(void* pHandle, char* pGroup, char* pKey, char* pValue,char* pComment);		//写入字符串值
int   file_WriteProfileFloat(void* pHandle, char* pGroup, char* pKey, float fValue, char* pComment);		//写入浮点数

char* file_ReadProfileString(void* pHandle, char* pGroup, char* pKey);										//读取字符串值
float file_ReadProfileFloat(void* pHandle, char* pGroup, char* pKey);										//读取浮点数

int   file_RemoveProfileAllKey(void* pHandle);																//删除全部关键字
int   file_RemoveProfileGroup(void* pHandle, char* pGroup);													//删除小组
int   file_RemoveProfileKey(void* pHandle, char* pGroup, char* pKey);										//删除某一个关键字

#ifdef __cplusplus
}
#endif

#endif  //__AIG_FILE_H__