#pragma once
#include <stdlib.h>
#include <time.h>

#include "elevio.h"
#include "que.h"


/// @brief Struct for Buttons, holding type and  status on/off 
typedef struct{
    ButtonType type;
    int volatile status; //TODO, consider remove struct if status is never needed
}Button;
//May add floorLevel

typedef struct{
    Button* upButtons;
    Button* downButtons;
    Button* cabinButtons;
    MotorDirection volatile direction;
    int volatile currentFloor;
}Elevator;

void driveElevator();
void updateCurrentFloor();
void changeButtonandLightStatus(int floor, ButtonType type,int status);

Button initializeButton(ButtonType type);
Elevator initializeElevator();

void freeMemory(Elevator *elev);

