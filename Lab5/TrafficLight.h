//
// Created by Luca Schidu on 4/23/2016.
//

#ifndef WINAPI_TRAFFICLIGHT_H
#define WINAPI_TRAFFICLIGHT_H


#include <windef.h>
#include <winuser.h>
#include <wingdi.h>

class TrafficLight {

private:
    int x;
    int y;
    int radius;
    bool isRed;
    HBRUSH redBrush;
    HBRUSH greenBrush;

public:
    TrafficLight(int x, int y, int radius, bool isRed);
    void changeColor();
    void draw(HDC hdcMem);

};


#endif //WINAPI_TRAFFICLIGHT_H
