//
// Created by Luca Schidu on 4/26/2016.
//

#ifndef WINAPI_PEDESTRIANS_H
#define WINAPI_PEDESTRIANS_H


#include <windef.h>

class Pedestrian {
private:
    int width;
    int height;
    int x;
    int y;
    int direction;
    HBRUSH brush;
public:
    Pedestrian(int x, int y, int width, int height, int direction);
    int getWidth();
    int getHeight();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    int getDirection();
    void drawPedestrian(HDC hdcMem);
    void deleteBrush();
};


#endif //WINAPI_PEDESTRIANS_H
