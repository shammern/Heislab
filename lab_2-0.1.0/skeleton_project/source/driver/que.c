#include "que.h"

void addToque(int floorLevel, int currentLevel, MotorDirection motorDir, Node** head){//TODO, consider if current Level is global variable
    Node* new = (Node*)malloc(sizeof(Node));
    new->floorLevel = floorLevel;
    int destinationLevel = (*head)->floorLevel;
    if((*head) == NULL 
        || (motorDir == DIRN_DOWN && currentLevel < floorLevel && currentLevel < destinationLevel)
        || (motorDir == DIRN_UP && currentLevel > floorLevel && currentLevel > destinationLevel))
        {
        new->next = (*head);
        (*head) = new;
        return;  
    }

    if(0){//TODO, add if at end
        Node* lastnode = (*head);
        new->next = NULL;
        if(*head == NULL){
            *head = new;
            return;
        }
        while(lastnode->next !=NULL){
            lastnode  = lastnode->next;//TODO,implement  when to add based on floorleveldata
        }
    } 
}