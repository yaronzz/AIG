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
	int iX;				//��ʼ�Ĺ���
	int iY;				
	int iIndex;			//�ڼ���Refresh
	int iMaxNum;		//������
	int iOnlyText;		//�Ƿ�ֻ��ʾ�ı�
	char pDesc[1024];
}AigConsoleHanlde;

/// <summary>
/// ����	 :	��ȡ�������
/// ����	 :	iX			[out] ����X
///			iY			[out] ����Y
/// ����ֵ: 
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
/// ����	 :	���ù������
/// ����	 :	iX			[in] ����X
///			iY			[in] ����Y
/// ����ֵ: 
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
/// ����	 :	��������ʼ��
/// ����	 :	pHandle			[in-out] ���
///			pDesc			[in]	 ����
///			iMaxNum			[in]	 �������
///			iOnlyText		[in]	 ֻ��ʾ�ı�
/// ����ֵ: 
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
/// ����	 :	�������ͷ�
/// ����	 :	pHandle			[in-out] ���
/// ����ֵ: 
/// </summary>
void console_ProgressClose(void** pHandle)
{
	if (*pHandle)
		AIG_FUNC_FREE(*pHandle);
}

/// <summary>
/// ����	 :	ˢ�½�����
/// ����	 :	pHandle			[in] ���
///			CurNum			[in] ��ǰ����
/// ����ֵ: 
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

	//�˸�
	console_GetPositionXY(&iX, &iY);
	iNum = iX - pConsoleHandle->iX;
	for (int i = 0; i < iNum; i++)
		printf("\b");

	//��������ı�
	if (pConsoleHandle->pDesc[0] != '\0')
		printf("%s ", pConsoleHandle->pDesc);

	//��ʾ����
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


