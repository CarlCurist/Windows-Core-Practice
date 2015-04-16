// Win32Dll.cpp : 定义 DLL 应用程序的入口点。
//

#define _WIN32_WINNT  0x0500				// 设置系统版本, 确保可以使用底层键盘钩子

#include "Win32Dll.h"

HHOOK hkb=NULL;
HHOOK hlkb=NULL;
HINSTANCE hins;


LRESULT  CALLBACK KeyboardProc(int nCode,WPARAM wParam,LPARAM lParam)
{	

	if(lParam&0x80000000)
	{
		char Buff[32]; 
		sprintf(Buff,"%c  %x\n",wParam,lParam);	
		MessageBox(NULL,"Key Push",Buff,MB_OK);
	}
	LRESULT RetVal = CallNextHookEx( hkb, nCode, wParam, lParam );	
	return  RetVal;
}  
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{   
	char Buff[32]; 
	sprintf(Buff,"%x  %x\n",wParam,lParam);	
	MessageBox(NULL,"Low Level Key Push",Buff,MB_OK);
	// 调用系统中的下一个钩子
	return CallNextHookEx(hkb, nCode, wParam, lParam);
}

BOOL __declspec(dllexport)__stdcall InstallHook()
{
	hkb=SetWindowsHookEx(WH_KEYBOARD,(HOOKPROC)KeyboardProc,hins,0);
	return hkb==NULL? FALSE:TRUE;
}
BOOL __declspec(dllexport)__stdcall InstallLowHook()
{
	hlkb = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hins, NULL);
	return hlkb==NULL? FALSE:TRUE;
}
BOOL __declspec(dllexport)__stdcall  UnHook()
{   	
	BOOL unhooked = UnhookWindowsHookEx(hkb);
	return unhooked;
} 
BOOL __declspec(dllexport)__stdcall  UnLowHook()
{   	
	BOOL unhooked = UnhookWindowsHookEx(hlkb);
	return unhooked;
} 
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	hins = (HINSTANCE)hModule;
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			{
					 hkb = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, hins, 0);
				break;
			}
		case DLL_THREAD_ATTACH:
			
			break;

		case DLL_PROCESS_DETACH:

		case DLL_THREAD_DETACH:
			
			break;
	}
    return TRUE;

}

