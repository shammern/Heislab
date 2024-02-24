#include "que.h"
#include "globalVariables.h"


/// @brief Helper for addToQue, iterates to last instance in que and adds new input
/// @param  new the new node holding floorLevel and direction of button
/// @param head pointer in linked list to iterate from
void addLastInQue(Node* new, Node* prev){
    Node* iteratorNode = prev;
    new ->next = NULL;
    while(iteratorNode->next !=  NULL){
        iteratorNode = iteratorNode->next;
    }
    iteratorNode->next = new;
}

/// @brief Helper for addToQue, checks if an order can be handled when the elevators takes its first ordered trip 
/// @param  new the new node holding floorLevel and direction of button
/// @param head pointer in linked list to iterate from
/// @param motorDir the direction the elevator was first ordered "main mission"
/// @param destinationLevel the next floor the elevator will stop at
void insertInMidQue(Node* new, MotorDirection motorDir, int destinationLevel){
    Node* iterationNode = *ptrToHead;
    ///beware that next node could be NULL, DO NOT remove while loop!
    Node* nextIt;
    while(iterationNode->next != NULL){
        nextIt = iterationNode->next;
        if(nextIt->direction != motorDir){
            addLastInQue(new, iterationNode);
            return;
        }
        if(motorDir == DIRN_UP ? 
        nextIt->floorLevel > iterationNode->floorLevel 
        : nextIt->floorLevel < iterationNode->floorLevel)
            {
            new->next = nextIt;
            iterationNode->next = new;
            return;
        }
        iterationNode = iterationNode->next;
    }
    //Adding as last if not within the final destinationlevel in same direction
    iterationNode->next = new;
}

/// @brief Function placing new inputs at the correct place in the que to maintain the intenden operation pattern
/// @param pushedLevel Floor where a button were pushed
/// @param dirPushed The direction the button was pushed
/// @param currentLevel The last activated sensor, elevator will be between here and floor given by direction
/// @param head P2p to start of the que
void addToQue(int pushedLevel, MotorDirection dirPushed, int currentLevel){
    //TODO, add functionality for cabinbuttons
    Node* new = (Node*)malloc(sizeof(Node));
    new->floorLevel = pushedLevel;
    new->direction = dirPushed;
    
    if(*ptrToHead == NULL){
        *ptrToHead = new;
        new->next = NULL;
        return;
    }
    
    MotorDirection motorDir = (*ptrToHead)->direction;

    if(motorDir != dirPushed){
        addLastInQue(new, (*ptrToHead));
        return;
    }
    int nextStopLevel = (*ptrToHead)->floorLevel;  //TODO, this might not be as intended, destination floor is now the next stop, not the uppest floor at which to stop
    
    if(motorDir == DIRN_UP && currentLevel < nextStopLevel){
        if(pushedLevel < nextStopLevel){
            new->next = (*ptrToHead);
            (*ptrToHead) = new;
            return;
        }
        insertInMidQue(new, DIRN_UP, nextStopLevel);
        return;
    }

    if(motorDir == DIRN_DOWN && currentLevel > nextStopLevel){
        if(pushedLevel > nextStopLevel){
            new->next = (*ptrToHead);
            (*ptrToHead) = new;
        }
        insertInMidQue(new, DIRN_DOWN, nextStopLevel);
        return;
    }
    addLastInQue(new, (*ptrToHead));
}

/// @brief Function to remove all instances of a given floor level from the que (And frees the memory)
/// @param removeLevel floor level to remove
/// @param head P2p to start of que 
void removeFromQue(int removeLevel){
    Node* iterationNode = (*ptrToHead);
    if(iterationNode->floorLevel == removeLevel){
        (*ptrToHead) = iterationNode->next;
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

/// @brief Deletes all elements in que (And frees memory)
/// @param head p2p start of que
void clearQue(){
    Node* iterationNode = (*ptrToHead);
    (*ptrToHead) = NULL;
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
///Have not considered that the elevator should start by going to the floor at first order