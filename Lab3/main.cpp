#include <windows.h>
#include "Button.h"
#include "EditText.h"
#include <time.h>
#include <thread>
#include <c++/iostream>
#include <windowsx.h>
#include "resource.h"



#define DRAW_LINE 1
#define DRAW_CIRCLE 2
#define DRAW_RACTANGLE 3
#define DRAW_BEZIER 69
#define ERASER_MEDIUM 5
#define ERASER_SMALL 12
#define ERASER_LARGE 13
#define CONTROL_SPACE 101
#define ALT_LEFT 102
#define WIDTH 800
#define HEIGTH 600
int counterForBezier = 0;
POINT bezierCoordinate[4];
POINT bezierPoint;
POINT cursorPos;
int eraserSize;
bool firstStart = true;
HBITMAP fin = NULL;
HINSTANCE hInstance;
int draw_figure = 0;
int xMouse, yMouse;
RECT rectangle;
HDC Memhdc;
HBITMAP Membitmap;
HDC hdc;
HPEN bezierPen;
RECT rcClient;
POINT ptClientUL;
POINT ptClientLR;
POINTS ptsBegin;
POINTS ptsEnd;
POINTS ptsPrevEnd;
BOOL fPrevLine = FALSE;


void drawLines(HDC Memhdc) {

    srand(time(NULL));
    HPEN pen;
    for(int i = 0; i < 5; i++) {
        pen = CreatePen(PS_SOLID, i+1, RGB(rand()%250, rand()%250, rand()%250));
        SelectObject(Memhdc, pen);
        MoveToEx(Memhdc, 10, 50 + i*15, NULL);
        LineTo(Memhdc, 300, 50 + i*15);
    }
}

void drawBezier(HDC hdc) {

    POINT Pt[4] = { {  190,  182 }, {  258, 416 }, { 524, 362 }, { 420,  228 } };
    PolyBezierTo(hdc,Pt,4);
    PolyBezier (hdc, Pt, 4) ;
    MoveToEx (hdc, Pt[0].x, Pt[0].y, NULL) ;
    LineTo (hdc, Pt[1].x, Pt[1].y) ;
    MoveToEx (hdc, Pt[2].x, Pt[2].y, NULL) ;
    LineTo (hdc, Pt[3].x, Pt[3].y) ;
}


void drawObjects(HDC Memhdc) {

    HBRUSH brush = CreateSolidBrush(RGB(200,12,30));
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(200,12,30));
    SelectObject(Memhdc, pen);
    Rectangle(Memhdc, 400, 10, 550, 90);
    SelectObject(Memhdc,brush);
    Ellipse(Memhdc, 560, 10, 640 , 90);
}

void initializaCanvas(HWND hWnd) {
    RECT Client_Rect;
    GetClientRect(hWnd,&Client_Rect);
    int win_width = Client_Rect.right - Client_Rect.left;
    int win_height = Client_Rect.bottom + Client_Rect.left;
    PAINTSTRUCT ps;
    hdc = BeginPaint(hWnd, &ps);
    Memhdc = CreateCompatibleDC(hdc);
    Membitmap = CreateCompatibleBitmap(hdc, win_width, win_height);
    EndPaint(hWnd, &ps);
}

void drawGradient(HDC hdc, int x, int y, int X, int Y, int type){

    HBRUSH hBrush;
    RECT rectgleToDraw;
    RECT rectGradient = {x, y, X, Y};
    rectgleToDraw.top = rectGradient.top;
    rectgleToDraw.bottom = rectGradient.bottom;

    for(int i = 0; i < (rectGradient.right - rectGradient.left); i++) {
        int color;
        color = i * 255/(rectGradient.right - rectGradient.left);
        rectgleToDraw.left  = rectGradient.left  + i;
        rectgleToDraw.right = rectGradient.left + i + 1;
        if(type == 0) {
            hBrush = CreateSolidBrush(RGB(0, 0, color));
        }else{
            hBrush = CreateSolidBrush(RGB(color, 0, 0));

        }
        FillRect(hdc, &rectgleToDraw, hBrush);
        DeleteObject(hBrush);
    }

}

void initDraw(HWND hWnd){

    RECT Client_Rect;
    GetClientRect(hWnd,&Client_Rect);
    int win_width = Client_Rect.right - Client_Rect.left;
    int win_height = Client_Rect.bottom + Client_Rect.left;
    PAINTSTRUCT ps;
    hdc = BeginPaint(hWnd, &ps);

    Memhdc = CreateCompatibleDC(hdc);
    Membitmap = CreateCompatibleBitmap(hdc, win_width, win_height);
    SelectObject(Memhdc, Membitmap);
    HBRUSH hbrush = CreateSolidBrush(RGB(255,255,255));
    SelectObject(Memhdc, hbrush);
    Rectangle(Memhdc, 0, 0, win_width, win_height);
    drawLines(Memhdc);
    drawBezier(Memhdc);
    drawObjects(Memhdc);
    drawGradient(Memhdc, 10, 180, 100, 250, 0 );
    drawGradient(Memhdc, 10, 270, 100, 340, 1 );


    BitBlt(hdc, 0, 0, win_width, win_height, Memhdc, 0, 0, SRCCOPY);

    EndPaint(hWnd, &ps);
}



void AddMenus(HWND hwnd) {

    HMENU hMenubar;
    HMENU hMenu;

    hMenubar = CreateMenu();
    hMenu = CreateMenu();

    AppendMenuW(hMenu, MF_STRING, DRAW_LINE, L"&Line");
    AppendMenuW(hMenu, MF_STRING, DRAW_CIRCLE, L"&Circle");
    AppendMenuW(hMenu, MF_STRING, DRAW_RACTANGLE, L"&Rectangle");
    AppendMenuW(hMenu, MF_STRING, DRAW_BEZIER, L"&Bezier");

    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu, L"&Draw");

    hMenu = CreateMenu();
    AppendMenuW(hMenu, MF_STRING, ERASER_SMALL, L"&Small");
    AppendMenuW(hMenu, MF_STRING, ERASER_MEDIUM, L"&Medium");
    AppendMenuW(hMenu, MF_STRING, ERASER_LARGE, L"&Large");


    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu, L"&Eraser");
    SetMenu(hwnd, hMenubar);

    RegisterHotKey(hwnd, CONTROL_SPACE, MOD_CONTROL, VK_SPACE);
    RegisterHotKey(hwnd, ALT_LEFT, MOD_ALT, VK_LEFT);

}




void mouse_drawLine(WPARAM wParam, LPARAM lParam, HWND hWnd) {

    if (wParam & MK_LBUTTON) {
        PAINTSTRUCT ps;
        hdc = GetDC(hWnd);

        SetROP2(hdc, R2_NOTXORPEN);

        if (fPrevLine) {
            MoveToEx(hdc, ptsBegin.x, ptsBegin.y,
                     (LPPOINT) NULL);
            LineTo(hdc, ptsPrevEnd.x, ptsPrevEnd.y);
        }


        ptsEnd = MAKEPOINTS(lParam);
        MoveToEx(hdc, ptsBegin.x, ptsBegin.y, (LPPOINT) NULL);
        LineTo(hdc, ptsEnd.x, ptsEnd.y);


        fPrevLine = TRUE;
        ptsPrevEnd = ptsEnd;
        ReleaseDC(hWnd, hdc);
    }
}


void mouse_drawCircle(WPARAM wParam, LPARAM lParam, HWND hWnd) {

    if (wParam & MK_LBUTTON) {
        PAINTSTRUCT ps;
        hdc = GetDC(hWnd);

        SetROP2(hdc, R2_NOTXORPEN);

        if (fPrevLine) {
            MoveToEx(hdc, ptsBegin.x, ptsBegin.y,
                     (LPPOINT) NULL);
            Ellipse(hdc, ptsBegin.x, ptsBegin.y, ptsEnd.x, ptsEnd.y);
        }


        ptsEnd = MAKEPOINTS(lParam);
        MoveToEx(hdc, ptsBegin.x, ptsBegin.y, (LPPOINT) NULL);
        Ellipse(hdc, ptsBegin.x, ptsBegin.y, ptsEnd.x, ptsEnd.y);


        fPrevLine = TRUE;
        ptsPrevEnd = ptsEnd;
        ReleaseDC(hWnd, hdc);
    }
}


void mouse_drawRectangle(WPARAM wParam, LPARAM lParam, HWND hWnd) {

    if (wParam & MK_LBUTTON) {
        PAINTSTRUCT ps;
        hdc = GetDC(hWnd);

        SetROP2(hdc, R2_NOTXORPEN);

        if (fPrevLine) {
            MoveToEx(hdc, ptsBegin.x, ptsBegin.y,
                     (LPPOINT) NULL);
            Rectangle(hdc, ptsBegin.x, ptsBegin.y, ptsEnd.x, ptsEnd.y);
        }


        ptsEnd = MAKEPOINTS(lParam);
        MoveToEx(hdc, ptsBegin.x, ptsBegin.y, (LPPOINT) NULL);
        Rectangle(hdc, ptsBegin.x, ptsBegin.y, ptsEnd.x, ptsEnd.y);


        fPrevLine = TRUE;
        ptsPrevEnd = ptsEnd;
        ReleaseDC(hWnd, hdc);
    }
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

    hInstance = hInst;
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
            AddMenus(hWnd);
            initializaCanvas(hWnd);
            fin = (HBITMAP)LoadImage(hInstance, "themes.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
            bezierPen = CreatePen(PS_SOLID, 3, RGB(250, 0, 0));

            break;
        }

        case WM_HOTKEY : {
            switch(wParam) {

                case CONTROL_SPACE: {
                    draw_figure = 2;
                    break;
                }

                case ALT_LEFT: {
                    draw_figure = 3;
                    break;
                }
            }
        }

        case WM_LBUTTONDOWN : {
            SetCapture(hWnd);
            GetClientRect(hWnd, &rcClient);
            ptClientUL.x = rcClient.left;
            ptClientUL.y = rcClient.top;

            ptClientLR.x = rcClient.right + 1;
            ptClientLR.y = rcClient.bottom + 1;
            ClientToScreen(hWnd, &ptClientUL);
            ClientToScreen(hWnd, &ptClientLR);

            SetRect(&rcClient, ptClientUL.x, ptClientUL.y,
                    ptClientLR.x, ptClientLR.y);
            ClipCursor(&rcClient);
            GetCursorPos(&cursorPos);

            ptsBegin = MAKEPOINTS(lParam);

            if((wParam == MK_LBUTTON) && (draw_figure == 10)) {
                if(counterForBezier == 0) {
                    bezierPoint.x = xMouse;
                    bezierPoint.y = yMouse;
                    bezierCoordinate[0] = bezierPoint;
                    counterForBezier = 1;
                }
                else {
                    bezierPoint.x = xMouse;
                    bezierPoint.y = yMouse;
                    bezierCoordinate[2] = bezierPoint;
                    counterForBezier = 3;
                }
            }
            return 0;
        }

        case WM_MOUSEMOVE: {

            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);

            if(draw_figure == 2){
                mouse_drawLine(wParam, lParam, hWnd);
            }

            if(draw_figure == 3) {
                mouse_drawCircle(wParam, lParam, hWnd);
            }

            if(draw_figure == 1) {
                mouse_drawRectangle(wParam, lParam, hWnd);
            }


            if(draw_figure == 5 && MK_LBUTTON) {

                rectangle.left = xMouse - (eraserSize / 2);
                rectangle.right = xMouse + (eraserSize / 2);
                rectangle.top = yMouse - (eraserSize / 2);
                rectangle.bottom = yMouse + (eraserSize / 2);
                InvalidateRect(hWnd, &rectangle, FALSE);
                SendMessage(hWnd, WM_PAINT, 0, 0);
            }
            break;
        }

        case WM_LBUTTONUP: {
            fPrevLine = FALSE;
            ClipCursor(NULL);
            ReleaseCapture();

            if(counterForBezier == 1){
                bezierPoint.x = xMouse;
                bezierPoint.y = yMouse;
                bezierCoordinate[1] = bezierPoint;
                counterForBezier = 2;
            }

            if(counterForBezier == 3) {
                bezierPoint.x = xMouse;
                bezierPoint.y = yMouse;
                bezierCoordinate[3] = bezierPoint;
                counterForBezier = 0;
                SelectObject(hdc, bezierPen);
                PolyBezier(hdc, bezierCoordinate, 4);
                DeleteObject(bezierPen);
            }

            break;
        }


        case WM_COMMAND: {
            switch(wParam) {

                case DRAW_RACTANGLE : {
                    draw_figure = 1;
                    break;
                }

                case DRAW_LINE : {
                    draw_figure = 2;
                    break;
                }

                case ERASER_MEDIUM : {
                    draw_figure = 5;
                    eraserSize = 50;
                    break;
                }

                case ERASER_SMALL : {
                    draw_figure = 5;
                    eraserSize = 50;
                    break;
                }

                case ERASER_LARGE : {
                    draw_figure = 5;
                    eraserSize = 100;
                    break;
                }


                case DRAW_CIRCLE : {
                    draw_figure = 3;
                }

                case DRAW_BEZIER: {
                    draw_figure = 10;
                }
            }

            break;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }

    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}



