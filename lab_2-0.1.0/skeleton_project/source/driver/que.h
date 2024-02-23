#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "elevio.h"
#include "elevator.h"

typedef struct Node Node;

/// @brief Nodes of a Linked List taking care of execution order
struct Node{
    int floorLevel;
    MotorDirection direction;
    struct Node* next;
};


typedef struct{
    Node* head;
}Que;//TODO, consider removing, replace by a single global variable, are not supposed to have multiplisity

void addToQue(int pushedLevel, MotorDirection dirPushed, int currentLevel, Node** head);
void addLastInQue(Node* new, Node* head);
void insertInMidQue(Node* new, Node* head, MotorDirection motorDir, int destinationLevel);
void removeFromQue(int fremoveLevel, Node** head);
void clearQue(Node** head); 

static const Node* head;