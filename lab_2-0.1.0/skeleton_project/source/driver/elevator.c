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
}