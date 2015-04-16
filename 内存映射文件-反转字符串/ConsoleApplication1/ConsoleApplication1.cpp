// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<windows.h>
#include<cstdio>
#include<string.h>


int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR szBuf[200];
	wscanf_s(L"%ls", szBuf, _countof(szBuf));
	
	HANDLE hFileRes = CreateFile(szBuf, GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFileRes == INVALID_HANDLE_VALUE)
	{
		printf("打开文件出错\n");
	}

	DWORD dwFileSize = GetFileSize(hFileRes, NULL);
	HANDLE hFileMap = CreateFileMapping(hFileRes, NULL, PAGE_READWRITE, 0, dwFileSize + sizeof(char), NULL);
	if (hFileMap == NULL)
	{
		printf("创建文件映射对象失败\n");
	}

	PVOID pvFile = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);
	if (pvFile == NULL)
	{
		printf("映射文件失败\n");
	}

	PSTR psFile = (PSTR)pvFile;
	psFile[dwFileSize / sizeof(char)] = 0;
	_strrev(psFile);

	SetFilePointer(hFileRes, dwFileSize, NULL, FILE_BEGIN);
	SetEndOfFile(hFileRes);
	UnmapViewOfFile(pvFile);
	CloseHandle(hFileRes);
	CloseHandle(hFileMap);
	return 0;
}

