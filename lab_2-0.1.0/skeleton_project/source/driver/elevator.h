#pragma once
#include "elevio.h"

#define NUM_LIGHTS 8;  

/// @brief Struct holding the int matching floor levels in the desired order
typedef struct{
    int* queStart;
    int volatile queSize;
}Que;

/// @brief Struct, 
typedef struct{
    ButtonType type;
    int volatile status;
}Button;

typedef struct{
    int floorLevel;
    Button up;
    Button down;
}Floor;

typedef struct{
    Floor* floors;
    Que que;
    MotorDirection volatile direction;
}Elevator;

Button initializeButton(ButtonType type);
Floor initializeFloors(int floorLevel, int topLevel, int lowestLevel);
Elevator initializeElevator();

void addToQue(int floor);
void removeFromQue(int floor);
void clearQue();