// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
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
		printf("ö�ٽ���ʧ��");
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
		printf("����ֹ���̾��ʧ��\n");
		DWORD Error=GetLastError();
		printf("�������Ϊ��%u\n", Error);
		return FALSE;
	}
	if (!TerminateProcess(hProcess, 0))
	{
		printf("��ֹ����ʧ��\n");
		DWORD Error = GetLastError();
		printf("�������Ϊ��%u\n", Error);
		return FALSE;
	}
	printf("���̽����ɹ�\n");
	return TRUE;
}
int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR szBuf[50];
	while (1)
	{
		printf("���롰enum��ö�ٵ�ǰ���̣����롰exit���˳������������PID�����ý���\n");
		wscanf_s(L"%ls", szBuf, _countof(szBuf));
		if (!wcscmp(szBuf, TEXT("exit")))
			break; 
		if (!wcscmp(szBuf, TEXT("enum")))
		{
			EnumProcess();
			continue;
		}
		//���϶����ǣ�������Ϊһ�����̵�PID
		DWORD ProcessPID = (DWORD)_wtol((wchar_t *)szBuf);//��TCHARת����DWORD
		Terminate(ProcessPID);
	}
	return 0;
}

