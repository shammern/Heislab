#pragma once
#include <stdlib.h>
#include <time.h>

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
    //Consider adding button up and down here, to keep information about direction in button
    MotorDirection volatile direction;
    int volatile currentFloor;
}Elevator;

void driveElevator(Elevator *elev, int destination);
void updateCurrentFloor(Elevator *elev);
void updateMotorDirection(Elevator *elev, MotorDirection direction);

Button initializeButton(ButtonType type);
Floor initializeFloors(int floorLevel, int topLevel, int lowestLevel);
Elevator initializeElevator();
void freeMemory(Elevator *elev);

