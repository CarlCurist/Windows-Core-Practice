// ������-������ͬ�ĳ�����ͬʱ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<cstdio>
#include<windows.h>
#include<iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE Mutex = OpenMutex(MUTEX_ALL_ACCESS, TRUE, TEXT("Flame"));
	if (GetLastError() == ERROR_FILE_NOT_FOUND)//������δ����
	{
		char InData;
		Mutex = CreateMutex(NULL, TRUE, TEXT("Flame"));
		if (Mutex != NULL)printf("�������Ѵ���\n");
		else printf("����ʧ��\n");
		while (1)
		{
			///////////////////////////////////////////////////////////////////////////
			//scanf_s("%c", &InData);
			cin >> InData;    //�˴�Ϊʲô����һ��scanf_s����������������
			//////////////////////////////////////////////////////////////////////
			fflush(stdin); //ˢ�����뻺����,����δƥ��� input �ַ������� buffer
			printf("%c\n", InData);
			if (InData == 'e')
			{
				ReleaseMutex(Mutex);
				printf("���������ͷţ��ȴ���һ�����̽���\n");
				break;
			}
			if (InData == 's')
			{
				CloseHandle(Mutex);
				printf("��������ɾ��\n");
				break;
			}
		}
	}
	else
	{
		printf("�������Ѵ���,�ȴ���һ�������˳�\n");
		WaitForSingleObject(Mutex, INFINITE);
		printf("��һ�������˳�\n");
	}
	system("pause");
	return 0;
}

