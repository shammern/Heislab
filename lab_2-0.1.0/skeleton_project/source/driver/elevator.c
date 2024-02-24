#include <time.h>

#include "globalVariables.h"
#include "elevator.h"
void updateCurrentFloor(Elevator *elev){
    elev -> currentFloor = elevio_floorSensor();
}

void updateElevatorDirection(Elevator *elev, MotorDirection direction){
    elev -> direction = direction;
}

Button initializeButton(ButtonType type){
    Button button;
    button.type = type;
    button.status = 0;
    return button;
}

Floor initializeFloors(int floorLevel, int topLevel, int lowestLevel){
    //assert(floorLevel >= 0 && floorLevel < N_FLOORS);
    Floor floor;
    floor.floorLevel = floorLevel;
    if(!topLevel){
        floor.up = initializeButton(BUTTON_HALL_UP);
    }
    if(!lowestLevel){
        floor.down = initializeButton(BUTTON_HALL_DOWN);
    }
    return floor;
}

Elevator initializeElevator(){
    Elevator elevator;

    elevator.floors = malloc(sizeof(Floor)*N_FLOORS); 

    /*
    Floor floor = initializeFloors(0,0,1);
    elevator.floors = &floor;
    Floor lastFloor = initializeFloors(N_FLOORS-1,1,0);
    *(elevator.floors + N_FLOORS*sizeof(Floor)) = lastFloor;
    */

    elevator.floors[0] = initializeFloors(0,0,1);
    elevator.floors[N_FLOORS-1] = initializeFloors(N_FLOORS-1,1,0);

    for(int i = 1; i < N_FLOORS-2; i++){
        /*Floor floor = initializeFloors(i,0,0);
        *(elevator.floors + i*sizeof(Floor)) = floor;
        */
       elevator.floors[i] = initializeFloors(i,0,0);
    }

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

void driveElevator(Elevator *elev, int destination){
    printf("Elevator running, current floor: %d\n", elev -> currentFloor);

    //Code for running elevator upwards
    if(destination > elev -> currentFloor){
        
        updateElevatorDirection(elev, DIRN_UP);
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
};

void freeMemory(Elevator *elev){
    free(elev->floors);
}
