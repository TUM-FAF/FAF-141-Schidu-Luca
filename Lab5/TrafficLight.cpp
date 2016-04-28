//
// Created by Luca Schidu on 4/23/2016.
//

#include "TrafficLight.h"


TrafficLight::TrafficLight(int x, int y, int radius, bool isRed) {
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->isRed = isRed;

    redBrush = CreateSolidBrush(RGB(255, 0, 0));
    greenBrush = CreateSolidBrush(RGB(0, 255, 0));

}

void TrafficLight::draw(HDC hdcMem) {

    if(isRed){
        SelectObject(hdcMem, redBrush);
    }else {
        SelectObject(hdcMem, greenBrush);
    }
    
    Ellipse(hdcMem, x, y, x + radius, y + radius);

}

void TrafficLight::changeColor() {

    (isRed) ? isRed = false : isRed = true;
}