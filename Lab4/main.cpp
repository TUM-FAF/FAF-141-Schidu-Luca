#include <windows.h>
#include "Button.h"
#include "EditText.h"
#include <time.h>
#include <thread>
#include <c++/iostream>
#include <windowsx.h>
#include <wingdi.h>
#include <vector>
#include "resource.h"
#include "Object.h"

#define WIDTH 800
#define HEIGTH 600

#define TIMER_ID 1

static PAINTSTRUCT ps;
const int BALL_MOVE_DELTA = 2;
static HDC hdc,hdcMem;
static RECT rect;
static HBRUSH hBrush;
static HBITMAP hbmMem;
static HANDLE hOld;

int x, y;

vector<Object> vec;

void initObjects() {

    srand(time(NULL));
    Object *object;
    for(int i = 0; i < 10; i++) {
        object = new Object(rand()%rect.right, rand()%rect.bottom, 50, 50);
        object->setCircle(false);
        object->setDirection(rand()%4);
        vec.push_back(*object);
    }

}

static void Paint(HWND hWnd, LPPAINTSTRUCT lpPS)
{
    RECT rc;
    HDC hdcMem;
    HBITMAP hbmMem, hbmOld;
    HBRUSH hbrBkGnd;
    HFONT hfntOld;

    GetClientRect(hWnd, &rc);

    hdcMem = CreateCompatibleDC(lpPS->hdc);
    hbmMem = CreateCompatibleBitmap(lpPS->hdc, rc.right-rc.left, rc.bottom-rc.top);
    hbmOld = (HBITMAP) SelectObject(hdcMem, hbmMem);
    hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));

    FillRect(hdcMem, &rc, hbrBkGnd);

    for(int i = 0; i < 10; i++){
        x = vec[i].getX();
        y = vec[i].getY();

        vec[i].wallCollision(rect.right, rect.bottom);
        switch(vec[i].getDirection()) {
            case 0:
                x += 2;
                y += 2;
                break;
            case 1:
                x -= 2;
                y += 2;
                break;
            case 2:
                x += 2;
                y -= 2;
                break;
            case 3:
                x -= 2;
                y -= 2;
                break;
        }

        vec[i].setPosition(x, y);
        Rectangle(hdcMem, vec[i].getX(), vec[i].getY(), vec[i].getX() + vec[i].getWidth(), vec[i].getY() + vec[i].getHeight());
    }
    DeleteObject(hbrBkGnd);
    SetBkMode(hdcMem, TRANSPARENT);
    SetTextColor(hdcMem, GetSysColor(COLOR_WINDOWTEXT));


    if (hfntOld) {
        SelectObject(hdcMem, hfntOld);
    }

    BitBlt(lpPS->hdc, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, hdcMem, 0, 0, SRCCOPY);

    SelectObject(hdcMem, hbmOld);
    DeleteObject(hbmMem);
    DeleteDC(hdcMem);

}


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd) {
    WNDCLASSEX wClass;
    ZeroMemory(&wClass, sizeof(WNDCLASSEX));
    wClass.cbClsExtra = NULL;
    wClass.cbSize = sizeof(WNDCLASSEX);
    wClass.cbWndExtra = NULL;
    wClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wClass.hCursor = LoadCursor(NULL, IDC_ICON);
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

            BeginPaint(hWnd, &ps);
            Paint(hWnd, &ps);
            EndPaint(hWnd, &ps);

        }
            break;

        case WM_CREATE: {

            x = 0;
            y = 0;

            hdc = GetDC(hWnd);
            GetClientRect(hWnd,&rect);
            hdcMem = CreateCompatibleDC(hdc);
            hbmMem = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
            hOld = SelectObject(hdcMem,hbmMem);

            int ret = SetTimer(hWnd, TIMER_ID, 5, NULL);
            if(ret == 0)
                MessageBox(hWnd, "Could not SetTimer()!", "Error", MB_OK | MB_ICONEXCLAMATION);
            initObjects();
            break;
        }


        case WM_TIMER: {
            InvalidateRect(hWnd, &rect, FALSE);
        }
            break;


        case WM_COMMAND: {
            switch(wParam) {

            }
            break;
        }

        case WM_DESTROY: {
            KillTimer(hWnd, TIMER_ID);

            PostQuitMessage(0);
            return 0;
        }

    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}



