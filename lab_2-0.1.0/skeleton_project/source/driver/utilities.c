#include "utilities.h"

MotorDirection buttonTypeToDir(ButtonType type){
    MotorDirection dir;
    switch (type)
    {
    case BUTTON_HALL_UP:
        dir = DIRN_UP;
        break;
    
    case BUTTON_HALL_DOWN:
        dir = DIRN_UP;
        break;

    default:
        break;
    }
    return dir;    
}