#include <time.h>

#include "globalVariables.h"
#include "elevator.h"
void updateCurrentFloor(){
    if(elevio_floorSensor != -1){
        elev.currentFloor = elevio_floorSensor();
    }
}

void changeButtonandLightStatus(int floor, ButtonType type, int status){
    elevio_buttonLamp(floor, type, status);
    if(type == DIRN_UP){
        elev.upButtons[floor].status = status;
        return;
    }
    else if(type == DIRN_UP){
        elev.downButtons[floor].status = status;
        return;
    }
}

Button initializeButton(ButtonType type){
    Button button;
    button.type = type;
    button.status = 0;
    return button;
}

Elevator initializeElevator(){
    Elevator elevator;

    elevator.upButtons = malloc(sizeof(Button)*(N_FLOORS));
    elevator.downButtons = malloc(sizeof(Button)*(N_FLOORS)); //Allocates extra slots, but helps us avoid offset in button order

    elevator.upButtons[0] = initializeButton(DIRN_UP);
    elevator.downButtons[N_FLOORS-1] = initializeButton(DIRN_DOWN);

    for(int i = 1; i < N_FLOORS-2; i++){
        elevator.cabinButtons[i] = initializeButton(DIRN_STOP);
        elevator.upButtons[i] = initializeButton(DIRN_UP);
        elevator.downButtons[i] = initializeButton(DIRN_DOWN);
    }

    //Takes care of out initiating routine
    while(1){
        elevio_motorDirection(DIRN_UP);
        if(elevio_floorSensor() != -1){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
    }

    elevator.currentFloor = elevio_floorSensor();
    elevator.direction = DIRN_STOP;
    printf("Elevator initilized, current floor: %d\n", elevator.currentFloor);
    nanosleep(&(struct timespec){0, 10*1000*1000}, NULL);
    printf("Elevator done sleeping\n");
    return elevator;
}

void driveElevator(){
    printf("Elevator running, current floor: %d\n", elev.currentFloor);
    if((*ptrToHead) == NULL){
        elevio_motorDirection(DIRN_STOP);
        return;
    }
    elevio_motorDirection((*ptrToHead)->direction);
    /*
    //Code for running elevator upwards
    if(destination > elev.currentFloor){
        elev.direction = destination;
        elevio_motorDirection(DIRN_UP);
        while(elev -> currentFloor != destination){
            updateCurrentFloor(elev);
            if(elevio_stopButton()){
                elevio_motorDirection(DIRN_STOP);
            break;
            }
        }
        elevio_motorDirection(DIRN_STOP); 
    
    }
    
    //Code for running elevator downwards
    if(destination < elev -> currentFloor){
        updateElevatorDirection(elev, DIRN_DOWN);
        elevio_motorDirection(DIRN_DOWN);
        while(elev -> currentFloor != destination){
            updateCurrentFloor(elev);
            if(elevio_stopButton()){
                elevio_motorDirection(DIRN_STOP);
            break;
            }
        }
        elevio_motorDirection(DIRN_STOP);    
    }
        
    printf("Elevator has arrived at your destinationfloor: %d\n", destination);
    */
};

void freeMemory(Elevator *elev){
    free(elev->upButtons);
    free(elev->downButtons);
}
