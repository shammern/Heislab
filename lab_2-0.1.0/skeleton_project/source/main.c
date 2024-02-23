#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/elevator.h"
//#include "driver/elevio.con"



int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    printf("Running function initializeElevator()\n");
    Elevator elev = initializeElevator();
    

    printf("Running function driveElevator()\n");
    driveElevator(&elev, 0);
    driveElevator(&elev, 3);
    driveElevator(&elev, 0);

    
    freeMemory(&elev);
    return 0;
}
