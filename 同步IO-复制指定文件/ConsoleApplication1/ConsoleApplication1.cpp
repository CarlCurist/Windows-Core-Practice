// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<cstdio>
#include<windows.h>

HANDLE RFile, WFile;
TCHAR szBuf[255];
LARGE_INTEGER FileSize;

VOID ChooseFile()
{
	printf("��������Ҫ���Ƶ��ļ��ľ���·��(��֧�ֳ���4G���ļ�)\n");
	wscanf_s(L"%ls", szBuf, _countof(szBuf));
	RFile = CreateFile(szBuf, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
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
	WFile = CreateFile(szBuf, GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);
	if (RFile == INVALID_HANDLE_VALUE)
	{
		printf("����ʧ��\n");
	}
	return;
}

VOID CopyFileBegin()
{
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
}
int _tmain(int argc, _TCHAR* argv[])
{
	ChooseFile();
	ChooseAddress();
	CopyFileBegin();
	return 0;
}

