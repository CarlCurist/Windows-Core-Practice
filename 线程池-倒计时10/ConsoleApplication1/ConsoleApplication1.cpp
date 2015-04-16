// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<windows.h>
#include<cstdio>

int count = 10;

VOID CALLBACK TimeCallback(PTP_CALLBACK_INSTANCE pInstance, PVOID pvContext, PTP_TIMER pTimer)
{
	printf("%d\n", count--);
}

int _tmain(int argc, _TCHAR* argv[])
{
	ULARGE_INTEGER ul;
	ul.QuadPart = (LONGLONG)-(10000000);
	FILETIME ft;
	//ft.dwHighDateTime = ul.HighPart;
	//ft.dwLowDateTime = ul.LowPart;
	ft.dwHighDateTime = 0;
	ft.dwLowDateTime = -1;

	PTP_TIMER timer = CreateThreadpoolTimer(TimeCallback, NULL, NULL);
	SetThreadpoolTimer(timer, &ft, 1000, 0);
	//WaitForThreadpoolTimerCallbacks(timer, FALSE);
	//CloseThreadpoolTimer(timer);
	while (1)
	{
		if (count == 0)
		{
			CloseThreadpoolTimer(timer);
			break;
		}
	}
	return 0;
}

