//
// Created by Luca Schidu on 4/18/2016.
//

#include <time.h>
#include "Controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

Controller::Controller() {
    initTrafficLights();
    srand(time(NULL));
    trafficLight = 1;
}

void Controller::increaseRandom() {
    this->randomG++;
    cout << randomG << " ";
}

void Controller::decreaseRandom() {
    if(randomG > 50){
        this->randomG--;
        cout << randomG << " ";

    }
}

void Controller::initTrafficLights() {

    trOne = new TrafficLight(280, 150, 40, false);
    trTwo = new TrafficLight(480, 150, 40, true);
    trThree = new TrafficLight(280, 400, 40, true);
    trFour = new TrafficLight(480, 400, 40, false);
}

void Controller::generateCar() {

    int vector = rand() % 4;
    bool canGenerate;

    switch (vector){
        case 0:
            vector = rand() % randomG;
            if(vector == 0){
                canGenerate = true;
                for(int i = 0; i < vecOne.size(); i++){
                    if(vecOne[i].getX() < 0 )
                        canGenerate = false;
                }

                if(canGenerate){
                    car = new Car(-100, 330, 80, 40, 1);
                    if(rand() % 10 == 0) car->setColor(255, 0, 0);
                    vecOne.push_back(*car);

                }
            }

            break;
        case 1:
            vector = rand() % randomG;
            if(vector == 0){
                canGenerate = true;
                for(int i = 0; i < vecTwo.size(); i++){
                    if(vecTwo[i].getY() < 0 )
                        canGenerate = false;
                }

                if(canGenerate){
                    car = new Car(330, -100, 80, 40, 2);
                    if(rand() % 10 == 0) car->setColor(255, 0, 0);
                    vecTwo.push_back(*car);
                }
                cout << vecTwo.size() << " " ;
            }

            break;
        case 2:
            vector = rand() % randomG;
            if(vector == 0){
                canGenerate = true;
                for(int i = 0; i < vecThree.size(); i++){
                    if(vecThree[i].getX() + vecThree[i].getHeight() > 800 )
                        canGenerate = false;
                }

                if(canGenerate){
                    car = new Car(820, 230, 80, 40, 3);
                    if(rand() % 10 == 0) car->setColor(255, 0, 0);
                    vecThree.push_back(*car);
                }
            }

            break;
        case 3:
            vector = rand() % randomG;
            if(vector == 0){
                canGenerate = true;

                for(int i = 0; i < vecFour.size(); i++){
                    if(vecFour[i].getY() + vecFour[i].getHeight() > 600 )
                        canGenerate = false;
                }
                if(canGenerate){
                    car = new Car(430, 600, 80, 40, 4);
                    if(rand() % 10 == 0) car->setColor(255, 0, 0);
                    vecFour.push_back(*car);
                }
            }

            break;
    }
}

void Controller::drawCars(HDC hdcMem) {

    for(int i = 0; i < vecOne.size(); i++) {
        vecOne[i].drawCar(hdcMem);
    }

    for(int i = 0; i < vecTwo.size(); i++) {
        vecTwo[i].drawCar(hdcMem);
    }

    for(int i = 0; i < vecThree.size(); i++) {
        vecThree[i].drawCar(hdcMem);
    }

    for(int i = 0; i < vecFour.size(); i++) {
        vecFour[i].drawCar(hdcMem);
    }
}


void Controller::drawPedestrians(HDC hdcMem) {
    for(int i = 0; i < pedOne.size(); i++) {
        pedOne[i].drawPedestrian(hdcMem);
    }

    for(int i = 0; i < pedTwo.size(); i++) {
        pedTwo[i].drawPedestrian(hdcMem);
    }
}

void Controller::drawTrafficLights(HDC hdcMem) {
    trOne->draw(hdcMem);
    trTwo->draw(hdcMem);
    trThree->draw(hdcMem);
    trFour->draw(hdcMem);
}

void Controller::moveCars() {

        for(int i = 0; i < vecOne.size(); i++) {

            if(trafficLight == 1) {
                if(vecOne[i].isSpecial() && canCarMove(i, vecOne, 1)){
                    vecOne[i].setX(vecOne[i].getX() + vecOne[i].getSpeed());
                    isSpecialCarMoving = true;
                }else
                if(vecOne[i].getX() <= 300 - 100 || vecOne[i].getX() > 320 ) {
                    if(canCarMove(i, vecOne, 1))
                        vecOne[i].setX(vecOne[i].getX() + vecOne[i].getSpeed());
                }
            }else{
                vecOne[i].setX(vecOne[i].getX() +  vecOne[i].getSpeed());
            }
        }

        for(int i = 0; i < vecTwo.size(); i++) {
            if(trafficLight == 0) {
                if(vecTwo[i].isSpecial() && canCarMove(i, vecTwo, 2)){
                    vecTwo[i].setX(vecTwo[i].getY() + vecTwo[i].getSpeed());
                    isSpecialCarMoving = true;
                }else
                if(vecTwo[i].getY() <= 150 - 50 || vecTwo[i].getY() > 170) {
                    if(canCarMove(i, vecTwo, 2))
                        vecTwo[i].setY(vecTwo[i].getY() +  vecTwo[i].getSpeed());
                }
            }else{
                vecTwo[i].setY(vecTwo[i].getY() +  vecTwo[i].getSpeed());
            }
        }

        for(int i = 0; i < vecThree.size(); i++) {
            if(trafficLight == 1) {
                if(vecThree[i].isSpecial() && canCarMove(i, vecThree, 3)){
                    vecThree[i].setX(vecThree[i].getX() -  vecThree[i].getSpeed());
                    isSpecialCarMoving = true;
                }else
                if(vecThree[i].getX() >= 500 + 10 || vecThree[i].getX() < 490) {
                    if(canCarMove(i, vecThree, 3))
                        vecThree[i].setX(vecThree[i].getX() -  vecThree[i].getSpeed());
                }
            }else{
                vecThree[i].setX(vecThree[i].getX() -  vecThree[i].getSpeed());
            }
        }

        for(int i = 0; i < vecFour.size(); i++) {
            if(trafficLight == 0) {
                if(vecFour[i].isSpecial() && canCarMove(i, vecFour, 4)){
                    vecFour[i].setY(vecFour[i].getY() - vecFour[i].getSpeed());
                    isSpecialCarMoving = true;
                }else
                if(vecFour[i].getY() >= 400 + 10 || vecFour[i].getY() < 380) {
                    if(canCarMove(i, vecFour, 4))
                        vecFour[i].setY(vecFour[i].getY() - vecFour[i].getSpeed());
                }
            }else{
                vecFour[i].setY(vecFour[i].getY() - vecFour[i].getSpeed());
            }
        }
 }


void Controller::generatePedestrian() {

    int vector = rand() % 2;
    int canGenerate;

    switch (vector) {
        case 0:
            vector = rand() % randomG;
            if (vector == 0) {
                canGenerate = true;
                for (int i = 0; i < pedOne.size(); i++) {
                    if (pedOne[i].getX() < 0)
                        canGenerate = false;
                }

                if (canGenerate) {
                    pedestrian = new Pedestrian(-100, 385, 30, 30, 1);
                    pedOne.push_back(*pedestrian);
                }
            }
            break;
        case 1:
            vector = rand() % randomG;
            if (vector == 0) {
                canGenerate = true;
                for (int i = 0; i < pedTwo.size(); i++) {
                    if (pedTwo[i].getY() < 0)
                        canGenerate = false;
                }

                if (canGenerate) {
                    pedestrian = new Pedestrian(285, -100, 30, 30, 2);
                    pedTwo.push_back(*pedestrian);
                }
            }
            break;
    }
}

void Controller::changeTraficLight() {

    trOne->changeColor();
    trTwo->changeColor();
    trThree->changeColor();
    trFour->changeColor();

    if(trafficLight == 0) {
        trafficLight = 1;
    }else{
        trafficLight = 0;
    }
}


void Controller::movePedestrians() {

    for(int i = 0; i < pedOne.size(); i++) {

        if(trafficLight == 1) {
            if(pedOne[i].getX() <= 300 - 100 || pedOne[i].getX() > 320 ) {
                if(canPedestrianMove(i, pedOne, 1))
                    pedOne[i].setX(pedOne[i].getX() + 2);
            }
        }else{
            pedOne[i].setX(pedOne[i].getX() + 2);
        }
    }

    for(int i = 0; i < pedTwo.size(); i++) {
        if(trafficLight == 0) {

            if(pedTwo[i].getY() <= 150 - 50 || pedTwo[i].getY() > 170) {
                if(canPedestrianMove(i, pedTwo, 2))
                    pedTwo[i].setY(pedTwo[i].getY() + 2);
            }
        }else{
            pedTwo[i].setY(pedTwo[i].getY() + 2);
        }
    }

}


bool Controller::canPedestrianMove(int index, vector<Pedestrian> ped, int direction) {

    bool canMove = true;

    for(int i = 0; i < index; i++) {

        if(index != i) {
            switch(direction) {
                case 1:
                    if(ped[index].getX() + ped[index].getWidth() + 10 >= ped[i].getX()) {
                        canMove = false;
                    }
                    break;
                case 2:
                    if(ped[index].getY() + ped[index].getWidth() + 10 >= ped[i].getY()) {
                        canMove = false;
                    }
                    break;
            }
        }
    }

    return canMove;

}

bool Controller::canCarMove(int index, vector<Car> cars, int direction) {
    bool canMove = true;

    for(int i = 0; i < index; i++) {

        if(index != i) {
            switch(direction) {
                case 1:
                    if(cars[index].getX() + cars[index].getWidth() + 10 >= cars[i].getX()) {
                        canMove = false;
                    }
                    break;
                case 2:
                    if(cars[index].getY() + cars[index].getWidth() + 10 >= cars[i].getY()) {
                        canMove = false;
                    }
                    break;
                case 3:
                    if(cars[index].getX() - 10 <= cars[i].getX() + cars[i].getWidth()) {
                        canMove = false;
                    }
                    break;
                case 4:
                    if(cars[index].getY() - 10 <= cars[i].getY() + cars[i].getWidth()) {
                        canMove = false;
                    }
                    break;
            }
        }
    }

    return canMove;
}

