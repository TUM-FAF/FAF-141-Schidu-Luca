//
// Created by Luca Schidu on 2/5/2016.
//

#include <libloaderapi.h>
#include <windows.h>
#include "EditText.h"
#include <string>
using namespace std;

EditText::EditText(char *text, int posX, int posY, int width, int height, HWND parent, int id) {

    this->parent = parent;

    hWndEdit=CreateWindowEx(WS_EX_CLIENTEDGE,
                         "EDIT",
                         "",
                         WS_CHILD|WS_VISIBLE|
                         ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL,
                         posX,
                         posY,
                         width,
                         height,
                         parent,
                         (HMENU)id,
                         GetModuleHandle(NULL),
                         NULL);


}


int EditText::getHeight() {return this->height; }
int EditText::getId(){return this->id;}
int EditText::getWidth(){return this->width;}
int EditText::getPosX(){return this->posX;}
int EditText::getPosY(){return this->posY;}
void EditText::setText(char* string1){
    SetWindowTextA(hWndEdit, string1);
}

void EditText::setFont(){
    HFONT hFont = CreateFont (20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Comic Sans MS");
    SendMessage(hWndEdit, WM_SETFONT, WPARAM (hFont), TRUE);

}

