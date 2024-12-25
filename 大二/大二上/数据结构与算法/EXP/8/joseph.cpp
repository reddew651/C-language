#include<stdio.h>
#include <stdlib.h>

int m,n;

typedef struct Node{
	int data;
	struct Node*next;
}person;

person *newnode(int data)   //����ѭ������ 
{
	person *temp=(person*)malloc(sizeof(person));
	temp->next=temp;
	temp->data=data;
	return temp;
}

void getposition(int n,int m)  // �ҵ�ʣ�µ���һ���� 
{
	person *head=newnode(1);
	person *prev=head;
	for(int i=2;i<=n;i++)
	{
		prev->next=newnode(i);
		prev=prev->next;
	}
	prev->next=head;  //����ѭ������ 
	
	person *p1=head,*p2=prev;  
	
	while(p1->next != p1){
		for (int i=1; i<m; i++){
			p2 = p1;
			p1 = p1->next;
		}
		p2->next = p1->next;
		p1 = p1->next;
	   //add main code here
    } 
    printf("%d",p1->data);
}

int main(){
	scanf("%d%d",&n,&m);
	getposition(n,m);
	return 0; 
}
