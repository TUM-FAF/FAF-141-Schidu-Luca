#include <windows.h>
#include <time.h>
#include <thread>
#include <c++/iostream>
#include <windowsx.h>
#include <wingdi.h>
#include <vector>
#include "Car.h"
#include "Controller.h"

using namespace std;

#define WIDTH 800
#define HEIGTH 600

#define TIMER_ID 1

static PAINTSTRUCT ps;
static HDC hdc;
static RECT rect;
RECT rc;
HDC hdcMem;
HBITMAP hbmMem, hbmOld;
HBRUSH hbrBkGnd;
HFONT hfntOld;


int x, y;

HINSTANCE inst;

Car *car;
int changeTrafficLight = 0;
Controller *controller;

void drawRoad(HDC hdcMem) {

    MoveToEx(hdcMem, 0, 200, NULL);
    LineTo(hdcMem, rc.right, 200);

    MoveToEx(hdcMem, 0, 300, NULL);
    LineTo(hdcMem, rc.right, 300);

    MoveToEx(hdcMem, 0, 400, NULL);
    LineTo(hdcMem, rc.right, 400);


    MoveToEx(hdcMem, 300, 0, NULL);
    LineTo(hdcMem, 300, rc.bottom);

    MoveToEx(hdcMem, 400, 0, NULL);
    LineTo(hdcMem, 400, rc.bottom);

    MoveToEx(hdcMem, 500, 0, NULL);
    LineTo(hdcMem, 500, rc.bottom);
}

static void Paint(HWND hWnd, LPPAINTSTRUCT lpPS) {

    GetClientRect(hWnd, &rc);

    hdcMem = CreateCompatibleDC(lpPS->hdc);
    hbmMem = CreateCompatibleBitmap(lpPS->hdc, rc.right-rc.left, rc.bottom-rc.top);
    hbmOld = (HBITMAP) SelectObject(hdcMem, hbmMem);
    hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));

    FillRect(hdcMem, &rc, hbrBkGnd);

    drawRoad(hdcMem);
    controller->drawCars(hdcMem);
    controller->drawTrafficLights(hdcMem);
    controller->drawPedestrians(hdcMem);

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
    inst = hInst;
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
            controller->generateCar();
            controller->moveCars();
            controller->generatePedestrian();
            controller->movePedestrians();


            hdc = BeginPaint(hWnd, &ps);
            Paint(hWnd, &ps);
            EndPaint(hWnd, &ps);

        }
            break;

        case WM_CREATE: {

            hdc = GetDC(hWnd);
            GetClientRect(hWnd,&rect);
            controller = new Controller();
            int ret = SetTimer(hWnd, TIMER_ID, 5, NULL);
            if(ret == 0)
                    MessageBox(hWnd, "Could not SetTimer()!", "Error", MB_OK | MB_ICONEXCLAMATION);
            break;
        }


        case WM_TIMER: {
            changeTrafficLight++;
//            if(changeTrafficLight == 1000) {
//                changeTrafficLight = 0;
//                controller->changeTraficLight();
//            }

            InvalidateRect(hWnd, &rect, FALSE);
        }
            break;


        case WM_COMMAND: {
            switch(wParam) {

            }
            break;
        }

        case WM_LBUTTONDOWN: {
            controller->changeTraficLight();
            break;
        }


        case WM_MOUSEWHEEL : {
            int zDelta = (short) HIWORD(wParam);

            if(zDelta > 0) {
                controller->increaseRandom();
            }else {
                controller->decreaseRandom();
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



