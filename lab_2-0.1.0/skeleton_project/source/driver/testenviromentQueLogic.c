#include "que.h"
#include "globalVariables.h"

int main(){
    int pushed = 4;
    addToQue(pushed, DIRN_UP, 1);
    pushed = 2;
    Node** watch = ptrToHead;
    addToQue(pushed, DIRN_DOWN, 1);
    pushed = 2;
    addToQue(pushed, DIRN_UP, 1);
    pushed = 3;
    addToQue(pushed, DIRN_UP, 1);
    clearQue();
    addToQue(pushed, DIRN_UP, 1);
    watch = ptrToHead;
    return 0;
}


///Tests
/*
void addToQue(int pushedLevel, MotorDirection dirPushed, int currentLevel, Node** head);
    OK add first
    OK void addLastInQue(Node* new, Node* head);
    OK void insertInMidQue(Node* new, Node* head, MotorDirection motorDir, int destinationLevel);
OK void removeFromQue(int fremoveLevel, Node** head);
OK void clearQue(Node** head); */