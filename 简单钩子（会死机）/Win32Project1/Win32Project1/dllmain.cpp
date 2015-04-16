// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include<windows.h>
HHOOK g_hHook = NULL;
HINSTANCE g_hInstDll = NULL;
void OK();
LRESULT WINAPI GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
							   g_hInstDll = hModule;
							   OK();
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


void OK()
{
	SetWindowsHookEx(WH_CBT, GetMsgProc, g_hInstDll, 0);
}
LRESULT WINAPI GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam) {

	MessageBox(NULL, TEXT("ok"), TEXT("ok"), MB_OK);

	return(CallNextHookEx(g_hHook, nCode, wParam, lParam));
}
