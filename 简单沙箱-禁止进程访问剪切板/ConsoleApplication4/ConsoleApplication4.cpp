// ConsoleApplication4.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include<Windows.h>
#include<stdio.h>
#include <stdlib.h>


int _tmain(int argc, _TCHAR* argv[])
{
	//setlocale(LC_CTYPE, "chs");

	/*
	SHELLEXECUTEINFO sei{ sizeof(SHELLEXECUTEINFO) };
	sei.lpVerb = TEXT("runas");
	sei.lpFile = TEXT("NOTEPAD");
	sei.nShow = SW_SHOWDEFAULT;
	//ShellExecuteEX(&sei);
	ShellExecuteEx(&sei);
	*/


	//STARTUPINFO si = { sizeof(si) };
	//PROCESS_INFORMATION pi;

	TCHAR processname[100];
	wscanf_s(L"%ls", processname, _countof(processname));

	HANDLE hjob = CreateJobObject(NULL, TEXT("SimpleSandBox"));
	
	JOBOBJECT_BASIC_UI_RESTRICTIONS jobui;
	jobui.UIRestrictionsClass = JOB_OBJECT_UILIMIT_NONE;
	//jobui.UIRestrictionsClass = JOB_OBJECT_UILIMIT_READCLIPBOARD;//��ֹ���̶�ȡ�����������
	jobui.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_WRITECLIPBOARD;

	SetInformationJobObject(hjob, JobObjectBasicUIRestrictions, &jobui,sizeof(jobui));

	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	CreateProcess(NULL, processname, NULL, NULL, FALSE, CREATE_SUSPENDED|CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);//CREATE_SUSPENDED��־�ý��̲�����ִ��
	AssignProcessToJobObject(hjob, pi.hProcess);
	ResumeThread(pi.hThread);//�ý���ִ�д���
	CloseHandle(pi.hThread);

	CloseHandle(hjob);

	//MessageBox(NULL, sz, TEXT("df"), NULL);
	//CreateProcess(NULL, processname, NULL, NULL, NULL, 0, NULL, NULL, &si, &pi);
	return 0;
}