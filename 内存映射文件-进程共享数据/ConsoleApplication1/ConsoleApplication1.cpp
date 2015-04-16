// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<windows.h>
#include<cstdio>


int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hShare = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, TEXT("SharedData"));
	if (hShare == NULL)
	{
		printf("不存在共享数据\n");
		hShare = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 4 * 1024, TEXT("SharedData"));
		if (hShare == NULL)printf("创建内存映射失败\n");
		PSTR pBuf = (PSTR)MapViewOfFile(hShare, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
		if (pBuf == NULL)printf("映射内存失败");
		
		printf("输入想要传输的数据：\n");
		scanf_s("%s", pBuf, 4 * 1024);

	}
	else
	{
		printf("收到传输数据\n");
		PSTR pBuf = (PSTR)MapViewOfFile(hShare, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
		printf("%s", pBuf);
	}
	
	system("PAUSE");
	return 0;
}

