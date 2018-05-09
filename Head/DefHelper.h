#if !defined __AIG_DEF_H__
#define __AIG_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32  
#include <windows.h>
#include <io.h>  
#elif linux || (__LYNX
#include <unistd.h>  
#include <sys/time.h>
#endif 

#define AIG_DEBUG
#define AIG_NORELEASE				//表示还还没实现
#define AIG_TRUE			1		//正确
#define AIG_FALSE			0		//错误
#define AIG_MAXLEN_FILEPATH	1024	//目录名的最大长度

typedef int KEYPTR;
typedef int(*pfn_AIG_CMP_CALLBACK)(void* in_pKeyA, void* in_pKeyB);						//关键字比较回调函数（0相等,>0 A>B,<0 A<B）
typedef int(*pfn_AIG_CMP_CALLBACK2)(void* in_pKeyA, void* in_pKeyB, int in_KeyLen);		//关键字比较回调函数（0相等,>0 A>B,<0 A<B）


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

	eAEC_ParaNumOver		= 20,	//参数个数超出限制
	eAEC_BufferOver			= 21,	//空间溢出
	eAEC_HandleNoLoad		= 22,	//句柄未装载过参数
	eAEC_OptErr				= 23,	//Opt格式错误
	eAEC_PwdLenOver	        = 24,   //密码长度超过了限制
	eAEC_PwdErr             = 25,   //密码错误

}AIG_ERRORCODE;


#ifdef __cplusplus
}
#endif

#endif  //__AIG_DEF_H__