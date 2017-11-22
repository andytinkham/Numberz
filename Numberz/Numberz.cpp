// Numberz.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Numberz.h"

void NumberzLogic(HWND hwnd);
void FixFont(HWND hwnd);
INT_PTR  CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int iCmdShow)
{
	HWND hwnd = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_MAINAPP), 0, DialogProc, 0);
	ShowWindow(hwnd, iCmdShow);

	MSG msg;

	while (GetMessage(&msg, hwnd, 0, 0)) 
	{ 
		if (!IsDialogMessage(hwnd, &msg))
		{ 
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		} 
	} 

	DestroyWindow(hwnd);

	return 0;
}
 
INT_PTR CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		FixFont(hwnd);
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		PostQuitMessage(0);
		return FALSE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTONROLL:
			{
				NumberzLogic(hwnd);
			}
		}
	default:
		return FALSE;
	}
	return FALSE;
}

void NumberzLogic(HWND hwnd)
{
	//get 5 random numbers
	int vals[5];
	WCHAR tmp[5][2];
	WCHAR ttl[3];
	int total = 0;

	srand(GetTickCount());
	for (int i = 0; i < 5; i++)
	{
		vals[i] = (rand() % 10);
		// bug #1 - let's skew the results toward the number 3
		if ((rand() % 30) == 0)
		{
			vals[i] = 3;
		}
		total += vals[i];

		_itow_s(vals[i], tmp[i], 10);
	}

	SetDlgItemText(hwnd, IDC_STATIC1, tmp[0]);
	SetDlgItemText(hwnd, IDC_STATIC2, tmp[1]);
	SetDlgItemText(hwnd, IDC_STATIC3, tmp[2]);
	SetDlgItemText(hwnd, IDC_STATIC4, tmp[3]);
	SetDlgItemText(hwnd, IDC_STATIC5, tmp[4]);
	
	// bug #2 .02% of the time, the total will be one less
	//        and .002% of the time the total will be one more. 
	double random = (double)(rand() / (double)RAND_MAX);
	if (random < 0.002)
	{
		total -= 1;
	}
	else if (random > 0.998)
	{
		total += 1;
	}
	_itow_s(total, ttl, 10);
	SetDlgItemText(hwnd, IDC_RESULTS, ttl);
}




void FixFont(HWND hwnd)
{
	HFONT hFont, hNewFont; 
	LOGFONT lf; 
	HDC hDC; 
	HWND hStatic1 = GetDlgItem(hwnd, IDC_STATIC1);
	hFont = (HFONT)SendMessage(hStatic1, WM_GETFONT, 0, 0); 
	if(hDC = GetDC(hStatic1)) 
	{ 
		if (hFont == NULL) 
		{ 
			hFont = (HFONT) GetStockObject(SYSTEM_FONT); 
			GetObject(hFont, sizeof(LOGFONT),&lf); 
			lf.lfQuality = DEFAULT_QUALITY; 
			lf.lfWidth = 0; 
		} 
		else 
		{
			GetObject(hFont, sizeof(LOGFONT),&lf); 
		}
		lf.lfHeight = -MulDiv(20, GetDeviceCaps(hDC, LOGPIXELSY), 72); 
		hNewFont = CreateFontIndirect(&lf); 
		SendMessage(hStatic1, WM_SETFONT, (WPARAM)hNewFont, MAKELPARAM(TRUE, 0)); 
		
		SendMessage(GetDlgItem(hwnd, IDC_STATIC2), WM_SETFONT, (WPARAM)hNewFont, MAKELPARAM(TRUE, 0)); 	
		SendMessage(GetDlgItem(hwnd, IDC_STATIC3), WM_SETFONT, (WPARAM)hNewFont, MAKELPARAM(TRUE, 0)); 	
		SendMessage(GetDlgItem(hwnd, IDC_STATIC4), WM_SETFONT, (WPARAM)hNewFont, MAKELPARAM(TRUE, 0)); 	
		SendMessage(GetDlgItem(hwnd, IDC_STATIC5), WM_SETFONT, (WPARAM)hNewFont, MAKELPARAM(TRUE, 0)); 	
		SendMessage(GetDlgItem(hwnd, IDC_STATIC6), WM_SETFONT, (WPARAM)hNewFont, MAKELPARAM(TRUE, 0)); 	
		SendMessage(GetDlgItem(hwnd, IDC_STATIC7), WM_SETFONT, (WPARAM)hNewFont, MAKELPARAM(TRUE, 0)); 	
		SendMessage(GetDlgItem(hwnd, IDC_BUTTONROLL), WM_SETFONT, (WPARAM)hNewFont, MAKELPARAM(TRUE, 0)); 	
		ReleaseDC(hStatic1, hDC);
	}
	SetDlgItemText(hwnd, IDC_STATIC1, 0);
	SetDlgItemText(hwnd, IDC_STATIC2, 0);
	SetDlgItemText(hwnd, IDC_STATIC3, 0);
	SetDlgItemText(hwnd, IDC_STATIC4, 0);
	SetDlgItemText(hwnd, IDC_STATIC5, 0);
}