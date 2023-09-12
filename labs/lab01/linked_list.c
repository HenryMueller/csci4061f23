#include "linked_list.h"

// Head pointer for the linked list
Node *head = NULL;
Node *tail; // tail will point to the final node before NULL


Node *createNode(int value){
    Node *node =  (Node *)malloc(sizeof(Node));
    node->val = value;
    node->next = NULL;
    return node;
}

void insertLL(int value){
    Node *newNode = createNode(value);
    // Cases to handle:
    // Empty linked list
    if (head == NULL){
        newNode->next = head;
        head = newNode;
        tail = newNode;
        return;
    }
    // value < head->val
    if (value < head->val){
        newNode->next = head;
        head = newNode;
        return;
    }
    // value > last node in linked list
    if (value > tail->val){
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
        return;
    }
    // insert value within linked list
    Node *nextNode = head;
    Node *prevNode;
    while (newNode->val > nextNode->val)
    {
        prevNode = nextNode;
        nextNode = nextNode->next;
    }
    prevNode->next = newNode;
    newNode->next = nextNode;
    return;
}

void freeLL(){
    Node *nextNode = NULL;
    while(head){
        nextNode = head -> next;
        free(head);
        head = nextNode;
    }
    head = NULL;
}

void displayLL(){
    Node *trav = head;
    while(trav){
        printf("%d ", trav->val);
        trav = trav->next;
    }
    printf("\n");
}