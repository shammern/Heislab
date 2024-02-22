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
    ///beware that next node could be NULL, keep while loop
    while(iterationNode->next != NULL){
        Node* next = iterationNode->next; 
        if(next->direction != motorDir){
            addLastInQue(new, iterationNode);
            return;
        }
        if(motorDir == DIRN_UP ? 
        next->floorLevel < destinationLevel 
        : next->floorLevel > destinationLevel)
            {
            new->next = next;
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
        insertInMiddle(new, head, DIRN_UP);
        return;
    }

    if(insertDown){
        if(pushedLevel > destinationLevel){
            new->next = (*head);
            (*head) = new;
        }
        insertInMiddle(new, head, DIRN_DOWN);
        return;
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

