//
// Created by Luca Schidu on 4/18/2016.
//

#include "Car.h"

void Car::drawCar(HDC hdcMem) {
    SelectObject(hdcMem, brush);

    if(direction == 2 || direction == 4) {
        Rectangle(hdcMem, x, y, x + height, y + width);
    }else{
        Rectangle(hdcMem, x, y, x + width, y + height);
    }
}


void Car::setY(int y) {
    this->y = y;
}

void Car::setX(int x) {
    this->x = x;
}

int Car::getX() {
    return this->x;
}

int Car::getY(){
    return this->y;
}

int Car::getDirection() {
    return this->direction;
}

bool Car::isSpecial() {
    return this->special;
}



Car::Car(int x, int y, int width, int height, int direction) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->direction = direction;
    brush = CreateSolidBrush(RGB(0, 0, 0));
    speed = 3;
    special = false;
}

int Car::getWidth() {
    return this->width;
}


int Car::getHeight() {
    return this->height;
}

void Car::deleteBrush() {
    DeleteObject(brush);
}

void Car::setSpeed(int speed) {
    this->speed = speed;
}

int Car::getSpeed() {
    return this->speed;
}

void Car::setColor(int r, int g, int b) {
    brush = CreateSolidBrush(RGB(r, g, b));
    (r == 255) ? special = true : special = false;
}