#include "utilities.h"
#include "elevator.h"

MotorDirection buttonTypeToDir(ButtonType type, int floorPushed, Elevator* elev){
    MotorDirection dir;
    switch (type)
    {
    case BUTTON_HALL_UP:
        dir = DIRN_UP;
        break;
    
    case BUTTON_HALL_DOWN:
        dir = DIRN_DOWN;
        break;

    case BUTTON_CAB:
        dir = elev->currentFloor < floorPushed ? DIRN_UP : DIRN_DOWN;
        break;

    default:
        break;
    }
    return dir;    
}