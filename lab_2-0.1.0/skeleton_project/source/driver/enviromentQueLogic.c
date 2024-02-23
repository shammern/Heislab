#include "que.h"

static const Node** head;

int main(){
    Button button = initializeButton(DIRN_UP);
    int pushed = 3;
    addToQue(pushed, button.type, 1, head);
    pushed = 2;
    addToQue(pushed, DIRN_DOWN, 1,&(head));
    pushed = 2;
    addToQue(pushed, button.type, 1,&(head));
    removeFromQue(2, &(head));
    return 0;
}


///Tests
/*
void addToQue(int pushedLevel, MotorDirection dirPushed, int currentLevel, Node** head);
void addLastInQue(Node* new, Node* head);
void insertInMidQue(Node* new, Node* head, MotorDirection motorDir, int destinationLevel);
void removeFromQue(int fremoveLevel, Node** head);
void clearQue(Node** head); */