// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<windows.h>
#include<cstdio>
#include<cstring>

char data[50];
int DataLong = 0;
HANDLE hRead,hOk,hDo;

DWORD WINAPI ReadData(PVOID pvParam)
{
	DWORD dwResult = 0;
	int temp1 = 0;
	scanf_s("%s", data, _countof(data));
	DataLong = strlen(data);

	SetEvent(hOk);
	return dwResult;
}
DWORD WINAPI Do(PVOID pvParam)
{
	DWORD dwResult = 0;
	WaitForSingleObject(hOk, INFINITE);
	char tempchar;
	for (int temp1 = 0; temp1 < DataLong/2; temp1++)
	{
		tempchar = data[temp1];
		data[temp1] = data[DataLong - 1 - temp1];
		data[DataLong - 1 - temp1] = tempchar;
	}
	printf("%s", data);
	ResetEvent(hOk);
	return dwResult;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int temp1;
	hOk = CreateEvent(NULL, TRUE, FALSE, NULL);
	while (1)
	{
		hRead = CreateThread(NULL, 0, ReadData, NULL, 0, NULL);
		hDo = CreateThread(NULL, 0, Do, NULL, 0, NULL);
		WaitForSingleObject(hRead, INFINITE);
		WaitForSingleObject(hDo, INFINITE);
		CloseHandle(hDo);
		CloseHandle(hRead);
		printf("\n");
	}
	CloseHandle(hOk);


	return 0;
}

