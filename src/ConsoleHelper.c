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

#include "ConsoleHelper.h"

typedef struct _AigConsoleHanlde
{
	int iX;				//开始的光标点
	int iY;				
	int iIndex;			//第几次Refresh
	int iMaxNum;		//总数量
	int iOnlyText;		//是否只显示文本
	char pDesc[1024];
}AigConsoleHanlde;

/// <summary>
/// 功能	 :	获取光标坐标
/// 参数	 :	iX			[out] 坐标X
///			iY			[out] 坐标Y
/// 返回值: 
/// </summary>
int console_GetPositionXY(int* iX, int* iY)
{
	if (iX == NULL || iY == NULL)
		return eAEC_Input;

#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE pHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(pHandle, &info);
	*iX = info.dwCursorPosition.X;	
	*iY = info.dwCursorPosition.Y;
	return eAEC_Success;
#endif

	return eAEC_Err;
}

/// <summary>
/// 功能	 :	设置光标坐标
/// 参数	 :	iX			[in] 坐标X
///			iY			[in] 坐标Y
/// 返回值: 
/// </summary>
int console_SetPositionXY(int iX, int iY)
{
#ifdef _WIN32
	COORD pos;
	HANDLE pHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = (short)iX;
	pos.Y = (short)iY;
	SetConsoleCursorPosition(pHandle, pos);
	return eAEC_Success;
#endif

	return eAEC_Err;
}

/// <summary>
/// 功能	 :	进度条初始化
/// 参数	 :	pHandle			[in-out] 句柄
///			pDesc			[in]	 描述
///			iMaxNum			[in]	 最大数量
///			iOnlyText		[in]	 只显示文本
/// 返回值: 
/// </summary>
int console_ProgressOpen(void** pHandle, char* pDesc, int iMaxNum, int iOnlyText)
{
	if (pHandle == NULL || iMaxNum <= 0)
		return eAEC_Input;

	AigConsoleHanlde* pConsoleHandle = (AigConsoleHanlde*)AIG_FUNC_MALLOC(sizeof(AigConsoleHanlde));
	console_GetPositionXY(&pConsoleHandle->iX, &pConsoleHandle->iY);
	pConsoleHandle->iOnlyText = iOnlyText;
	pConsoleHandle->iMaxNum = iMaxNum;
	pConsoleHandle->iIndex = 0;
	
	memset(pConsoleHandle->pDesc, 0, 1024);
	if (pDesc)
		sprintf(pConsoleHandle->pDesc, "%s", pDesc);

	*pHandle = pConsoleHandle;
	return eAEC_Success;
}

/// <summary>
/// 功能	 :	进度条释放
/// 参数	 :	pHandle			[in-out] 句柄
/// 返回值: 
/// </summary>
void console_ProgressClose(void** pHandle)
{
	if (*pHandle)
		AIG_FUNC_FREE(*pHandle);
}

/// <summary>
/// 功能	 :	刷新进度条
/// 参数	 :	pHandle			[in] 句柄
///			CurNum			[in] 当前数量
/// 返回值: 
/// </summary>
void console_ProgressRefresh(void* pHandle, int CurNum)
{
	AigConsoleHanlde* pConsoleHandle = (AigConsoleHanlde*)pHandle;
	
	int iX, iY;
	int iNum;
	char sBar[25];
	char sIndex[6] = "-\\|/\0";

	if (CurNum > pConsoleHandle->iMaxNum)
		CurNum = pConsoleHandle->iMaxNum;
	if (CurNum < 0)
		CurNum = 0;

	//退格
	console_GetPositionXY(&iX, &iY);
	iNum = iX - pConsoleHandle->iX;
	for (int i = 0; i < iNum; i++)
		printf("\b");

	//输出描述文本
	if (pConsoleHandle->pDesc[0] != '\0')
		printf("%s ", pConsoleHandle->pDesc);

	//显示进度
	printf("%d\\%d ", pConsoleHandle->iMaxNum, CurNum);

	if (pConsoleHandle->iOnlyText == AIG_FALSE)
	{
		memset(sBar, 0, sizeof(sBar));
		sBar[0] = '[';
		sBar[1] = sIndex[pConsoleHandle->iIndex++ % 4];

		iNum = CurNum * 100 / pConsoleHandle->iMaxNum;
		for (int i = 0; i < iNum / 10; i++)
			sBar[i + 2] = '>';
		for (int i = iNum / 10; i < 10; i++)
			sBar[i + 2] = ' ';

		printf("%s %d%%]", sBar, iNum);
	}
}


