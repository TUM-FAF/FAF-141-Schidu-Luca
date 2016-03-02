//
// Created by Luca Schidu on 2/5/2016.
//

#include "Button.h"


Button::Button(char *text, int posX, int posY, int width, int height, HWND parent, int id) {

    this->posX = posX;
    this->posY = posY;
    this->width = width;
    this->height = height;
    this->parent = parent;

    hWndButton=CreateWindowEx(NULL,
                              "BUTTON",
                              text,
                              WS_TABSTOP|WS_VISIBLE|
                              WS_CHILD|BS_DEFPUSHBUTTON,
                              posX,
                              posY,
                              width,
                              height,
                              parent,
                              (HMENU)id,
                              GetModuleHandle(NULL),
                              NULL);
}


int Button::getHeight() {return this->height; }
int Button::getId(){return this->id;}
int Button::getWidth(){return this->width;}
int Button::getPosX(){return this->posX;}
int Button::getPosY(){return this->posY;}

void Button::setPos(int x, int y){
    this->posX = x;
    this->posY = y;
    SetWindowPos(hWndButton, HWND_TOP, x, y, x/2, y/2, 1);
    InvalidateRect(hWndButton, NULL, true);
}

void Button::setFont(){
    HFONT hFont = CreateFont (20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Comic Sans MS");
    SendMessage(hWndButton, WM_SETFONT, WPARAM (hFont), TRUE);

}