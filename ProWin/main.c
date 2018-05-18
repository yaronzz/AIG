// AIG.cpp : 定义控制台应用程序的入口点。
//

#include "DesHelper.h"
#include "ArgvHelper.h"
int main(int argc, char * argv[])
{
	int iCheck;
	AigArgvHandle aArgvHandle;
	unsigned char sText1[1024];
	unsigned char sText2[1024] = "Test";
	unsigned char sText3[1024];

	iCheck = argv_ParseString(&aArgvHandle, "Test.exe A=1 B=2");
	iCheck = argv_ParseString(&aArgvHandle, "Test.exe \"A=1 2\" B=2");

	des_BlockEncrypt(sText1, sText2, 5);
	iCheck = strlen(sText1);
	des_BlockDecrypt(sText3, sText1, strlen(sText1));
	return 0;
}

