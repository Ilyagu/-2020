#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

WCHAR WinName[] = _TEXT("MainFrame");
WCHAR WinName2[] = _TEXT("MainFrame2");


/*BOOL MySystemShutdown()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;


	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return(FALSE);

	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
		&tkp.Privileges[0].Luid);

	tkp.PrivilegeCount = 1; 
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;


	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
		(PTOKEN_PRIVILEGES)NULL, 0);

	if (GetLastError() != ERROR_SUCCESS)
		return FALSE;

	if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,
		SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
		SHTDN_REASON_MINOR_UPGRADE |
		SHTDN_REASON_FLAG_PLANNED))
		return FALSE;

	return TRUE;
}*/

int WINAPI wWinMain(HINSTANCE This, 
	HINSTANCE Prev, 
	LPTSTR cmd,
	int mode)
{
	HWND hWnd; 
	MSG msg; 
	WNDCLASS wc;
	
	wc.hInstance = This;
	wc.lpszClassName = WinName2;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);



	if (!RegisterClass(&wc)) return 0;

	hWnd = CreateWindow(WinName2,
		_TEXT("Окно №2"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		600,
		500,
		HWND_DESKTOP,
		NULL,
		This, 
		NULL);
	HMENU hmenu1;
	hmenu1 = CreateMenu();
	AppendMenu(hmenu1, MF_STRING, 1000, L"Закрыть окно №1");

	SetMenu(hWnd, hmenu1);
	ShowWindow(hWnd, mode);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND descriptor;
	switch (message)
	{
	case WM_USER + 1:
	{
		MessageBox(hWnd, _TEXT("Сообщение №1"), _TEXT("Сообщение"), MB_OK);
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_USER + 2:
	{
		//MessageBox(hWnd, _TEXT("Сообщение №2"), _TEXT("Выключение"), MB_OK);
		//SendMessage(HWND(wParam), WM_USER + 3, NULL, NULL);
		//MySystemShutdown();
	}
	case WM_DESTROY:
		PostQuitMessage(0);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case 1000:
			descriptor = FindWindow(WinName, NULL);
			if (descriptor != NULL)
				SendMessage(descriptor, WM_CLOSE, WPARAM(hWnd), NULL);
			break;
		}
	}
	}
	return 0;
}