#include <windows.h>
#include "Button.h"
#include "EditText.h"
#include <time.h>
#include <thread>
#include <windowsx.h>
#include <advpub.h>
#include <c++/iostream>
#include <tchar.h>

#define IDC_BUTTON_1    1            // Button identifier
#define IDC_EDIT_1    2            // Edit box identifier
#define IDC_BUTTON_2    101            // Button identifier
#define IDC_EDIT_2    4            // Edit box identifier
#define MENU_ITEM_1 10
#define MENU_ITEM_2 11
#define MENU_ITEM_3 12
#define CONTROL_SPACE 101
#define ALT_LEFT 102
#define LIST_BOX 110
#define MyIcon 100001



// Add new popup menu
#define ADDPOPUPMENU(hmenu, string) \
	HMENU hSubMenu = CreatePopupMenu(); \
	AppendMenu(hmenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, string);

// Add a menu item
#define ADDMENUITEM(hmenu, ID, string) \
	AppendMenu(hSubMenu, MF_STRING, ID, string);


#define WIDTH 800
#define HEIGTH 600

HWND hEdit;
HWND hListBox;
Button *button;
Button *button2;
EditText *editText1;
EditText *editText2;
RECT rect;
static HDC dcOne;
HMENU hMenu;
HACCEL haccel;
HANDLE histAcc;
bool hotkeyPressed = false;
HBRUSH hbrush;
int CurPos = 0;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void addListBox(HWND hWnd){
    HINSTANCE hInstance = GetModuleHandle(NULL);
    hListBox = CreateWindowExW(WS_EX_CLIENTEDGE
            , L"LISTBOX", NULL
            , WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL
            , 200, 10, 300, 200
            , hWnd, (HMENU) LIST_BOX, hInstance, NULL);

    SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM) "One");
    SendMessage(hListBox, LB_ADDSTRING, 0,(LPARAM) "Two");
    SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"Three");
    SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"Four");
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd) {
    WNDCLASSEX wClass;
    ZeroMemory(&wClass, sizeof(WNDCLASSEX));
    wClass.cbClsExtra = NULL;
    wClass.cbSize = sizeof(WNDCLASSEX);
    wClass.cbWndExtra = NULL;
    wClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wClass.hCursor = LoadCursor(NULL, IDC_CROSS);
    wClass.hIcon = LoadIcon(NULL, IDC_WAIT);
    wClass.hIconSm = LoadIcon(NULL, IDC_WAIT);
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
                               WS_OVERLAPPEDWINDOW | WS_VSCROLL,
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
            if(hotkeyPressed) {
                RECT rect;
                GetClientRect(hWnd, &rect);
                InvalidateRect(hWnd, &rect, true);
                hbrush = CreateSolidBrush(RGB(rand() % 250, rand() % 250 , rand() % 250));
            }

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            FillRect(hdc,&ps.rcPaint, hbrush);

            EndPaint(hWnd, &ps);
        }
            break;

        case WM_CREATE: {
            srand(time(NULL));
            button = new Button("Click me !", 40, 10, 100, 40, hWnd, IDC_BUTTON_1);
            button2 = new Button("Select Item", 540, 10, 100, 20, hWnd, IDC_BUTTON_2);
            GetSystemMenu(hWnd, true);
            hMenu = CreateMenu();
            ADDPOPUPMENU(hMenu, "&Menu Commands");
            ADDMENUITEM(hMenu, MENU_ITEM_1, "&Say Something");
            ADDMENUITEM(hMenu, MENU_ITEM_2, "&Change Button position");
            ADDMENUITEM(hMenu, MENU_ITEM_3, "&Exit");
            SetMenu(hWnd, hMenu);
            RegisterHotKey(hWnd, CONTROL_SPACE, MOD_CONTROL, VK_SPACE);
            RegisterHotKey(hWnd, ALT_LEFT, MOD_ALT, VK_LEFT);
            addListBox(hWnd);

            HICON hIcon = (HICON) LoadImage(NULL, "themes.ico",  IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
            if (hIcon) {
                //Change both icons to the same icon handle.
                SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
                SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
                //This will ensure that the application icon gets changed too.
                SendMessage(GetWindow(hWnd, GW_OWNER), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
                SendMessage(GetWindow(hWnd, GW_OWNER), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
            }

            break;
        }

        case WM_GETMINMAXINFO: {
            MINMAXINFO *mmi = (MINMAXINFO *) lParam;
            mmi->ptMinTrackSize.x = 500;
            mmi->ptMaxTrackSize.x = 900;
            mmi->ptMinTrackSize.y = 500;
            mmi->ptMaxTrackSize.y = 900;
            return 0;
        }


        case WM_VSCROLL: {
            hotkeyPressed = true;
            SendMessage(hWnd, WM_PAINT, wParam, lParam);
            hotkeyPressed = false;

         CurPos = GetScrollPos(hWnd, SB_CTL);

                switch (LOWORD(wParam))
                {
                case SB_TOP:
                        CurPos = 0;
                        break;

                case SB_LINEUP:
                        if (CurPos > 0)
                                CurPos--;
                        break;

                case SB_THUMBPOSITION:
                        CurPos = HIWORD(wParam);
                        break;

                case SB_THUMBTRACK:
                        CurPos = HIWORD(wParam);
                        break;

                case SB_LINEDOWN:
                        if (CurPos < 240)
                                CurPos++;
                        break;

                case SB_BOTTOM:
                        CurPos = 240;
                        break;

                case SB_ENDSCROLL:
                        break;
                }

        SetScrollPos(hWnd, SB_CTL, CurPos, TRUE);

        }

        case WM_HOTKEY : {
            switch(wParam) {

                case CONTROL_SPACE: {
                    button2->setPos(rand() % 400, rand() % 400);
                    break;
                }

                case ALT_LEFT: {
                    hotkeyPressed = true;
                    SendMessage(hWnd, WM_PAINT, wParam, lParam);
                    hotkeyPressed = false;
                    break;
                }
            }
        }


        case WM_MOUSEMOVE: {
        }

        case WM_COMMAND: {

            switch (LOWORD(wParam)) {

                case IDC_BUTTON_1 : {
                    MessageBox(hWnd, "You just clicked the Button !", "Information", NULL);
                    break;
                }

                case MENU_ITEM_1 : {
                    MessageBox(hWnd, "Something !", "Menu command", NULL);

                    break;
                }

                case MENU_ITEM_2 : {
                    button->setPos( rand() % 400 + 10 , rand() % 400 + 10);
                    break;
                }

                case MENU_ITEM_3 : {
                    PostQuitMessage(0);
                    return 0;
                }



                case IDC_BUTTON_2: {

                    int count  = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
                    cout << count << endl;
                    switch(count){
                        case 0:
                            MessageBox(hWnd, "One", "Listbox", NULL);
                            break;
                        case 1:
                            MessageBox(hWnd, "TWO", "Listbox", NULL);
                            break;
                        case 2:
                            MessageBox(hWnd, "THREE", "Listbox", NULL);
                            break;
                        case 3:
                            MessageBox(hWnd, "FOUR", "Listbox", NULL);
                            break;
                    }
                    return 0;

                }

            }
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



