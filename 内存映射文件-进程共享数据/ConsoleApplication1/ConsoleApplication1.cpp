// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<windows.h>
#include<cstdio>


int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hShare = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, TEXT("SharedData"));
	if (hShare == NULL)
	{
		printf("�����ڹ�������\n");
		hShare = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 4 * 1024, TEXT("SharedData"));
		if (hShare == NULL)printf("�����ڴ�ӳ��ʧ��\n");
		PSTR pBuf = (PSTR)MapViewOfFile(hShare, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
		if (pBuf == NULL)printf("ӳ���ڴ�ʧ��");
		
		printf("������Ҫ��������ݣ�\n");
		scanf_s("%s", pBuf, 4 * 1024);

	}
	else
	{
		printf("�յ���������\n");
		PSTR pBuf = (PSTR)MapViewOfFile(hShare, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
		printf("%s", pBuf);
	}
	
	system("PAUSE");
	return 0;
}

