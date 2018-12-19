// AIG.cpp : 定义控制台应用程序的入口点。
//
#include "stdio.h"

#include "ArgvHelper.h"
#include "ListHelper.h"
#include "StringHelper.h"
#include "HashHelper.h"
#if 0
int main(int argc, char * argv[])
{
	int iCheck;
	AigArgvHandle aArgvHandle;
	unsigned char sText1[1024];
	unsigned char sText2[1024] = "Test";
	unsigned char sText3[1024];
	unsigned char* pFind;
	unsigned char* pKey;
	unsigned char* pValue;
	int iArrary[10] = { 6, 2, 4, 8, 9, 1, 5, 7, 3 };

	iCheck = argv_ParseString(&aArgvHandle, "Test.exe A=1 B=2");
	iCheck = argv_ParseString(&aArgvHandle, "Test.exe \"A=1 2\" B=2");

	void* pHashHandle;
	pHashHandle = hash_Creat(sizeof(int), sizeof(int), 10, string_MemoryCmp,NULL);
	for (int i = 0; i < 9; i++)
		hash_Insert(pHashHandle, iArrary + i, iArrary + i, 1);

	pFind = hash_Find(pHashHandle, iArrary + 4);
	hash_SetOut(pHashHandle);
	while (hash_GetNext(pHashHandle, &pKey, &pValue) == eAEC_Success)
		iCheck ++;

	hash_Remove(pHashHandle, iArrary + 2);
	pFind = hash_Find(pHashHandle, iArrary + 2);

	return 0;
}
#endif
