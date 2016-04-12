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

