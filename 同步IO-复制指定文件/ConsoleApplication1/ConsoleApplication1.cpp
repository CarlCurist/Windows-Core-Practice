// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<cstdio>
#include<windows.h>

HANDLE RFile, WFile;
TCHAR szBuf[255];
LARGE_INTEGER FileSize;

VOID ChooseFile()
{
	printf("输入你想要复制的文件的绝对路径(不支持超过4G的文件)\n");
	wscanf_s(L"%ls", szBuf, _countof(szBuf));
	RFile = CreateFile(szBuf, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (RFile == INVALID_HANDLE_VALUE)
	{
		printf("打开文件失败\n");
		return;
	}
	GetFileSizeEx(RFile, &FileSize);
	printf("文件大小：%d字节，%dKB，%dMB\n", FileSize.LowPart, FileSize.LowPart / 1024, FileSize.LowPart / 1048576);
	return;
}

VOID ChooseAddress()
{
	printf("输入想要复制的地址\n");
	wscanf_s(L"%ls", szBuf, _countof(szBuf));
	WFile = CreateFile(szBuf, GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);
	if (RFile == INVALID_HANDLE_VALUE)
	{
		printf("设置失败\n");
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
	printf("复制完成\n");
}
int _tmain(int argc, _TCHAR* argv[])
{
	ChooseFile();
	ChooseAddress();
	CopyFileBegin();
	return 0;
}

