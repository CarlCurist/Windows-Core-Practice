// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<cstdio>
#include<windows.h>

#define OK_READ 1
#define OK_WRITE 2

HANDLE RFile, WFile;
TCHAR szBuf[255];
LARGE_INTEGER FileSize;

VOID ChooseFile()
{
	printf("��������Ҫ���Ƶ��ļ��ľ���·��(��֧�ֳ���4G���ļ�)\n");
	wscanf_s(L"%ls", szBuf, _countof(szBuf));
	RFile = CreateFile(szBuf, GENERIC_READ, 0, NULL, OPEN_EXISTING,/* FILE_FLAG_NO_BUFFERING | */FILE_FLAG_OVERLAPPED, NULL);
	if (RFile == INVALID_HANDLE_VALUE)
	{
		printf("���ļ�ʧ��\n");
		return;
	}
	GetFileSizeEx(RFile, &FileSize);
	printf("�ļ���С��%d�ֽڣ�%dKB��%dMB\n", FileSize.LowPart, FileSize.LowPart / 1024, FileSize.LowPart / 1048576);
	return;
}

VOID ChooseAddress()
{
	printf("������Ҫ���Ƶĵ�ַ\n");
	wscanf_s(L"%ls", szBuf, _countof(szBuf));
	WFile = CreateFile(szBuf, GENERIC_WRITE, 0, NULL, CREATE_NEW,/* FILE_FLAG_NO_BUFFERING | */FILE_FLAG_OVERLAPPED, NULL);
	if (RFile == INVALID_HANDLE_VALUE)
	{
		printf("����ʧ��\n");
	}
	return;
}

VOID CopyFileBegin()
{
	DWORD AlreadyMove = 0, HaveMove = 0, temp = 0;
	OVERLAPPED OWrite = { 0 }, ORead = { 0 };
	ULONG_PTR CompletionKey;
	OVERLAPPED* pO;
	BOOL bOk;
	
	HANDLE IOPort = CreateIoCompletionPort(RFile, NULL, OK_READ, 0);
	CreateIoCompletionPort(WFile, IOPort, OK_WRITE, 0);

	PostQueuedCompletionStatus(IOPort, 255, OK_WRITE, &ORead);
	while (1)
	{
		bOk = GetQueuedCompletionStatus(IOPort, &HaveMove, &CompletionKey, &pO, INFINITE);
		GetOverlappedResult(IOPort, &ORead, &HaveMove, TRUE);
		temp = HaveMove;
		if (bOk)
		{
			switch (CompletionKey)
			{
			case OK_READ:
				WriteFile(WFile, szBuf, temp, &HaveMove, &OWrite);
				//WriteFile(WFile, szBuf, temp, &HaveMove, &ORead);
				printf("%d\n", GetLastError());
				break;
			case OK_WRITE:
				if (AlreadyMove + 255 < FileSize.LowPart)
				{
					ReadFile(RFile, szBuf, 255, &HaveMove, &ORead);
					printf("%d\n", GetLastError());
					AlreadyMove += 255;
					break;
				}
				else
				{
					ReadFile(RFile, szBuf, FileSize.LowPart - AlreadyMove, &HaveMove, &ORead);
					AlreadyMove += FileSize.LowPart - AlreadyMove;
					break;
				}
			}
		}
		if (AlreadyMove >= FileSize.LowPart)
		{
			CloseHandle(IOPort);
			break;
		}
	}
	printf("�������\n");

	/*
	//SetFilePointerEx(WFile, FileSize, NULL, FILE_BEGIN);
	//SetEndOfFile(WFile);

	DWORD AlreadyMove = 0, HaveMove = 0;
	while (1)
	{
		if (AlreadyMove + 255 < FileSize.LowPart)
		{
			ReadFile(RFile, szBuf, 255, &HaveMove, NULL);
			WriteFile(WFile, szBuf, 255, &HaveMove, NULL);
			AlreadyMove += 255;
		}
		else
		{
			ReadFile(RFile, szBuf, FileSize.LowPart - AlreadyMove, &HaveMove, NULL);
			WriteFile(WFile, szBuf, FileSize.LowPart - AlreadyMove, &HaveMove, NULL);
			break;
		}
		if (AlreadyMove >= FileSize.LowPart)break;
	}
	printf("�������\n");
	*/
}
int _tmain(int argc, _TCHAR* argv[])
{
	ChooseFile();
	ChooseAddress();
	CopyFileBegin();
	
	CloseHandle(RFile);
	CloseHandle(WFile);
	return 0;
}

