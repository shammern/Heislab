#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/elevator.h"
#include "driver/globalVariables.h"
#include "driver/utilities.h"
//#include "driver/elevio.con"



int main(){
    elevio_init();

    //Made to start timer
    time_t startCountDoor;
    time_t currentTime;
    time(&startCountDoor);
    int doorBlocksDrive = 0;

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    Elevator elev = initializeElevator();

    int prevFloor = elev.currentFloor;
    Node** test = ptrToHead;


    while(1){
        //At destination
        if(*ptrToHead != NULL && (*ptrToHead)->floorLevel == elev.currentFloor){
            if(prevFloor != elev.currentFloor){
                time(&startCountDoor);
                elevio_motorDirection(DIRN_STOP);
                removeFromQue(elev.currentFloor);
                for(int b = 0; b < N_BUTTONS; b++){
                    changeButtonandLightStatus(elev.currentFloor, b, 0, &elev);
                }  
            }
        }

        //Drives to nest in que if not waiting for the door
        if(time(&currentTime) >= startCountDoor + 3){ 
            if(*ptrToHead != NULL && elev.currentFloor == (*ptrToHead)->floorLevel){
                removeFromQue(elev.currentFloor);
            }
            driveElevator(&elev);
        }
        
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                if(btnPressed){
                    MotorDirection dir = buttonTypeToDir(b, f, &elev);
                    changeButtonandLightStatus(f, b, 1, &elev);
                    addToQue(f,dir,elev.currentFloor);
                }
            }
        }

        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            time(&startCountDoor);
        }

        //Obstruction light
        if(elevio_obstruction()){
            elevio_stopLamp(1);
            time(&startCountDoor); //Is this according to spec? now it is waiting three seconds after obstruction
        } else {
            elevio_stopLamp(0);
        }

        updateCurrentFloor(&elev);
        elevio_floorIndicator(elev.currentFloor);
    }
    



    /*
    while(1){
        int floor = elevio_floorSensor();

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }
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
        if(floor == N_FLOORS-1){
    time_t startCountDoor;
    time_t currentTime;
    int doorBlocksDrive = 0;

            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed); //TODO, implement hold on light after button released
            }
        }

        
        //Checking all buttons, 
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                if(btnPressed){
                    changeButtonandLightStatus(f, b, 1);
                    MotorDirection dir = buttonTypeToDir(b);
                    addToQue(f,dir,elev.currentFloor);
                }
            }
        }
        previousFloor = elev.currentFloor;
        updateCurrentFloor(); 
    }
    /*
    while(1){
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
    */

    
    //freeMemory(&elev);
    return 0;
}

