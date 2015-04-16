// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<Windows.h>
#include<cstdio>

int s[100];
HANDLE hMutex = NULL;

DWORD WINAPI read(PVOID pvParam)
{
	DWORD dwResult = 0;
	hMutex = CreateMutex(NULL, TRUE, NULL);
	for (int i = 0; i < 100; i++)
	{
		printf("%d", s[i]);
	}
	ReleaseMutex(hMutex);
	Sleep(INFINITE);
	return dwResult;
}
DWORD WINAPI write(PVOID pvParam)
{
	DWORD dwResult = 0;
	WaitForSingleObject(hMutex, INFINITE);
	for (int i = 0; i < 100; i++)
	{
		s[i] = 2;
	}
	return dwResult;
}
int _tmain(int argc, _TCHAR* argv[])
{
	for (int i = 0; i < 100; i++)
	{
		s[i] = 1;
	}
	HANDLE hRead = CreateThread(NULL, 0, read, NULL, 0, NULL);
	HANDLE hWrite = CreateThread(NULL, 0, write, NULL, 0, NULL);
	Sleep(1000);
	printf("\n");
	for (int i = 0; i < 100; i++)
	{
		printf("%d", s[i]);
	}
	Sleep(INFINITE);
	return 0;
}


