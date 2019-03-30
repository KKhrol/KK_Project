#include "Header.h"
//#include "Binary_Calculator.cpp"
int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int mode)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 11);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szWindowClass;
	wc.hIconSm = LoadIcon(wc.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		return 1;
	}

	hInst = hInstance;
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_SYSMENU,			//WS_OVERLAPPEDWINDOW  Стиль окна 
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		340,
		270,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)
	{
		return 1;
	}

	ShowWindow(hWnd, mode);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hButton[19], hEdit, hListBox, hEdit_bin;
	PAINTSTRUCT ps;
	HDC hdc;
	int i = 0, count = 0, a = 0, b = 0;
	switch (message)
	{
	case WM_CREATE:
		hEdit_bin = CreateWindow(_T("edit"), _T("0"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 10, 51, 310, 20, hWnd, (HMENU)ID_EDIT_BIN, hInst, 0);
		hEdit = CreateWindow(_T("edit"), _T("0"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 10, 5, 310, 45, hWnd, (HMENU)ID_EDIT, hInst, 0);
		hButton[0] = CreateWindow(_T("Button"), _T("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 180, 130, 30, hWnd, (HMENU)ID_BUTTON, hInst, 0);
		hButton[1] = CreateWindow(_T("Button"), _T("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 75, 40, 30, hWnd, (HMENU)ID_BUTTON_1, hInst, 0);
		hButton[2] = CreateWindow(_T("Button"), _T("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 75, 40, 30, hWnd, (HMENU)ID_BUTTON_2, hInst, 0);
		hButton[3] = CreateWindow(_T("Button"), _T("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 75, 40, 30, hWnd, (HMENU)ID_BUTTON_3, hInst, 0);
		hButton[4] = CreateWindow(_T("Button"), _T("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 110, 40, 30, hWnd, (HMENU)ID_BUTTON_4, hInst, 0);
		hButton[5] = CreateWindow(_T("Button"), _T("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 110, 40, 30, hWnd, (HMENU)ID_BUTTON_5, hInst, 0);
		hButton[6] = CreateWindow(_T("Button"), _T("6"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 110, 40, 30, hWnd, (HMENU)ID_BUTTON_6, hInst, 0);
		hButton[7] = CreateWindow(_T("Button"), _T("7"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 145, 40, 30, hWnd, (HMENU)ID_BUTTON_7, hInst, 0);
		hButton[8] = CreateWindow(_T("Button"), _T("8"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 145, 40, 30, hWnd, (HMENU)ID_BUTTON_8, hInst, 0);
		hButton[9] = CreateWindow(_T("Button"), _T("9"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 145, 40, 30, hWnd, (HMENU)ID_BUTTON_9, hInst, 0);
		hButton[10] = CreateWindow(_T("Button"), _T("+"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 110, 40, 30, hWnd, (HMENU)ID_BUTTON_ADD, hInst, 0);
		hButton[11] = CreateWindow(_T("Button"), _T("-"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 145, 40, 30, hWnd, (HMENU)ID_BUTTON_SUB, hInst, 0);
		hButton[12] = CreateWindow(_T("Button"), _T("*"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 200, 110, 40, 30, hWnd, (HMENU)ID_BUTTON_MUL, hInst, 0);
		hButton[13] = CreateWindow(_T("Button"), _T("/"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 200, 145, 40, 30, hWnd, (HMENU)ID_BUTTON_DIV, hInst, 0);
		hButton[14] = CreateWindow(_T("Button"), _T("="), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 180, 90, 30, hWnd, (HMENU)ID_BUTTON_RES, hInst, 0);
		hButton[15] = CreateWindow(_T("Button"), _T("C"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 75, 90, 30, hWnd, (HMENU)ID_BUTTON_C, hInst, 0);
		hButton[16] = CreateWindow(_T("Button"), _T("|"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 250, 75, 60, 30, hWnd, (HMENU)ID_BUTTON_LOGIC_SUM, hInst, 0);
		hButton[17] = CreateWindow(_T("Button"), _T("&&"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 250, 110, 60, 30, hWnd, (HMENU)ID_BUTTON_LOGIC_MUL, hInst, 0);
		hButton[18] = CreateWindow(_T("Button"), _T("^"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 250, 145, 60, 30, hWnd, (HMENU)ID_BUTTON_LOGIC_XOR, hInst, 0);
		
		break;


	case WM_COMMAND:
		if ((LOWORD(wParam) == ID_BUTTON) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));
			if ((*buf == TEXT('0')) && (0 == buf[1]))
			{
				*buf = 0;
			}
			if ((*buf_bin == TEXT('0')) && (0 == buf_bin[1]))
			{
				*buf_bin = 0;
			}
			if ((*temp == TEXT('0')) && (0 == temp[1]))
			{
				*temp = 0;
			}
			StrCat(buf, TEXT("0"));
			StrCat(temp, TEXT("0"));
			StrCat(buf_bin, Resout_Bin(temp));

			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
			delete[] Resout_Bin(temp);
		}

		if ((LOWORD(wParam) == ID_BUTTON_1) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));
			GetWindowText(hEdit, buf, sizeof(buf));
			if ((*buf == TEXT('0')) && (0 == buf[1]))
			{
				*buf = 0;
			}
			if ((*buf_bin == TEXT('0')) && (0 == buf_bin[1]))
			{
				*buf_bin = 0;
			}
			if ((*temp == TEXT('0')) && (0 == temp[1]))
			{
				*temp = 0;
			}
			StrCat(buf, TEXT("1"));
			StrCat(temp, TEXT("1"));
			StrCat(buf_bin, Resout_Bin(temp));

			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
			delete[] Resout_Bin(temp);
		}

		if ((LOWORD(wParam) == ID_BUTTON_2) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));
			if ((*buf == '0') && (0 == buf[1]))
			{
				*buf = 0;
			}

			if ((*buf_bin == '0') && (0 == buf_bin[1]))
			{
				*buf_bin = 0;
			}
			if ((*temp == TEXT('0')) && (0 == temp[1]))
			{
				*temp = 0;
			}
			StrCat(buf, TEXT("2"));
			StrCat(temp, TEXT("2"));
			StrCat(buf_bin, Resout_Bin(temp));

			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
			delete[] Resout_Bin(temp);
		}

		if ((LOWORD(wParam) == ID_BUTTON_3) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));
			if ((*buf == '0') && (0 == buf[1]))
			{
				*buf = 0;
			}
			if ((*buf_bin == '0') && (0 == buf_bin[1]))
			{
				*buf_bin = 0;
			}
			if ((*temp == TEXT('0')) && (0 == temp[1]))
			{
				*temp = 0;
			}
			StrCat(buf, TEXT("3"));
			StrCat(temp, TEXT("3"));
			StrCat(buf_bin, Resout_Bin(temp));

			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
			delete[] Resout_Bin(temp);
		}

		if ((LOWORD(wParam) == ID_BUTTON_4) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));
			if ((*buf == TEXT('0')) && (0 == buf[1]))
			{
				*buf = 0;
			}
			if ((*buf_bin == '0') && (0 == buf_bin[1]))
			{
				*buf_bin = 0;
			}
			if ((*temp == TEXT('0')) && (0 == temp[1]))
			{
				*temp = 0;
			}
			StrCat(buf, TEXT("4"));
			StrCat(temp, TEXT("4"));
			StrCat(buf_bin, Resout_Bin(temp));

			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
			delete[] Resout_Bin(temp);
		}

		if ((LOWORD(wParam) == ID_BUTTON_5) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));
			if ((*buf == '0') && (0 == buf[1]))
			{
				*buf = 0;
			}
			if ((*buf_bin == '0') && (0 == buf_bin[1]))
			{
				*buf_bin = 0;
			}
			if ((*temp == TEXT('0')) && (0 == temp[1]))
			{
				*temp = 0;
			}
			StrCat(buf, TEXT("5"));
			StrCat(temp, TEXT("5"));
			StrCat(buf_bin, Resout_Bin(temp));

			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
			delete[] Resout_Bin(temp);
		}

		if ((LOWORD(wParam) == ID_BUTTON_6) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));
			if ((*buf == '0') && (0 == buf[1]))
			{
				*buf = 0;
			}
			if ((*buf_bin == '0') && (0 == buf_bin[1]))
			{
				*buf_bin = 0;
			}
			if ((*temp == TEXT('0')) && (0 == temp[1]))
			{
				*temp = 0;
			}
			StrCat(buf, TEXT("6"));
			StrCat(temp, TEXT("6"));
			StrCat(buf_bin, Resout_Bin(temp));

			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
			delete[] Resout_Bin(temp);
		}

		if ((LOWORD(wParam) == ID_BUTTON_7) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit, buf_bin, sizeof(buf_bin));
			if ((*buf == '0') && (0 == buf[1]))
			{
				*buf = 0;
			}
			if ((*buf_bin == '0') && (0 == buf_bin[1]))
			{
				*buf_bin = 0;
			}
			if ((*temp == TEXT('0')) && (0 == temp[1]))
			{
				*temp = 0;
			}
			StrCat(buf, TEXT("7"));
			StrCat(temp, TEXT("7"));
			StrCat(buf_bin, Resout_Bin(temp));

			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
			delete[] Resout_Bin(temp);
		}

		if ((LOWORD(wParam) == ID_BUTTON_8) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));
			if ((*buf == '0') && (0 == buf[1]))
			{
				*buf = 0;
			}
			if ((*buf_bin == '0') && (0 == buf_bin[1]))
			{
				*buf_bin = 0;
			}
			if ((*temp == TEXT('0')) && (0 == temp[1]))
			{
				*temp = 0;
			}
			StrCat(buf, TEXT("8"));
			StrCat(temp, TEXT("8"));
			StrCat(buf_bin, Resout_Bin(temp));

			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
			delete[] Resout_Bin(temp);
		}

		if ((LOWORD(wParam) == ID_BUTTON_9) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));
			if ((*buf == '0') && (0 == buf[1]))
			{
				*buf = 0;
			}
			if ((*buf_bin == '0') && (0 == buf_bin[1]))
			{
				*buf_bin = 0;
			}
			if ((*temp == TEXT('0')) && (0 == temp[1]))
			{
				*temp = 0;
			}
			StrCat(buf, TEXT("9"));
			StrCat(temp, TEXT("9"));
			StrCat(buf_bin, Resout_Bin(temp));

			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
			delete[] Resout_Bin(temp);
		}

		if ((LOWORD(wParam) == ID_BUTTON_ADD) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));
			
			temp[0] = 0;
			StrCat(buf, TEXT("+"));
			StrCat(buf_bin, TEXT("+"));
			
			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
		
		}

		if ((LOWORD(wParam) == ID_BUTTON_SUB) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));

			temp[0] = 0;
			StrCat(buf, TEXT("-"));
			StrCat(buf_bin, TEXT("-"));
			
			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
		}

		if ((LOWORD(wParam) == ID_BUTTON_MUL) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));

			temp[0] = 0;
			StrCat(buf, TEXT("*"));
			StrCat(buf_bin, TEXT("*"));
			
			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
		
		}

		if ((LOWORD(wParam) == ID_BUTTON_DIV) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));

			temp[0] = 0;
			StrCat(buf, TEXT("/"));
			StrCat(buf_bin, TEXT("/"));
			
			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
			
		}

		if ((LOWORD(wParam) == ID_BUTTON_RES) && (HIWORD(wParam) == BN_CLICKED))
		{
			int result = 0;
			buf_bin[0] = 0;
			temp[0] = 0;
			
			StrCat(temp, Calculate(buf));
			GetWindowText(hEdit, buf, sizeof(buf));
			SetWindowText(hEdit, temp);
			result = _tstoi(*&temp);
			
			_stprintf_s(temp, _T("%d"), result);

			GetWindowText(hEdit_bin, buf_bin, sizeof(buf));
			SetWindowText(hEdit_bin, Resout_Bin(temp));

			delete[] Resout_Bin(temp);
			buf_bin[0] = 0;
		}

		if ((LOWORD(wParam) == ID_BUTTON_C) && (HIWORD(wParam) == BN_CLICKED))
		{
			SetWindowText(hEdit, TEXT("0"));
			SetWindowText(hEdit_bin, TEXT("0"));
			buf[0] = 0;
			buf_bin[0] = 0;
			temp[0] = 0;
		}

		if ((LOWORD(wParam) == ID_BUTTON_LOGIC_MUL) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));

			temp[0] = 0;
			StrCat(buf, TEXT("&"));
			StrCat(buf_bin, TEXT("&"));
			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);

		}

		if ((LOWORD(wParam) == ID_BUTTON_LOGIC_SUM) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));

			temp[0] = 0;
			StrCat(buf, TEXT("|"));
			StrCat(buf_bin, TEXT("|"));

			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
		}
		if ((LOWORD(wParam) == ID_BUTTON_LOGIC_XOR) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			GetWindowText(hEdit_bin, buf_bin, sizeof(buf_bin));

			temp[0] = 0;
			StrCat(buf, TEXT("^"));
			StrCat(buf_bin, TEXT("^"));

			SetWindowText(hEdit, buf);
			SetWindowText(hEdit_bin, buf_bin);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}