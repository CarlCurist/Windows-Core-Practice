// ConsoleApplication4.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<windows.h>
#include<iostream>
#include<cstdio>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "chs");//��Ҫ�ڿ���̨�����������Ҫ�����

	DWORD dwError;
	cin >> dwError;
	HLOCAL hlo = NULL;

	DWORD systemLocale = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);

	BOOL fOk=FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,NULL, dwError, systemLocale, (PTSTR)&hlo, 0, NULL);
	
	if (!fOk)
	{
		HMODULE hDll = LoadLibraryEx(TEXT("netmsg.dll"), NULL, DONT_RESOLVE_DLL_REFERENCES);
		if (hDll != NULL)
		{
			fOk = FormatMessage(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, hDll, dwError, systemLocale, (PTSTR)&hlo, 0, NULL);
			FreeLibrary(hDll);
		}
	}
	if (fOk && (hlo != NULL))
	{
		//cout << *(PCTSTR)LocalLock(hlo);
		/*
		for (; (PCTSTR)LocalLock(hlo) != NULL;)
		{
			wprintf("%c", (PCTSTR)LocalLock(hlo));
		}
		*/
		//MessageBox(NULL, (PCTSTR)LocalLock(hlo), TEXT("ss"),MB_OK);
		_tprintf(TEXT("%s"), (PCTSTR)LocalLock(hlo));
		LocalFree(hlo);
	}
	else
	{
		cout << "error";
	}

	return 0;
}

