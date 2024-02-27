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

    time_t startCountDoor;
    time_t currentTime;
    int doorBlocksDrive = 0;

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elev = initializeElevator();

    //Made to start timer at change
    int previousFloor = elev.currentFloor;

    while(1){
        //At destination
        if(*ptrToHead != NULL && (*ptrToHead)->floorLevel == elev.currentFloor){
            if(previousFloor != elev.currentFloor){
                time(&startCountDoor); //Restart timer
                elevio_motorDirection(DIRN_STOP);
                removeFromQue(elev.currentFloor);
                for(int b = 0; b < N_BUTTONS; b++){
                    changeButtonandLightStatus(elev.currentFloor, b, 0);
                }  
            }
        }
        //Drives to nest in que if not waiting for the door
        time(&currentTime);
        doorBlocksDrive = currentTime  >= startCountDoor + 3 ? 0 : 1; 
        if(!doorBlocksDrive){
            driveElevator();
        }

        //Checking stop button
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            //Holding until deactivated
            time(&startCountDoor);
            break;
        }

        //Obstruction light
        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
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
    freeMemory(&elev);
    return 0;
}

