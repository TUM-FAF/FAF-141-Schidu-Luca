//
// Created by Luca Schidu on 4/18/2016.
//

#ifndef WINAPI_CAR_H
#define WINAPI_CAR_H


#include <windef.h>
#include <winuser.h>
#include <wingdi.h>

class Car {
private:
    int width;
    int height;
    int x;
    int y;
    int direction;
    HBRUSH brush;
    int speed;
    bool special;

public:
    Car(int x, int y, int width, int height, int direction);
    int getWidth();
    int getHeight();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    int getDirection();
    void drawCar(HDC hdcMem);
    void deleteBrush();
    int getSpeed();
    void setSpeed(int speed);
    void setColor(int r, int g, int b);
    bool isSpecial();

};


#endif //WINAPI_CAR_H
