#include "que.h"
#include "globalVariables.h"


int main(){
    Node* head = NULL; // Pointer to Node
    Node* const *ptrToConstHead = &head; // Constant pointer to a pointer to Node
    *ptrToHead = head; // Assign address of head to ptrToHead
    Button button = initializeButton(DIRN_UP);
    int pushed = 3;
    addToQue(pushed, button.type, 1);
    pushed = 2;
    addToQue(pushed, DIRN_DOWN, 1);
    pushed = 2;
    addToQue(pushed, button.type, 1);
    removeFromQue(2);
    return 0;
}


///Tests
/*
void addToQue(int pushedLevel, MotorDirection dirPushed, int currentLevel, Node** head);
void addLastInQue(Node* new, Node* head);
void insertInMidQue(Node* new, Node* head, MotorDirection motorDir, int destinationLevel);
void removeFromQue(int fremoveLevel, Node** head);
void clearQue(Node** head); */