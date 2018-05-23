// AIG.cpp : 定义控制台应用程序的入口点。
//

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


	return 0;
}

