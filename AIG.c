#include <stdio.h>
#include "StringHelper.h"
#include "PathHelper.h"
#include "ProfileHelper.h"
#include "SortHelper.h"

int main(int argc, char* argv[])
{
	int iCheck;
	int iCount;
	AigFileAttribute aFileAttr;

#ifdef _WIN32
	char sPath2[100] = { "E:\\1" };
#elif linux || __LYNX
	char sPath2[100] = { "/home/AIG/trunk" };
#endif

	int  iArrary[20] = { 9, 3, 5, 8, 3, 5, 6, 1 };
	char sPath[100] = { "E:\\1\\Hello.ini" };
	char sText[100] = { "abababTextbbb" };
	char sText2[100] = { "ababab" };
	char sText3[1024] = {"\0"};

	iCheck = sort_Quick(iArrary, 8, sizeof(int), string_MemoryCmp);


	iCheck = profile_GetString("TEST", "KEY", NULL, sText3, sizeof(sText3), sPath);
	iCheck = profile_SetString("TEST", "KEY", "QQQ", sPath);

	iCheck = path_GetWorkPath(sText3, 1024);
	printf("%s\n", sText3);

	iCheck = path_GetFileName(sPath, sText3, 100);
	iCheck = path_GetFileNameWithoutExtension(sPath, sText3, 100);
	iCheck = path_GetExtensionName(sPath, sText3, 100);
	iCheck = path_GetDirectoryName(sPath, sText3, 100);

	iCheck = path_GetFullPath("Test", sText3, 100);
	iCount = path_GetFilesNumInDirectory(sPath2);
	printf("FileNum [%d]\n", iCount);
	for (int i = 0; i < iCount; i++)
	{
		iCheck = path_GetFilesAttrInDirectory(sPath2, i, &aFileAttr);

		printf("[%d] %s Time:%d-%d-%d %d-%d-%d\n", i, aFileAttr.FileName
			, aFileAttr.CreatTime.Year
			, aFileAttr.CreatTime.Month
			, aFileAttr.CreatTime.Day
			, aFileAttr.CreatTime.Hour
			, aFileAttr.CreatTime.Minute
			, aFileAttr.CreatTime.Second);
	}

	iCheck = string_Strcat(sText3, "aa", "bb", "cc");
	iCheck = string_Insert(sText2, 12, "TTT", sText3, 100);
	iCheck = string_ReplaceStr(sText, "ab", NULL, sText3, 100);
	iCheck = string_LeftTrim(sText2, "ab");
	iCheck = string_RightTrim(sText2, "ab");
	iCheck = string_CountChr(sText, 'b');
	return 0;
}
