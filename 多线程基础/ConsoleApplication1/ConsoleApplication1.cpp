// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<cstdio>
#include<windows.h>

int count = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD WINAPI Thread1(PVOID pvParam);
	DWORD WINAPI Thread2(PVOID pvParam);

	HANDLE Thread[2];
	Thread[0] = CreateThread(NULL, 0, Thread1, NULL, 0, NULL);
	Thread[1] = CreateThread(NULL, 0, Thread2, NULL, 0, NULL);
	WaitForMultipleObjects(2, Thread, TRUE, INFINITE);
	CloseHandle(Thread[0]);
	CloseHandle(Thread[1]);
	Sleep(1000);
	printf("%d", count);
	return 0;
}
DWORD WINAPI Thread1(PVOID pvParam)
{
	DWORD dwResult = 0;
	count++;
	return dwResult;
}
DWORD WINAPI Thread2(PVOID pvParam)
{
	DWORD dwResult = 0;
	Sleep(2000);
	count += 2;
	return dwResult;
}
