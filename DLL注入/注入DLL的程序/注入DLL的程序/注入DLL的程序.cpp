// ע�⣺windows������ļ�����ע�벻�ˣ��������5��ò����Ȩ�޲���
//

#include "stdafx.h"
#include<windows.h>
#include<cstdio>

TCHAR DllAddress[255];
DWORD ProcessPID;

int _tmain(int argc, _TCHAR* argv[])
{
	printf("������Ҫע���DLL�ĵ�ַ\n");
	wscanf_s(L"%ls", DllAddress, _countof(DllAddress));
	printf("������Ҫע��Ľ��̵�PID\n");
	scanf_s("%d", &ProcessPID);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessPID);

	if (hProcess == INVALID_HANDLE_VALUE)
		printf("��ע�����ʧ��\n");
	PWSTR pBuf = (PWSTR)VirtualAllocEx(hProcess, NULL, 1024, MEM_COMMIT, PAGE_READWRITE);
	if (pBuf == NULL)
		printf("ΪԶ�̽��̷����ڴ�ʧ��\n");
	if (!WriteProcessMemory(hProcess, pBuf, DllAddress, 255, NULL))
		printf("��Զ�̽��̶�дʧ��\n");


	//��ȡLoadLibrary��Ŀ�꺯���ĵ�ַ
	PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryW");
	if (pfnThreadRtn == NULL)
		printf("��ȡLoadLibrary��ַʧ��\n");
	////

	HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, pfnThreadRtn, pBuf, 0, NULL);
	if (hRemoteThread == NULL)
		printf("����Զ���߳�ʧ��\n");
	printf("%d", GetLastError());

	WaitForSingleObject(hRemoteThread, INFINITE);


	system("PAUSE");
	return 0;
}

