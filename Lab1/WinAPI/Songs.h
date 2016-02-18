//
// Created by Luca Schidu on 2/17/2016.
//

#ifndef WINAPI_SONGS_H
#define WINAPI_SONGS_H


#include <c++/thread>

class Songs {
private:
    int C = 523; // DO - dura 191ms - 382ms
    int D = 587; // RE - dura 170ms - 340ms
    int E = 659; // MI - dura 152ms - 304ms
    int F = 698; // FA - dura 143ms - 286ms
    int G = 740; // SOL - dura 135ms - 270ms
    int A = 880; // LA - dura 114ms - 228ms
    int B = 988; // SI - dura 110ms - 220ms

public:
    void refrenSolo();
    void starWars();
    void HBDAY();


};


#endif //WINAPI_SONGS_H
