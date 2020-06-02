#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

WCHAR WinName[] = _TEXT("MainFrame");
WCHAR WinName2[] = _TEXT("MainFrame2");


int WINAPI wWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// Заполнение окна белым цветом 



	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_TEXT("Окно № 1"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		600, 				// width 
		500, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 
	HMENU hmenu1;
	hmenu1 = CreateMenu();
	AppendMenu(hmenu1, MF_STRING,1000, L"Закрыть окно №2");

	SetMenu(hWnd, hmenu1);
	ShowWindow(hWnd, mode);
	UpdateWindow(hWnd);


	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND descriptor;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		descriptor = FindWindow(WinName2, NULL);
		if (descriptor != NULL)
		{
			MessageBox(hWnd, _TEXT("Окно № 2 открыто"), _TEXT("Сообщение"), MB_OK);
			SendMessage(descriptor, WM_USER + 1, WPARAM(hWnd), NULL);
		}
		else
		{
			MessageBox(hWnd, _TEXT("Окно № 2 закрыто"), _TEXT("Окно № 2 не найдено"), MB_OK);
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_RBUTTONDOWN:
	{
		descriptor = FindWindow(WinName2, NULL);
		if (descriptor != NULL)
		{
			MessageBox(hWnd, _TEXT("Окно № 2 открыто!"), _TEXT("Сообщение выключения"), MB_OK);
			SendMessage(descriptor, WM_USER + 2, WPARAM(hWnd), NULL);
		}
		else
		{
			MessageBox(hWnd, __TEXT("Окно № 2 закрыто"), _TEXT("Окно № 2 не найдено"), MB_OK);
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_DESTROY:
		PostQuitMessage(0);
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
			case 1000:
				descriptor = FindWindow(WinName2, NULL);
				if (descriptor != NULL)
					SendMessage(descriptor, WM_CLOSE, WPARAM(hWnd), NULL);
				break;
			}
		}
	}
	return 0;
}