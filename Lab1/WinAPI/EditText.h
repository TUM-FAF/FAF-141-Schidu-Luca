//
// Created by Luca Schidu on 2/5/2016.
//

#ifndef WINAPI_EDITTEXT_H
#define WINAPI_EDITTEXT_H
#include <string.h>

#include <windef.h>
#include <c++/cstring>
#include <string>


class EditText {

private:
    HWND hWndEdit;
    char *text;
    int posX;
    int posY;
    int width;
    int height;
    int id;
    HWND parent;

public:
    EditText(char* text, int posX, int posY, int width, int height, HWND parent, int id );
    int getId();
    int getPosX();
    int getPosY();
    int getHeight();
    int getWidth();
    void setText(char * string1);
    void setFont();

};


#endif //WINAPI_EDITTEXT_H
