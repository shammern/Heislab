#pragma once
#include <stdio.h>

#include "elevio.h"
#include "elevator.h"

/// @brief Linked list to 
typedef struct{
    int floorLevel;
    MotorDirection direction;
    Node* next;
}Node;

typedef struct{
    Node* head;
}Que;//TODO, consider removing

void addToQue(int pushedLevel, MotorDirection dirPushed, int currentLevel, Node** head);
void addLastInQue(Node* new, Node* head);
void insertInMidQue(Node* new, Node* head, MotorDirection motorDir, int destinationLevel);
void removeFromQue(int fremoveLevel, Node** head);//TODO, if head removed, set equal to NULL, beware memory leekage
void clearQue(Node** head); //TODO, set head equal to NULL, beware memory leakage