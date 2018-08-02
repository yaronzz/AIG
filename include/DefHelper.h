#if !defined __AIG_DEF_H__
#define __AIG_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <time.h>
#include <io.h>
#include <direct.h>
#endif

#if defined(__linux) || defined(linux) || defined(__LYNX)
#include <unistd.h>
#include <dirent.h>
#include <stdarg.h>
#include <time.h>
#include <strings.h>
#include <sys/stat.h>
#endif

#define AIG_DEBUG
#define AIG_NORELEASE				//表示还还没实现
#define AIG_TRUE			1		//正确
#define AIG_FALSE			0		//错误
#define AIG_MAXLEN_FILEPATH	1024	//目录名的最大长度
#define AIG_MAXLEN_FILENAME 256		//文件名的最大长度

#define AIG_FUNC_MALLOC malloc		//申请内存
#define AIG_FUNC_FREE	free		//释放内存
typedef int(*pfn_AIG_CMP_CALLBACK)(void* in_pKeyA, void* in_pKeyB, int in_KeyLen);		//关键字比较回调函数（0相等,>0 A>B,<0 A<B）


//错误码
typedef enum _AIG_ERRORCODE
{
	eAEC_Err				= -1,
	eAEC_Success			= 0,
	eAEC_Malloc				= 1,	//申请内存空间失败
	eAEC_Input				= 2,	//输入参数错误
	eAEC_Open				= 3,	//打开文件失败
	eAEC_Mkdir				= 4,	//新建文件夹失败
	eAEC_Creat				= 5,	//新建文件失败
	eAEC_NoFile				= 6,	//文件不存在
	eAEC_NoDir				= 7,	//目录不存在
	eAEC_PathOver			= 8,	//路径长度溢出
	eAEC_IndexOver			= 9,	//下标溢出
	eAEC_End				= 10,	//结束

	eAEC_ParaNumOver		= 20,	//参数个数超出限制
	eAEC_BufferOver			= 21,	//空间溢出
	eAEC_HandleNoLoad		= 22,	//句柄未装载过参数
	eAEC_OptErr				= 23,	//Opt格式错误
	eAEC_PwdLenOver	        = 24,   //密码长度超过了限制
	eAEC_PwdErr             = 25,   //密码错误
	eAEC_InvalidTime		= 26,	//无效的时间
	eAEC_AlreadyExist		= 27,	//已经存在
	eAEC_TimeOut			= 28,	//超时

}AIG_ERRORCODE;


#ifdef __cplusplus
}
#endif

#endif  //__AIG_DEF_H__
