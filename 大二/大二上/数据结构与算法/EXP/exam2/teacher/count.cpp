#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void CreateBiTree(BiTree &T){
    char ch;
    scanf("%c", &ch);
    if('#' == ch) T = NULL;
    else{
        if(!(T = (BiTNode *)malloc(sizeof(BiTNode)))) exit(-1);
        T->data = ch;             //Create the root node
        CreateBiTree(T->lchild);  //Create left subtree
        CreateBiTree(T->rchild);  //Create left subtree
    }
}

int count(BiTree T){
    if(T == NULL) return 0;
    int c = 0;
    if (T->lchild != NULL && T->rchild == NULL || 
	    T->lchild == NULL && T->rchild != NULL) c++;
    return (c + count(T->lchild) + count(T->rchild));
}

int main(){
    BiTree T;
    CreateBiTree(T);
    printf("%d", count(T));
    return 0;
}
