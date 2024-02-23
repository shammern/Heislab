#include "que.h"

int main(){
    Node* head = NULL;
    Button button = initializeButton(DIRN_UP);
    int pushed = 3;
    addToQue(pushed, button.type, 1, &(head));
    
    return 0;
}