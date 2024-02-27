#pragma once
#include <signal.h>
#include "elevio.h"
#include "elevator.h"

MotorDirection buttonTypeToDir(ButtonType type, int floor, Elevator* elev);