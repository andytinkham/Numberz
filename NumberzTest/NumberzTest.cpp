// NumberzTest.cpp : Main app for brute force win32 automation.
//

#include "stdafx.h"
#include "NumberzTest.h"

void Log(HANDLE hFile, wchar_t* buffer);

int counts[10];
int additionErrors = 0;

// I got the IDs of the window items I care about from spy++
int numIDs[] = 
{
	0x3ea,
	0x3eb,
	0x3ec,
	0x3ed,
	0x3ee
};
int resultID = 0x3ef;
int buttonID = 0x3e8;


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,  LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);

	wchar_t buffer[256];
	DWORD unused = 0;
	DWORD dwLen = 0;

	HWND hwnd = FindWindow(NULL, L"Numberz");
	HANDLE hFile = CreateFile(L"NumberzTestOutput.log", 
								GENERIC_WRITE,
								0, 
								NULL, 
								CREATE_ALWAYS,
								FILE_ATTRIBUTE_NORMAL, 
								NULL);
	int one = 0, two = 0, three = 0, four = 0, five = 0, six = 0;

	int LoopCount = _wtoi(lpCmdLine);
	if (LoopCount == 0)
	{
		LoopCount = 100;
	}
	
	//ok - now we have all the window handles we need, the rest is (mostly) easy
	ShowWindow(hwnd, nCmdShow);
	for (int loop = 0; loop < LoopCount; loop++)
	{
		SendDlgItemMessage(hwnd, buttonID, WM_LBUTTONDOWN, 0, 0);
		SendDlgItemMessage(hwnd, buttonID, WM_LBUTTONUP, 0, 0);
		int total = 0;
		for (int i = 0; i < 5; i++)
		{
			int val = GetDlgItemInt(hwnd, numIDs[i], NULL, FALSE);
			switch (val)
			{
				case 1:
					one++;
					break;
				case 2:
					two++;
					break;
				case 3:
					three++;
					break;
				case 4:
					four++;
					break;
				case 5:
					five++;
					break; 
				case 6:
					six++;
					break;
				default:
					break;
			}
			total +=val;

			// counts may be enough
			counts[val]++;
		}
		int proposedVal = GetDlgItemInt(hwnd, resultID, NULL, FALSE);
		if (proposedVal != total)
		{
			StringCchPrintf(buffer, 256, 
				L"[Loop iteration %d] Error: Total of dice is %d, Actual is %d\r\n",
				loop, proposedVal, total);
				Log(hFile, buffer);
			additionErrors++;
		}
	}
	StringCchPrintf(buffer, 256, L"Total of %d addition errors in %d iterations\r\n", 
		additionErrors, LoopCount);
		Log(hFile, buffer);


	// write values and counts here
	StringCchPrintf(buffer, 256, L"\r\n================================================\r\n");
	Log(hFile, buffer);

	StringCchPrintf(buffer, 256, L"Totals:\t1\t2\t3\t4\t5\t6\r\n");
	Log(hFile, buffer);

	StringCchPrintf(buffer, 256, L"\t%d\t%d\t%d\t%d\t%d\t%d\r\n", one, two, three, four, five, six);
	Log(hFile, buffer);
	
	CloseHandle(hFile);
}

void Log(HANDLE hFile, wchar_t* buffer)
{
	DWORD unused = 0;
	DWORD dwLength = lstrlen(buffer);
	WriteFile(hFile, buffer, dwLength * 2, &unused, NULL);
}
