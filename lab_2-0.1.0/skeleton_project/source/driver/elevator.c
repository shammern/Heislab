#include "elevator.h"


Button initializeButton(ButtonType type){
    Button button;
    button.type = type;
    button.status = 0;
    return button;
}

Floor initializeFloors(int floorLevel, int topLevel, int lowestLevel){
    assert(floorLevel >= 0 && floorLevel < N_FLOORS);
    Floor floor;
    floor.floorLevel = floorLevel;
    if(!topLevel){
        floor.up = initializeButton(BUTTON_HALL_UP);
    }
    if(!lowestLevel){
        floor.down = initializeButton(BUTTON_HALL_DOWN);
    }
}

Elevator initializeElevator(){
    Elevator elevator;
    elevator.floors = malloc(N_FLOORS); 
    *elevator.floors = initializeFloors(0,0,1);
    *(elevator.floors + N_FLOORS*sizeof(Floor)) = initializeFloors(N_FLOORS-1,1,0);
    for(int i = 1; i < N_FLOORS-1; i++){
        Floor floor  = initializeFloors(i,0,0);
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
    return elevator;
}

void driveElevator(Elevator elev, int destination){
    if(destination < elev.currentFloor){
        updateElevatorDirection(elev, DIRN_UP);
        while(destination != elev.currentFloor){
            elevio_motorDirection(DIRN_UP);
            updateCurrentFloor(elev);
        }
        elevio_motorDirection(DIRN_STOP);
    }

    if(destination > elev.currentFloor){
        updateElevatorDirection(elev, DIRN_DOWN);
        while(destination != elev.currentFloor){
            elevio_motorDirection(DIRN_DOWN);
            updateCurrentFloor(elev);
        }
        elevio_motorDirection(DIRN_STOP);
    }
};

void updateCurrentFloor(Elevator elev){
    elev.currentFloor = elevio_floorSensor();
}

void updateElevatorDirection(Elevator elev, MotorDirection direction){
    elev.direction = direction;
}