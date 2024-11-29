//建立一个简单链表，它由3个学生数据的结点组成，要求输出各结点中的数据。
#include "stdio.h"
struct student//define the struct function
{
	int num;
	float score;
	struct student* next;//student* next is a pointer to point the next student
};
int main()
{
	struct student a, b, c, * head, * p;//set the variable 
	a.num = 10101;
	a.score = 89.5;
	b.num = 10103;
	b.score = 90.0;
	c.num = 10107;
	c.score = 85.0;
	head = &a;//here, head is the address of a 
	a.next = &b;//a.next is the address of the b
	b.next = &c;
	c.next = NULL;
	p = head;
	do
	{
		printf("%d  %.1f\n", p->num, p->score);
		p = p->next;//set the p to the next struct
	} while (p != NULL);
	return 0;
}