// dz.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "dz.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
int h = 5;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DZ, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DZ));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DZ));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DZ);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        static int      cxClient, cyClient;
        static POINT    ptCenter;
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);

        ptCenter.x = cxClient / 2;
        ptCenter.y = cyClient / 2;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case 0:
            {
                /*std::wstring text{};
                text.resize(5);
                GetWindowText(hWnd, &text[0], 5);
                std::string st(text.begin(), text.end());
                h= atoi(st.c_str());*/
                h--;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            case 1000:
                h++;
                InvalidateRect(hWnd,NULL, TRUE);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_CREATE:
    {
        /*HWND textbox=CreateWindow(TEXT("10"), TEXT("Деления"), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 
            200, 0, 200, 30, hWnd, NULL, NULL, NULL);*/
        HWND hButton = CreateWindow(L"BUTTON", L"Увеличить масштаб", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0, 0, 200, 30, hWnd, reinterpret_cast<HMENU>(0), nullptr, nullptr);
        HWND hButton1 = CreateWindow(L"BUTTON", L"Увеличить масштаб", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            200,0, 200, 30, hWnd, reinterpret_cast<HMENU>(1000), nullptr, nullptr);
    }
    return 0;
    case WM_PAINT:
        {
            InvalidateRect(hWnd, NULL, TRUE);
            double n;
            int y1,i1,a,k;
            if (h == 0) h=1;
            i1 =568/h;
            k = 0;
            double y, s,s1;
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            MoveToEx(hdc, ptCenter.x, 0, NULL);
            LineTo(hdc, ptCenter.x, cyClient);
            MoveToEx(hdc, 0, ptCenter.y, NULL);
            LineTo(hdc, cxClient, ptCenter.y);
            MoveToEx(hdc, ptCenter.x, 0, NULL);
            LineTo(hdc, ptCenter.x - 5, 20);
            MoveToEx(hdc, ptCenter.x, 0, NULL);
            LineTo(hdc, ptCenter.x + 5, 20);
            MoveToEx(hdc, cxClient, ptCenter.y,NULL);
            LineTo(hdc, cxClient-20, ptCenter.y-5);
            MoveToEx(hdc, cxClient, ptCenter.y, NULL);
            LineTo(hdc, cxClient - 20, ptCenter.y + 5);
            TextOut(hdc, cxClient - 15, ptCenter.y + 10, L"X", 1);
            TextOut(hdc, ptCenter.x - 25, 5, L"Y", 1);
            for (int i = 1; i <= 14; i=i+1) {
                MoveToEx(hdc, ptCenter.x+5, ptCenter.y - i * 15, NULL);
                LineTo(hdc, ptCenter.x-5, ptCenter.y - i * 15);
                
                k++;
                if (k % 2 == 0) {
                    a = i;
                    std::basic_stringstream<TCHAR> ss;
                    ss << a;
                    std::basic_string<TCHAR> s;
                    ss >> s;
                    TextOut(hdc, ptCenter.x - 30, ptCenter.y - i * 15+5, s.c_str(), s.size());
                }
            }
            for (int i = 1; i <= 14; i = i + 1) {
                MoveToEx(hdc, ptCenter.x + 5, ptCenter.y + i * 15, NULL);
                LineTo(hdc, ptCenter.x - 5, ptCenter.y + i * 15);
                k++;
                if (k % 2 == 0) {
                    a = i;
                    std::basic_stringstream<TCHAR> ss;
                    ss << a;
                    std::basic_string<TCHAR> s;
                    ss >> s;
                    TextOut(hdc, ptCenter.x - 30, ptCenter.y + i * 15 - 5, s.c_str(), s.size());
                }
            }
            k = 0;
            for (int i = 1; i <= h; i ++) {
                if (i * i1 + ptCenter.x >= cxClient - 20) break;
                MoveToEx(hdc, i*i1+ptCenter.x, ptCenter.y + 5, NULL);
                LineTo(hdc, i * i1 + ptCenter.x, ptCenter.y - 5);
                k = k + 1;
                if(i1>=60) {
                    a = i;
                    std::basic_stringstream<TCHAR> ss;
                    ss << a;
                    std::basic_string<TCHAR> s;
                    ss >> s;
                    TextOut(hdc, i * i1 + ptCenter.x - 5, ptCenter.y + 10, s.c_str(), s.size());
                    k = 0;
                }
                else if(k==(60/i1)){
                    a = i;
                    std::basic_stringstream<TCHAR> ss;
                    ss << a;
                    std::basic_string<TCHAR> s;
                    ss >> s;
                    TextOut(hdc, i * i1 + ptCenter.x - 5, ptCenter.y + 10, s.c_str(), s.size());
                    k = 0;
                }
            }
            for (int i = 1; i <= h; i++) {
                if (i * i1 + ptCenter.x >= cxClient - 20) break;
                MoveToEx(hdc, ptCenter.x - i * i1, ptCenter.y + 5, NULL);
                LineTo(hdc, ptCenter.x - i * i1, ptCenter.y - 5);
                k = k + 1;
                if (i1 >= 50){
                    a = -i;
                    std::basic_stringstream<TCHAR> ss;
                    ss << a;
                    std::basic_string<TCHAR> s;
                    ss >> s;
                    TextOut(hdc, ptCenter.x - i * i1 - 5, ptCenter.y + 10, s.c_str(), s.size());
                    k = 0;
                }
                else if (k == (60 / i1)) {
                    a = -i;
                    std::basic_stringstream<TCHAR> ss;
                    ss << a;
                    std::basic_string<TCHAR> s;
                    ss >> s;
                    TextOut(hdc, ptCenter.x - i * i1 - 5, ptCenter.y + 10, s.c_str(), s.size());
                    k = 0;
                }
            }
            for (int i = 20; i <= cxClient-20; i=i++) {
                i=i-ptCenter.x;
                i--;
                n = i;
                n = n / i1;
                s = fabs(sin(n * 0.3));
                s1 = pow(s, 0.4);
                y = ptCenter.y - (s1)*cos(2 * n) * 13 * 15;
                y1 = static_cast<int>(round(y));
                i = i + ptCenter.x;
                MoveToEx(hdc, i, y1, NULL);
                i = i - ptCenter.x;
                i++;
                n = i;
                n = n / i1;
                s = fabs(sin(n * 0.3));
                s1 = pow(s, 0.4);
                y = ptCenter.y - (s1)*cos(2 * n) * 13 * 15;
                y1 = static_cast<int>(round(y));
                i = i + ptCenter.x;
                LineTo(hdc, i, y1);
                }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
