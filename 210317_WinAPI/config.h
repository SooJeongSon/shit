// config.h

#pragma once

#include <Windows.h>
#include <string>
#include <ctime>
#include <math.h>
#include <bitset>
#include <vector>
#include "KeyManager.h"

using namespace std;

#define WINSIZE_X	800
#define WINSIZE_Y	1000

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;

//#define TIMER_ONESECOND 1