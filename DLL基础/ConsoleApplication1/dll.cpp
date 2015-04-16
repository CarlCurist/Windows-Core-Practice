#include<windows.h>

#define DLLAPI extern "C" __declspec(dllexport)

#include"stdafx.h"

int add(int a, int b)
{
	return(a + b);
}