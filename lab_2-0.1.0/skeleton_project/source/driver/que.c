#include "que.h"

void addLastInQue(Node* new, Node* head){
    Node* iteratorNode = head;
    while(iteratorNode->next !=  NULL){
        iteratorNode = iteratorNode->next;
    }
    iteratorNode->next = new;
}

void insertInMidQue(Node* new, Node* head, MotorDirection motorDir, int destinationLevel){
    Node* iterationNode = head;
    ///beware that next node could be NULL, DO NOT remove while loop!
    Node* nextIt;
    while(iterationNode->next != NULL){
        nextIt = iterationNode->next;
        if(nextIt->direction != motorDir){
            addLastInQue(new, iterationNode);
            return;
        }
        if(motorDir == DIRN_UP ? 
        nextIt->floorLevel < destinationLevel 
        : nextIt->floorLevel > destinationLevel)
            {
            new->next = nextIt;
            iterationNode->next = new;
            return;
        }
        iterationNode = iterationNode->next;
    }
    //Adding as last if not 
    iterationNode->next = new;
}

void addToQue(int pushedLevel, MotorDirection dirPushed, int currentLevel, Node** head){
    //TODO, consider if current Level is global variable
    Node* new = (Node*)malloc(sizeof(Node));
    new->floorLevel = pushedLevel;
    new->direction = dirPushed;

    int destinationLevel = (*head)->floorLevel;
    MotorDirection motorDir = (*head)->direction;

    int insertUp = (motorDir == DIRN_DOWN && currentLevel < destinationLevel) ? 1:0;
    int insertDown = (motorDir == DIRN_UP && currentLevel > destinationLevel) ? 1:0;

    if(!insertUp && !insertDown){
        addLastInQue(new, (*head));
        return;
    }

    if(insertUp){
        if(pushedLevel < destinationLevel){
            new->next = (*head);
            (*head) = new;
            return;
        }
        insertInMidQue(new, head, DIRN_UP, destinationLevel);
        return;
    }

    if(insertDown){
        if(pushedLevel > destinationLevel){
            new->next = (*head);
            (*head) = new;
        }
        insertInMiddle(new, head, DIRN_DOWN, destinationLevel);
        return;
    }
}

void removeFromQue(int removeLevel, Node** head){
    Node* iterationNode = (*head);
    if(iterationNode->floorLevel == removeLevel){
        (*head) = iterationNode->next;
        free(iterationNode);
    }

    Node* nextIt;
    while(iterationNode->next != NULL){
        nextIt = iterationNode->next; 
        if(nextIt->floorLevel == removeLevel){
            iterationNode->next = nextIt->next; //nextIt->next could be zero, but that is a non-issue
            free(nextIt);
        }      
    }
}

void clearQue(Node** head){
    Node* iterationNode = (*head);
    (*head) = NULL;
    Node* nextIt;
    while(iterationNode != NULL){
        nextIt =  iterationNode->next;
        free(iterationNode);
        iterationNode = nextIt;
    }
}

///Logic used in derivation of code:
///If greater than destination => Last node
///If opposite direction => Last node
///If between current and destination + direction aligns,first node
///What if original goal is 4, 2 hits button, before 3 hits button => second node?
    ///If direction aligns, and  is correct compared to current
        ///If correct side of head node=> first break/return
        ///while next direction align
            ///If correct side of head node => insert

///Using this insert could lead to multiple instances of same floor,should not be a problem as long as both are removed at deletion

