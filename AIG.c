#include <stdio.h>
#include "StringHelper.h"
int main(int argc, char* argv[])
{
	int iCheck;
	char sText[100] = { "abababTextbbb" };
	char sText2[100] = { "ababab" };
	char sText3[100] = {"\0"};


	iCheck = string_Strcat(sText3, "aa", "bb", "cc");
	iCheck = string_Insert(sText2, 12, "TTT", sText3, 100);
	iCheck = string_ReplaceStr(sText, "ab", NULL, sText3, 100);
	iCheck = string_LeftTrim(sText2, "ab");
	iCheck = string_RightTrim(sText2, "ab");
	iCheck = string_CountChr(sText, 'b');
	return 0;
}

