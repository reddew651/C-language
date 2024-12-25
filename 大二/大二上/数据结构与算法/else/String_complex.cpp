#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};
Node* head = NULL;

void insert(int data) {
    Node* temp = new Node();
    temp->data = data;
    temp->next = head;
    head = temp;
}

void insert_any(int data,int n){
    Node* temp = new Node();
    temp->data = data;
    temp->next = NULL;
    if (n == 1) {
        temp->next = head;
        head = temp;
        return;
    }
    Node* temp1 = head;
    for (int i = 0; i < n - 2; i++) {
        temp1 = temp1->next;
    }
    temp->next = temp1->next;
    temp1->next = temp;
}

void print() {
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void reverse_recrusion(Node* p) {
    if (p == NULL) {
        return;
    }
    reverse_recrusion(p->next);
    printf("%d ", p->data);
}

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
int main(){
    insert(7);
    insert(6);
    insert(4);
    insert(3);
    insert(2);
    insert(1);
    print();
    deleterange(head, 2, 5);
    print();
    return 0;
}