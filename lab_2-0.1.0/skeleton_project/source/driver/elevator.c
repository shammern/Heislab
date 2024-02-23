#include "elevator.h"
#include <time.h>

/// @brief Function updates the floor where the elevator currently is located
/// @param elev pointer to elevator object 
void updateCurrentFloor(Elevator *elev){
    elev -> currentFloor = elevio_floorSensor();
}

/// @brief Function updates the current elevator direction
/// @param elev pointer to elevator object
/// @param direction updates the direction parameter attached to the elevator object
void updateElevatorDirection(Elevator *elev, MotorDirection direction){
    elev -> direction = direction;
}

/// @brief Function that initilizes a button
/// @param type type of button to be created
/// @return the new button created
Button initializeButton(ButtonType type){
    Button button;
    button.type = type;
    button.status = 0;
    return button;
}

/// @brief Function that initilises the floors
/// @param floorLevel florlevel to be made
/// @param topLevel bool value of the floorlevel to be made is the top level
/// @param lowestLevel bool value of the floorlevel to be made is the lowest level 
/// @return the initiled floor
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

/// @brief initilezes the elevator object and drives the elevator upwards to the first detected floor
/// @return the initilezed elevator
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
    
    return elevator;
}

/// @brief Function that drives the elevator to a ddestination
/// @param elev pointer to a elevator object
/// @param destination destination floor for the elevator
void driveElevator(Elevator *elev, int destination){
    printf("Elevator running, current floor: %d\n", elev -> currentFloor);

    //Code for running elevator upwards
    if(destination > elev -> currentFloor){
        
        updateElevatorDirection(elev, DIRN_UP);
        elevio_motorDirection(DIRN_UP);
        while(elev -> currentFloor != destination){
            updateFloorLight(elev);
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
            updateFloorLight(elev);
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

/// @brief Frees up the memory used by the Elevator object
/// @param elev pointer to elevator object
void freeMemory(Elevator *elev){
    free(elev->floors);
}

/// @brief Updates the floorlights on the controller when the elevator is at a story. Does not update floorlight when elevator is betwhen two stories
/// @param elev pointer to the elevator object 
void updateFloorLight(Elevator *elev){
    int floor = elev -> currentFloor;
    if(floor != -1){
        elevio_floorIndicator(floor);
    }
}

