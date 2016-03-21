#include <windows.h>
#include "Button.h"
#include "EditText.h"
#include <time.h>
#include <thread>
#include <windowsx.h>
#include <advpub.h>
#include <c++/iostream>
#include <tchar.h>



#define IDM_FILE_NEW 40001
#define IDM_FILE_OPEN 40002
#define IDM_FILE_SAVE 40003
#define IDM_FILE_SAVE_AS 40004
#define IDM_APP_EXIT 40005
#define IDM_EDIT_UNDO 40006
#define IDM_EDIT_CUT 40007
#define IDM_EDIT_COPY 40008
#define IDM_EDIT_PASTE 40009
#define IDM_EDIT_CLEAR 40010
#define IDM_BKGND_WHITE 40011
#define IDM_BKGND_LTGRAY 40012
#define IDM_BKGND_GRAY 40013
#define IDM_BKGND_DKGRAY 40014
#define IDM_BKGND_BLACK 40015
#define IDM_TIMER_START 40016
#define IDM_TIMER_STOP 40017
#define IDM_APP_HELP 40018
#define IDM_APP_ABOUT 40019


#define WIDTH 800
#define HEIGTH 600

void drawLines(HDC Memhdc) {

    srand(time(NULL));
    HPEN pen;
    for(int i = 0; i < 5; i++) {
        pen = CreatePen(PS_SOLID, i+1, RGB(rand()%250, rand()%250, rand()%250));
        SelectObject(Memhdc, pen);
        MoveToEx(Memhdc, 10, 100 + i*15, NULL);
        LineTo(Memhdc, 500, 100 + i*15);
    }
}

void initDraw(HWND hWnd){

    RECT Client_Rect;
    GetClientRect(hWnd,&Client_Rect);
    int win_width = Client_Rect.right - Client_Rect.left;
    int win_height = Client_Rect.bottom + Client_Rect.left;
    PAINTSTRUCT ps;
    HDC Memhdc;
    HDC hdc;
    HBITMAP Membitmap;
    hdc = BeginPaint(hWnd, &ps);

    Memhdc = CreateCompatibleDC(hdc);
    Membitmap = CreateCompatibleBitmap(hdc, win_width, win_height);
    SelectObject(Memhdc, Membitmap);

    drawLines(Memhdc);

    BitBlt(hdc, 0, 0, win_width, win_height, Memhdc, 0, 0, SRCCOPY);
    DeleteObject(Membitmap);
    DeleteDC    (Memhdc);

    DeleteDC    (hdc);
    EndPaint(hWnd, &ps);

}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd) {
    WNDCLASSEX wClass;
    ZeroMemory(&wClass, sizeof(WNDCLASSEX));
    wClass.cbClsExtra = NULL;
    wClass.cbSize = sizeof(WNDCLASSEX);
    wClass.cbWndExtra = NULL;
    wClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wClass.hIcon = LoadIcon(NULL, IDC_ICON);
    wClass.hIconSm = LoadIcon(NULL, IDC_ICON);
    wClass.hInstance = hInst;
    wClass.lpfnWndProc = (WNDPROC) WinProc;
    wClass.lpszClassName = "Window Class";
    wClass.lpszMenuName = NULL;
    wClass.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&wClass)) {
        int nResult = GetLastError();
        MessageBox(NULL,
                   "Window class creation failed\r\n",
                   "Window Class Failed",
                   MB_ICONERROR);
    }

    HWND hWnd = CreateWindowEx(NULL,
                               "Window Class",
                               "Windows application",
                               WS_OVERLAPPEDWINDOW,
                               200,
                               200,
                               WIDTH,
                               HEIGTH,
                               NULL,
                               NULL,
                               hInst,
                               NULL);

    if (!hWnd) {
        int nResult = GetLastError();

        MessageBox(NULL,
                   "Window creation failed\r\n",
                   "Window Creation Failed",
                   MB_ICONERROR);
    }

    ShowWindow(hWnd, nShowCmd);

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {

            initDraw(hWnd);

        }
            break;

        case WM_CREATE: {
            break;
        }



        case WM_VSCROLL: {

        }

        case WM_HOTKEY : {
            switch(wParam) {

            }
        }


        case WM_MOUSEMOVE: {
        }

        case WM_COMMAND: {


            break;
        }



        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }

        case WM_SIZE: {

        }

            break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}



