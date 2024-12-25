#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef int TElemType;

#define TRUE         1
#define FALSE        0
#define OK           1
#define ERROR        0
#define OVERFLOW    -2

typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree, *SElemType;

typedef struct SNode {
    SElemType data;
    struct SNode *next;
}SNode;

typedef struct LinkStack {
    SNode *base;
    SNode *top;
}LinkStack;


Status InitStack(LinkStack &S) {
    S.top = S.base = NULL;
    return OK;
}

Status GetTop(LinkStack &S, SElemType &e)
{
    if (S.top == NULL) return ERROR;
    else e = S.top->data;
    return OK;
}

Status Push(LinkStack &S, SElemType e) {
    SNode *p = (SNode *)malloc(sizeof(SNode));
    if (!p) exit(OVERFLOW);
    p->data = e;
    p->next = S.top;
    S.top = p;
    return OK;
}

Status Pop(LinkStack &S, SElemType &e) {
    if (S.top == S.base)
        return ERROR;
    SNode *p = S.top;
    S.top = S.top->next;
    e = p->data;
    free(p);
    return OK;
}

Status StackEmpty(LinkStack S)
{
    if (S.base == S.top) return TRUE;
    else return FALSE;
}


Status Visit(TElemType e);
Status InOrderTraverse(BiTree T, Status (*Visit)(TElemType));

Status InitStack(LinkStack &S);
Status StackEmpty(LinkStack S);
Status GetTop(LinkStack &S, SElemType &e);
Status Push(LinkStack &S, SElemType e);
Status Pop(LinkStack &S, SElemType &e);

Status Visit(TElemType e)
{
    printf("%c", e);
    return OK;
}

Status InOrderTraverse(BiTree T, Status (*Visit)(TElemType e))
{
    LinkStack S;  BiTNode *p = NULL;
    InitStack(S); p = T;
    while (p || !StackEmpty(S))
    {
        if (p)
        {
            Push(S, p);
            p = p->lchild; } 
        else
        {
            Pop(S, p);
            if (!Visit(p->data))
                return ERROR;
            p = p->rchild;
        }
    }
    return OK;
}

Status CreateBiTree(BiTree &T)
{
    char ch;
    scanf("%c", &ch);

    if('#' == ch) T = NULL;
    else{
        if(!(T = (BiTNode *)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
        T->data = ch;             
        CreateBiTree(T->lchild);  
        CreateBiTree(T->rchild);  
    }
    return OK;
}

int main()
{
    BiTree T;
    CreateBiTree(T);

    //printf("\nIn Order Traverse: ");
    InOrderTraverse(T, Visit);

    return 0;
}



