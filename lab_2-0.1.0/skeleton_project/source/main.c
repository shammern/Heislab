#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "driver/elevio.h"
#include "elevator.h"
#include "globalVariables.h"
#include "utilities.h"
#include "que.h"




int main(){
    elevio_init();

    //Made to start timer
    time_t startCountDoor;
    time_t currentTime;
    time_t stopButtonTime;
    time(&startCountDoor);
    
    //State variables
    int stoppedAtFloor = 1;
    int prevStopped = 1;
    int numberPushedOnFloor = 0;

    MotorDirection prevDirection = DIRN_STOP;

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    Elevator elev = initializeElevator();

    Node** test = ptrToHead;


    while(1){
        //At destination
        if(*ptrToHead != NULL && elevio_floorSensor() == (*ptrToHead)->floorLevel && !stoppedAtFloor){
            
            stoppedAtFloor = 1;
            prevStopped = 1;
            numberPushedOnFloor = 0;
            time(&startCountDoor);
            elevio_doorOpenLamp(1);
            elevio_motorDirection(DIRN_STOP);
            updateCurrentFloor(&elev);
            for(int b = 0; b < N_BUTTONS; b++){
                changeButtonandLightStatus(elev.currentFloor, b, 0, &elev);
                elevio_buttonLamp(elev.currentFloor, b, 0);
            }
        }

        //Drives to nest in que if not waiting for the door
        if(time(&currentTime) >= startCountDoor + 3){
            if(prevStopped){
                driveElevator(&elev, &prevDirection, &prevStopped);
            }
            elevio_doorOpenLamp(0);

            //Removing from que and turning off buttonlights at departure
            if(stoppedAtFloor){
                removeFromQue(elev.currentFloor);
                stoppedAtFloor = 0;
                for(int b = 0; b < N_BUTTONS; b++){
                    elevio_buttonLamp(elev.currentFloor, b, 0);
                }
            }
        }
        
        ///Checking all buttons
        controllingAllButtonsExecuteActive(&elev,stoppedAtFloor, &numberPushedOnFloor);

        //At stop-button pressed
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            prevStopped = 1;
            elevio_stopLamp(1);
            if((*ptrToHead) != NULL){
                prevDirection = (*ptrToHead)->direction;
            }
            
            if(elevio_floorSensor() != -1){
                elevio_doorOpenLamp(1);
            }
            time(&stopButtonTime);
            time(&startCountDoor);
            clearQue();

            for(int f = 0; f < N_FLOORS; f++){
                for(int b = 0; b < N_BUTTONS; b++){
                    changeButtonandLightStatus(f, b, 0, &elev);        
                }
            }
        }
        //Resettingg stoplight
        if(time(&currentTime) >= stopButtonTime + 0.000001){
            elevio_stopLamp(0);            
        }

        //Obstruction leads to doortimer reset 
        if(elevio_obstruction()){
            time(&startCountDoor); 
        }

        //Updating the floor at valid sensor input
        updateCurrentFloor(&elev);
        elevio_floorIndicator(elev.currentFloor);
    }
}

