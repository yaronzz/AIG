#if !defined __AIG_CONSOLE_H__
#define __AIG_CONSOLE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"

/// <summary>
/// 功能	 :	获取光标坐标
/// 参数	 :	iX			[out] 坐标X
///			iY			[out] 坐标Y
/// 返回值: 
/// </summary>
int console_GetPositionXY(int* iX, int* iY);

/// <summary>
/// 功能	 :	设置光标坐标
/// 参数	 :	iX			[in] 坐标X
///			iY			[in] 坐标Y
/// 返回值: 
/// </summary>
int console_SetPositionXY(int iX, int iY);

/// <summary>
/// 功能	 :	进度条初始化
/// 参数	 :	pHandle			[in-out] 句柄
///			pDesc			[in]	 描述
///			iMaxNum			[in]	 最大数量
///			iOnlyText		[in]	 只显示文本
/// 返回值: 
/// </summary>
int console_ProgressOpen(void** pHandle, char* pDesc, int iMaxNum, int iOnlyText);

/// <summary>
/// 功能	 :	进度条释放
/// 参数	 :	pHandle			[in-out] 句柄
/// 返回值: 
/// </summary>
void console_ProgressClose(void** pHandle);

/// <summary>
/// 功能	 :	刷新进度条
/// 参数	 :	pHandle			[in] 句柄
///			CurNum			[in] 当前数量
/// 返回值: 
/// </summary>
void console_ProgressRefresh(void* pHandle, int CurNum);

#ifdef __cplusplus
}
#endif

#endif  //__AIG_CONSOLE_H__