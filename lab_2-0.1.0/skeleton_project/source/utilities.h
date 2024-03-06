#pragma once

#include "driver/elevio.h"
#include "elevator.h"

MotorDirection buttonTypeToDir(ButtonType type, int floor, Elevator* elev);

void controllingAllButtonsExecuteActive(Elevator* elev, int stoppedAtFloor, int* numberPushedOnFloor);