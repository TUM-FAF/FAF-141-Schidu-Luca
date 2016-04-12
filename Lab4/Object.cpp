//
// Created by Luca Schidu on 4/11/2016.
//

#include "Object.h"

Object::Object(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->heigth = height;
}


void Object::setColor(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Object::setDimension(int width, int height) {
    this->width = width;
    this->heigth = height;
}

void Object::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

int Object::getX() {
    return this->x;
}

int Object::getY() {
    return this->y;
}

int Object::getHeight() {
    return this->heigth;
}

int Object::getWidth() {
    return this->width;
}

int Object::getR() {
    return this->r;
}

int Object::getG() {
    return this->g;
}

int Object::getB() {
    return this->b;
}

void Object::setCircle(bool circle) {
    this->circle = circle;
}


void Object::setDirection(int direction) {
    this->direction = direction;
}

int Object::getDirection() {
    return this->direction;
}

void Object::wallCollision(int width, int height) {

    bool collision = false;

    if(y <= 0) {
        switch(direction) {
            case 2:
                direction = 0;
                break;
            case 3:
                direction = 1;
                break;
        }
    }

    if(x <= 0) {
        switch(direction) {
            case 3:
                direction = 2;
                break;
            case 1:
                direction = 0;
                break;
        }
        circle = false;
    }

    if(x + this->width >= width ) {
        switch(direction) {
            case 0:
                direction = 1;
                break;
            case 2:
                direction = 3;
                break;
        }
        circle = false;
    }

    if(y + this->heigth >= height) {
        switch(direction) {
            case 1:
                direction = 3;
                break;
            case 0:
                direction = 2;
                break;
        }
    }
}


bool Object::objectCollision(int X, int Y) {

    bool collision = false;

    if(y <= Y + heigth && y > Y && x <= X + width && x >= X  ) {
        collision = true;
    }


   return collision;
}


void Object::setSpeed(int speed) {
    this->speed = speed;
}

int Object::getSpeed() {
    return this->speed;
}

bool Object::isCircle() {
    return this->circle;
}