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
        //fill this part. 
    }
}

int count(BiTree T){
    if(T == NULL) return 0;
    //fill this part. 
}

int main(){
    //fill this part. 
    printf("%d", count(T));
    return 0;
}
