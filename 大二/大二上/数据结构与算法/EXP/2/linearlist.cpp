#include <stdio.h>
#include <stdlib.h>

int m;  //命令数 

struct node{
    int data;
    struct node* next;
};

node *head=NULL; // head指向头节点 


void inserthead(int data){
    node* temp = new node();    //创建新节点
    temp->data = data;
    temp->next = head;
    head = temp;
}
void inserttail(int data){
    node* temp = new node();
    temp->data = data;
    temp->next = NULL;
    node* p = head;
    while (p->next != NULL){
        p = p->next;
    }
    p->next= temp;
}

void insert(int i, int x) { // 插入x到a[i] ,
    node *p = head;
    for (int k = 0; k < i-1 && p != NULL; k++) { // 找到i的位置
        p = p->next;
    }
    if (p == NULL) return; // 如果i超出范围
    node *newNode = new node(); // 创建新节点
    newNode->data = x;
    newNode->next = p->next;
    p->next = newNode;
} 


void deleteByIndex(int i) { // 删除a[i] 
    node *p = head;
    for (int k = 0; k < i && p->next != NULL; k++) { // 找到i-1的位置
        p = p->next;
    }
    if (p->next == NULL) return; // 如果i超出范围
    node *temp = p->next;
    p->next = p->next->next; // 删除节点,通过跳过实现，p->next指向下下个节点
    free(temp);  // 释放p->next
} 

void find(int x) { // 查找第一个x
    node *p = head->next;
    int i = 0;
    while (p != NULL) {
        if (p->data == x) {
            printf("%d\n", i); // 找到并输出位置
            return;
        }
        p = p->next;
        i++;
    }
    printf("-1\n"); // 未找到
}

void eliminateRepeat() { // 去除重复元素 
    node *p = head->next;
    while (p != NULL) {
        node *q = p;
        while (q->next != NULL) {
            if (q->next->data == p->data) {
                node *temp = q->next;
                q->next = q->next->next; // 跳过重复元素
                free(temp);
            } else {
                q = q->next;
            }
        }
        p = p->next;
    }
}

void count(int x, int y) { // 统计[x,y]中元素个数
    int k = 0;
    node *p = head->next; 
    while (p != NULL) {
        if (p->data >= x && p->data <= y) k++; // 统计符合条件的元素
        p = p->next;
    }
    printf("%d\n", k);
}

void deleteByRange(int x, int y) { // 去除[x,y]范围内的元素 
    node *p = head;
    while (p->next != NULL) {
        if (p->next->data >= x && p->next->data <= y) {
            node *temp = p->next;
            p->next = p->next->next; // 跳过范围内的元素
            free(temp);
        } else {
            p = p->next;
        }
    }
} 
void print(){
    node* p = head;
    while (p->next != NULL){
        printf("%d ", p->next->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    scanf("%d", &m); // 读取命令数
    head = new node(); // 创建头节点
    head->next = NULL;
    
    for (int k = 0; k < m; k++) {
        int c, i, x, y;
        scanf("%d", &c); // 读取命令类型
        switch (c) {
            case 1: scanf("%d%d", &i, &x); insert(i, x); break; // 插入操作
            case 2: scanf("%d", &i); deleteByIndex(i); break; // 删除操作
            case 3: scanf("%d", &x); find(x); break; // 查找操作
            case 4: scanf("%d%d", &x, &y); count(x, y); break; // 统计范围内元素个数
            case 5: eliminateRepeat(); break; // 去重操作
            case 6: scanf("%d%d", &x, &y); deleteByRange(x, y); break; // 删除范围内元素
            case 7: print(); break; // 输出操作
        }
    }
    
    return 0;
}