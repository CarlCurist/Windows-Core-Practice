// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	HMODULE HDll = LoadLibrary(TEXT("Win32Dll.dll"));

	system("PAUSE");
	return 0;
}

