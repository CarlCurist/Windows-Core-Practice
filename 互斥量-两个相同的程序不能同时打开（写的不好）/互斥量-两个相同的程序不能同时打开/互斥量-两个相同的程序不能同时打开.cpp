// 互斥量-两个相同的程序不能同时打开.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<cstdio>
#include<windows.h>
#include<iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE Mutex = OpenMutex(MUTEX_ALL_ACCESS, TRUE, TEXT("Flame"));
	if (GetLastError() == ERROR_FILE_NOT_FOUND)//互斥量未创建
	{
		char InData;
		Mutex = CreateMutex(NULL, TRUE, TEXT("Flame"));
		if (Mutex != NULL)printf("互斥量已创建\n");
		else printf("创建失败\n");
		while (1)
		{
			///////////////////////////////////////////////////////////////////////////
			//scanf_s("%c", &InData);
			cin >> InData;    //此处为什么用上一句scanf_s不能正常读入数据
			//////////////////////////////////////////////////////////////////////
			fflush(stdin); //刷新输入缓冲区,避免未匹配的 input 字符被留在 buffer
			printf("%c\n", InData);
			if (InData == 'e')
			{
				ReleaseMutex(Mutex);
				printf("互斥量已释放，等待另一个进程接收\n");
				break;
			}
			if (InData == 's')
			{
				CloseHandle(Mutex);
				printf("互斥量已删除\n");
				break;
			}
		}
	}
	else
	{
		printf("互斥量已存在,等待另一个进程退出\n");
		WaitForSingleObject(Mutex, INFINITE);
		printf("另一进程已退出\n");
	}
	system("pause");
	return 0;
}

