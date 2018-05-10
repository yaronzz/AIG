#include <stdio.h>
#include "StringHelper.h"
#include "PathHelper.h"


int main(int argc, char* argv[])
{
	int iCheck;
	int iCount;
	AigFileAttribute aFileAttr;
	char sText[100] = { "abababTextbbb" };
	char sText2[100] = { "ababab" };
	char sText3[100] = {"\0"};


	iCheck = path_GetFullPath("Test", sText3, 100);

	iCount = path_GetFilesNum("E:\\1");
	for (int i = 0; i < iCount; i++)
	{
		iCheck = path_GetFilesAttr("E:\\1", i, &aFileAttr);
	}

	iCheck = string_Strcat(sText3, "aa", "bb", "cc");
	iCheck = string_Insert(sText2, 12, "TTT", sText3, 100);
	iCheck = string_ReplaceStr(sText, "ab", NULL, sText3, 100);
	iCheck = string_LeftTrim(sText2, "ab");
	iCheck = string_RightTrim(sText2, "ab");
	iCheck = string_CountChr(sText, 'b');
	return 0;
}
