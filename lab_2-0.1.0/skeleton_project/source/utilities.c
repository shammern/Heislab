#include "utilities.h"


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
        dir = elev->currentFloor < floorPushed ? DIRN_DOWN : DIRN_UP; //TODO, start bugtesting by changing here, changed 06.03.24
        break;

    default:
        break;
    }
    return dir;    
}

void controllingAllButtonsExecuteActive(Elevator* elev, int stoppedAtFloor, int* numberPushedOnFloor){
    for(int f = 0; f < N_FLOORS; f++){
        //For up and down-button
        for(int b = 0; b < N_BUTTONS -1; b++){
            int btnPressed = elevio_callButton(f, b);
            if(btnPressed && !elevio_stopButton()){
                MotorDirection dir = buttonTypeToDir(b, f, elev);
                changeButtonandLightStatus(f, b, 1, elev);
                addToQue(f,dir,elev->currentFloor);          
            }
        }
        //For cabin-button
        int btnPressed = elevio_callButton(f, BUTTON_CAB);
        if(btnPressed && !elevio_stopButton()){
            MotorDirection dir = buttonTypeToDir(BUTTON_CAB, f, elev);
            changeButtonandLightStatus(f, BUTTON_CAB, 1, elev);
            //addToQue(f,dir,elev->currentFloor); 
            if(stoppedAtFloor){
                addCabinOverrideFirstQue(f, dir, elev->currentFloor, numberPushedOnFloor);
            }
            else{
                addToQue(f,dir,elev->currentFloor); 
            }    
        }
    }
}