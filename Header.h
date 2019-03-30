#include <iostream>
#include <stdlib.h>
#include <stack>
#include <cctype>
#include <string>
#include <map>
#include <string.h>
#include <cstdio>
#include <sstream>
#include <windows.h>
#include <tchar.h>
#include <Shlwapi.h>
#include "Calculater.cpp"
#include "Binary_Calculator.cpp"

#define ID_EDIT_BIN 98
#define ID_EDIT 99
#define ID_BUTTON 100
#define ID_BUTTON_1 101 
#define ID_BUTTON_2 102
#define ID_BUTTON_3 103
#define ID_BUTTON_4 104
#define ID_BUTTON_5 105
#define ID_BUTTON_6 106
#define ID_BUTTON_7 107
#define ID_BUTTON_8 108
#define ID_BUTTON_9 109
#define ID_BUTTON_ADD 110
#define ID_BUTTON_SUB 111
#define ID_BUTTON_MUL 112
#define ID_BUTTON_DIV 113
#define ID_BUTTON_RES 114
#define ID_BUTTON_C 115
#define ID_BUTTON_LOGIC_MUL 116
#define ID_BUTTON_LOGIC_SUM 117
#define ID_BUTTON_LOGIC_XOR 118


static TCHAR szWindowClass[] = _T("win32_app");
static TCHAR szTitle[] = _T("Calculator_Lab2_K.Khrol");
TCHAR buf[300];
TCHAR buf_bin[300];
TCHAR temp[300];
HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
