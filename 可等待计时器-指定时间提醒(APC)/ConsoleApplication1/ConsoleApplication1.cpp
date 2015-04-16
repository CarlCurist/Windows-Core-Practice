// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//������ϸ�����ڡ�windows���ı�̡�P249

#include "stdafx.h"
#include<cstdio>
#include<windows.h>
#include <mmsystem.h> // ���ϣ���ȻPlaySound�����޷�ʹ��
#pragma comment(lib, "WINMM.LIB") // ���ϣ���ȻPlaySound�����޷�ʹ��

VOID APIENTRY TimerAPC(PVOID pvArgTOComletionRoutine,DWORD dwTimerLowValue,DWORD dwTimerHighValue)
{
	FILETIME ftUTC, ftLocal;
	SYSTEMTIME st;
	TCHAR szBuf[256];

	ftUTC.dwHighDateTime = dwTimerHighValue;
	ftUTC.dwLowDateTime = dwTimerLowValue;

	FileTimeToLocalFileTime(&ftUTC, &ftLocal);
	FileTimeToSystemTime(&ftLocal, &st);

	GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &st, NULL, szBuf, _countof(szBuf));
	_tcscat_s(szBuf, _countof(szBuf), TEXT(" "));
	GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st, NULL, _tcschr(szBuf, TEXT('\0')), (int)(_countof(szBuf) - _tcslen(szBuf)));
	
	PlaySound(TEXT("F:\\Complicated.wav"), NULL, SND_FILENAME | SND_ASYNC);
	MessageBox(NULL, szBuf, TEXT("timer"), MB_OK);
}
int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
	//LARGE_INTEGER li = { 0 };
	int Second;
	printf("������Ҫ�ڶ����������\n");
	scanf_s("%d", &Second);
	LARGE_INTEGER li;
	const int nTimerUnitsPerSecond = 10000000;
	li.QuadPart = -(Second * nTimerUnitsPerSecond);
	SetWaitableTimer(hTimer, &li, 0, TimerAPC, NULL, TRUE);
	SleepEx(INFINITE, TRUE);

	CloseHandle(hTimer);
	return 0;
}

