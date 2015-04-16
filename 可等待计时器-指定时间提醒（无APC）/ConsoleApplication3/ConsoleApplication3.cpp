// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<windows.h>
#include<cstdio>

HANDLE hTimer = NULL;

DWORD WINAPI timeout(PVOID pvParam)
{
	DWORD dwResult = 0;
	WaitForSingleObject(hTimer, INFINITE);
	MessageBox(NULL, TEXT("123"), TEXT("123"), MB_OK);
	return dwResult;
}
int _tmain(int argc, _TCHAR* argv[])
{
	hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
	HANDLE hThread = CreateThread(NULL, 0, timeout, NULL, 0, NULL);
	int Second;
	printf("请输入要在多少秒后提醒\n");
	scanf_s("%d", &Second);
	LARGE_INTEGER li;
	const int nTimerUnitsPerSecond = 10000000;//一秒等于一千万个100纳秒
	li.QuadPart = -(Second * nTimerUnitsPerSecond);
	SetWaitableTimer(hTimer, &li, 0, NULL, NULL, FALSE);
	SleepEx(INFINITE, TRUE);

	CloseHandle(hTimer);
	CloseHandle(hThread);

	return 0;
}

