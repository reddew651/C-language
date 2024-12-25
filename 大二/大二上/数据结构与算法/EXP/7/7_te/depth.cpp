#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef int TElemType;

#define OK           1
#define OVERFLOW    -2

typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree, *SElemType;

typedef struct SNode {
    SElemType data;
    struct SNode *next;
}SNode;



Status CreateBiTree(BiTree &T)
{
    char ch;
    scanf("%c", &ch);

    if('#' == ch) T = NULL;
    else{
        if(!(T = (BiTNode *)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
        T->data = ch;             //Create the root node
        CreateBiTree(T->lchild);  //Create left subtree
        CreateBiTree(T->rchild);  //Create left subtree
    }
    return OK;
}


int DeepTree(BiTree T)
{
    if(T == NULL)
        return 0;

    int ldeep, rdeep, deep = 0;
    ldeep = DeepTree(T->lchild);
    rdeep = DeepTree(T->rchild);
    deep = (ldeep > rdeep ? ldeep : rdeep);

    return (deep + 1);

}

//int DeepTree(BiTree T);

int main()
{
    BiTree T;
    CreateBiTree(T);
    printf("%d", DeepTree(T));
    return 0;
}
