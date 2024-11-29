//有3个学生的信息，放在结构体数组中，要求输出全部学生的信息。(利用指向结构体数组的指针)
#include "stdio.h"
struct student //define the struct
{
	int num;
	char name[20];
	char sex;
	int age;
};
struct student stu[3] = { {10101,"Li Lin",'M',18},{10102,"Zhang Fang",'M',19},{10104,"Wang Min",'F',20} };
int main()
{
	struct student* p;//define the pointer
	for (p = stu;p < stu + 3;p++)//set the recruit,printf the struct
		printf("%5d %-20s %2c %4d\n", p->num, p->name, p->sex, p->age);
	return 0;
}