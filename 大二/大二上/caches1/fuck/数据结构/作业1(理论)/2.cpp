#include <iostream>
struct Node{
    int data;
    Node* next;
};


void deleterange(Node *head, int a,int b){
    Node *prev = NULL, *current = head;
    while (current != NULL && current->data <= a){
        prev = current;
        current = current->next;
    }
    while (current != NULL && current->data < b){
        Node *temp= current;
        current = current->next;
        free(temp);
    }
    prev->next = current;
}