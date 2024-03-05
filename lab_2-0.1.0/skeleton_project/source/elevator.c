#include "elevator.h"
#include "globalVariables.h"

void updateCurrentFloor(Elevator* elev){
    if(elevio_floorSensor() != -1){
        elev->currentFloor = elevio_floorSensor();
    }
}

void changeButtonandLightStatus(int floor, ButtonType type, int status, Elevator* elev){
    elevio_buttonLamp(floor, type, status);
    // if(type == DIRN_UP){
    //     elev->upButtons[floor].status = status;
    //     return;
    // }
    // else if(type == DIRN_UP){
    //     elev->downButtons[floor].status = status;
    //     return;
    // }
}

// Button initializeButton(ButtonType type){
//     Button button;
//     button.type = type;
//     button.status = 0;
//     return button;
// }

Elevator initializeElevator(){
    Elevator elevator;


    //elevator.upButtons = malloc(sizeof(Button)*(N_FLOORS));
    //elevator.downButtons = malloc(sizeof(Button)*(N_FLOORS)); //Allocates extra slots, but helps us avoid offset in button order

    //elevator.upButtons[0] = initializeButton(BUTTON_HALL_UP);
    //elevator.downButtons[N_FLOORS-1] = initializeButton(BUTTON_HALL_DOWN);

    // for(int i = 1; i < N_FLOORS-2; i++){
    //     elevator.cabinButtons[i] = initializeButton(BUTTON_CAB);
    //     elevator.upButtons[i] = initializeButton(BUTTON_HALL_UP);
    //     elevator.downButtons[i] = initializeButton(BUTTON_HALL_DOWN);
    // }

    //Takes care of out initiating routine
    while(1){
        elevio_motorDirection(DIRN_UP);
        if(elevio_floorSensor() != -1){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
    }

    
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            changeButtonandLightStatus(f, b, 0, &elevator);
        }
    }
    

    elevator.currentFloor = elevio_floorSensor();
    //elevator.direction = DIRN_STOP;
    printf("Elevator initilized, current floor: %d\n", elevator.currentFloor);
    
    return elevator;
}

void driveElevator(Elevator* elev, MotorDirection *prevDirection, int *prevStopped){

    if((*ptrToHead) == NULL){
        elevio_motorDirection(DIRN_STOP);
        return;
    }
    if((*ptrToHead)->floorLevel > elev->currentFloor){
        prevStopped = 0;
        elevio_motorDirection(DIRN_UP);
        return;
    }
    if ((*ptrToHead)->floorLevel < elev->currentFloor){
        prevStopped = 0;
        elevio_motorDirection(DIRN_DOWN);
        return;
    } 

    if(*prevDirection == DIRN_UP){
        elevio_motorDirection(DIRN_UP);
        *prevDirection = DIRN_STOP;
        prevStopped = 0;
        return;
    }

    if(*prevDirection == DIRN_DOWN){
        elevio_motorDirection(DIRN_DOWN);
        *prevDirection = DIRN_STOP;
        prevStopped = 0;
        return;
    }
};

// void freeMemory(Elevator *elev){
//     free(elev->upButtons);
//     free(elev->downButtons);
// }
