#include "que.h"
#include "globalVariables.h"

void settingGlobals(){
    Node* head = NULL; // Pointer to Node
    *ptrToHead = head; // Assign address of head to ptrToHead
}

int main(){
    settingGlobals();
    Button button = initializeButton(DIRN_UP);
    int pushed = 3;
    addToQue(pushed, button.type, 1);
    pushed = 2;
    
    addToQue(pushed, DIRN_DOWN, 1);
    pushed = 2;
    Node** watch = ptrToHead;
    addToQue(pushed, button.type, 1);
    //removeFromQue(2);
    
    
    return 0;
}


///Tests
/*
void addToQue(int pushedLevel, MotorDirection dirPushed, int currentLevel, Node** head);
void addLastInQue(Node* new, Node* head);
void insertInMidQue(Node* new, Node* head, MotorDirection motorDir, int destinationLevel);
void removeFromQue(int fremoveLevel, Node** head);
void clearQue(Node** head); */