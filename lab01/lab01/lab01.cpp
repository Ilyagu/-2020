#include <Windows.h>
#include <tchar.h>

extern int l = 380;
extern int r = 380;
extern int lt = 10;
extern int rt = 10;
extern bool right = false;
extern bool left = false;
LRESULT APIENTRY WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 25); 	// Заполнение окна белым цветом 


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("Каркас Windows-приложения"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

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
	static int      cxClient, cyClient;
	static POINT    ptCenter;
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH brush;
	RECT prect;
	prect.top = 0;
	prect.bottom = cyClient;
	const char a = 'g';
	switch (message)
	{
	case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			MoveToEx(hdc, cxClient / 2, cyClient / 2 - 200, NULL); LineTo(hdc, cxClient / 2, 10);
			MoveToEx(hdc, cxClient / 2 + 1, cyClient / 2 - 200, NULL); LineTo(hdc, cxClient / 2 + 1, 10);
			brush = CreateSolidBrush(RGB(0, 128, 0));
			SelectObject(hdc, brush);
			Ellipse(hdc, cxClient / 2, 40 - 20, (cxClient / 2 + 70) + 50, 40 + 20);
			DeleteObject(brush);
			brush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, brush);
			Ellipse(hdc, cxClient / 2 - 200, cyClient / 2 - 200, cxClient / 2 + 200, cyClient / 2 + 200);
			DeleteObject(brush);

			EndPaint(hWnd, &ps);

			if (left == true) {
				prect.left = 0;
				prect.right = cxClient / 2 - 200 + lt;
				InvalidateRect(hWnd, NULL, FALSE);

				hdc = BeginPaint(hWnd, &ps);

				brush = CreateSolidBrush(RGB(0, 155, 250));
				SelectObject(hdc, brush);
				Ellipse(hdc, cxClient / 2 - l - 200, cyClient / 2 - 160, cxClient / 2 - l + 200, cyClient / 2 + 160);
				DeleteObject(brush);

				EndPaint(hWnd, &ps);

				InvalidateRect(hWnd, &prect, TRUE);

				hdc = BeginPaint(hWnd, &ps);
				EndPaint(hWnd, &ps);
			}
			if (right == true) {
				prect.left = cxClient / 2 + 200 - rt;
				prect.right = cxClient;
				InvalidateRect(hWnd, NULL, FALSE);

				hdc = BeginPaint(hWnd, &ps);

				brush = CreateSolidBrush(RGB(0, 155, 250));
				SelectObject(hdc, brush);
				Ellipse(hdc, cxClient / 2 + r - 200, cyClient / 2 - 160, cxClient / 2 + r + 200, cyClient / 2 + 160);
				DeleteObject(brush);

				EndPaint(hWnd, &ps);

				InvalidateRect(hWnd, &prect, TRUE);

				hdc = BeginPaint(hWnd, &ps);
				EndPaint(hWnd, &ps);
			}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		ptCenter.x = cxClient / 2;
		ptCenter.y = cyClient / 2;
		break;
	case WM_RBUTTONDOWN:
		right = true;
		if (r <= 230) {
			MessageBox(0, L"С правой стороны все съедено", L"ВСЕ!", MB_OK);
			break;
		}
		else {
			r = r - 30;
			rt = rt + 10;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		return 0;
	case WM_LBUTTONDOWN:
		left = true;
		if (l <= 230) {
			MessageBox(0, L"С левой стороны все съедено", L"ВСЕ!", MB_OK);
			break;
		}
		else {
			l = l - 30;
			lt = lt + 10;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
