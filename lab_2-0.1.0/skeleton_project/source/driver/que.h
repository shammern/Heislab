#pragma once
#include <stdio.h>

#include "elevio.h"

/// @brief Linked list to 
typedef struct{
    int floorLevel;
    Node* next;
}Node;

typedef struct{
    Node* head;
}Que;//TODO, consider removing

void addToQue(int floorLevel, Node* head);
void removeFromQue(int floor);//TODO, if head removed, set equal to NULL, beware memory leekage
void clearQue(); //TODO, set head equal to NULL, beware memory leakage