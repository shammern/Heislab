#pragma once
#include <stdlib.h>
#include <time.h>

#include "driver/elevio.h"

/// @brief Struct for Buttons, holding type and  status on/off 
typedef struct{
    ButtonType type;
    int volatile status; //TODO, consider remove struct if status is never needed
}Button;
//May add floorLevel

typedef struct{
    Button upButtons[N_FLOORS];
    Button downButtons[N_FLOORS];
    Button cabinButtons[N_FLOORS];
    MotorDirection volatile direction;
    int volatile currentFloor;
}Elevator;

void driveElevator(Elevator* elev, MotorDirection *prevDirection, int *prevStopped);
void updateCurrentFloor(Elevator* elev);
void changeButtonandLightStatus(int floor, ButtonType type,int status, Elevator* elev);

Button initializeButton(ButtonType type);
Elevator initializeElevator();

void freeMemory(Elevator *elev);

