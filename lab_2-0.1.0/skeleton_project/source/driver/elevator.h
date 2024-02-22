#pragma once
#include "elevio.h"
#include "que.h"

/// @brief Struct for Buttons, holding type and  status on/off 
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

