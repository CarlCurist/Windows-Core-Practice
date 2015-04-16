// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "tlhelp32.h"
#include "stdio.h"

void EnumProcess()
{
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcess == INVALID_HANDLE_VALUE)
	{
		printf("枚举进程失败");
		return;
	}
	else
	{
		PROCESSENTRY32 procEntry = { 0 };
		procEntry.dwSize = sizeof(PROCESSENTRY32);
		BOOL bRet = Process32First(hProcess, &procEntry);
		while (bRet)
		{
			wprintf(L"PID: %d (%s)\n ", procEntry.th32ProcessID, procEntry.szExeFile);
			bRet = Process32Next(hProcess, &procEntry);
		}
	}
	CloseHandle(hProcess);
}
BOOL Terminate(DWORD PID)
{
	printf("%u", PID);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	if (hProcess == NULL)
	{
		printf("打开终止进程句柄失败\n");
		DWORD Error=GetLastError();
		printf("错误代码为：%u\n", Error);
		return FALSE;
	}
	if (!TerminateProcess(hProcess, 0))
	{
		printf("终止进程失败\n");
		DWORD Error = GetLastError();
		printf("错误代码为：%u\n", Error);
		return FALSE;
	}
	printf("进程结束成功\n");
	return TRUE;
}
int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR szBuf[50];
	while (1)
	{
		printf("输入“enum”枚举当前进程，输入“exit”退出程序，输入进程PID结束该进程\n");
		wscanf_s(L"%ls", szBuf, _countof(szBuf));
		if (!wcscmp(szBuf, TEXT("exit")))
			break; 
		if (!wcscmp(szBuf, TEXT("enum")))
		{
			EnumProcess();
			continue;
		}
		//以上都不是，则输入为一个进程的PID
		DWORD ProcessPID = (DWORD)_wtol((wchar_t *)szBuf);//把TCHAR转换成DWORD
		Terminate(ProcessPID);
	}
	return 0;
}

