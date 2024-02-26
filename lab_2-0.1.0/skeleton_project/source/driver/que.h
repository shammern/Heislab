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
    Node* next;
};

void addToQue(int pushedLevel, MotorDirection dirPushed, int currentLevel);
void addLastInQue(Node* new, Node* prev);
void insertInMidQue(Node* new, MotorDirection motorDir);
void removeFromQue(int removeLevel);
void clearQue(); 
