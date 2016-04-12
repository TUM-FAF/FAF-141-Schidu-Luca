//
// Created by Luca Schidu on 4/11/2016.
//

#ifndef WINAPI_OBJECT_H
#define WINAPI_OBJECT_H


class Object {
    int width;
    int heigth;
    int x;
    int y;
    int r, g, b;


public:
    Object( int x, int y, int width, int height);
    void setPosition(int x, int y);
    void setDimension(int width, int height);
    void setColor(int r, int g, int b);
    int getR();
    int getG();
    int getB();
    int getWidth();
    int getHeight();
    int getX();
    int getY();

};


#endif //WINAPI_OBJECT_H
