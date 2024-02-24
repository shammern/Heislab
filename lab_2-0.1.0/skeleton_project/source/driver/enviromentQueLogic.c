#include "que.h"
#include "globalVariables.h"

void settingGlobals(){
    Node* head = NULL; // Pointer to Node
    *ptrToHead = head; // Assign address of head to ptrToHead
}

int main(){
    settingGlobals();
    int pushed = 4;
    addToQue(pushed, DIRN_UP, 1);
    pushed = 2;
    Node** watch = ptrToHead;
    addToQue(pushed, DIRN_DOWN, 1);
    pushed = 2;
    addToQue(pushed, DIRN_UP, 1);
    pushed = 3;
    addToQue(pushed, DIRN_UP, 1);
    //removeFromQue(2);
    watch = ptrToHead;
    return 0;
}


///Tests
/*
void addToQue(int pushedLevel, MotorDirection dirPushed, int currentLevel, Node** head);
    OK add first
    OK void addLastInQue(Node* new, Node* head);
    OK void insertInMidQue(Node* new, Node* head, MotorDirection motorDir, int destinationLevel);
void removeFromQue(int fremoveLevel, Node** head);
void clearQue(Node** head); */