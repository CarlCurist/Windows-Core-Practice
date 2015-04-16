// 注意：windows自身的文件好像注入不了，错误代码5，貌似是权限不够
//

#include "stdafx.h"
#include<windows.h>
#include<cstdio>

TCHAR DllAddress[255];
DWORD ProcessPID;

int _tmain(int argc, _TCHAR* argv[])
{
	printf("输入想要注入的DLL的地址\n");
	wscanf_s(L"%ls", DllAddress, _countof(DllAddress));
	printf("输入想要注入的进程的PID\n");
	scanf_s("%d", &ProcessPID);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessPID);

	if (hProcess == INVALID_HANDLE_VALUE)
		printf("打开注入进程失败\n");
	PWSTR pBuf = (PWSTR)VirtualAllocEx(hProcess, NULL, 1024, MEM_COMMIT, PAGE_READWRITE);
	if (pBuf == NULL)
		printf("为远程进程分配内存失败\n");
	if (!WriteProcessMemory(hProcess, pBuf, DllAddress, 255, NULL))
		printf("在远程进程读写失败\n");


	//获取LoadLibrary在目标函数的地址
	PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryW");
	if (pfnThreadRtn == NULL)
		printf("获取LoadLibrary地址失败\n");
	////

	HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, pfnThreadRtn, pBuf, 0, NULL);
	if (hRemoteThread == NULL)
		printf("创建远程线程失败\n");
	printf("%d", GetLastError());

	WaitForSingleObject(hRemoteThread, INFINITE);


	system("PAUSE");
	return 0;
}

