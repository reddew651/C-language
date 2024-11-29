//有3个候选人，每个选民只能投票选一人，要求编一个统计选票的程序，
//先后输入被选人的名字，最后输出各人得票结果。
#include <stdio.h>
#include <string.h>
struct Person
{
	char name[10];
	int count;
}leader[3] = { "Li",0,"Zhang",0,"Sun",0 };
int main()
{
	int i, j;
	char lea[20] = { 0 };//define the char
	for (i = 1;i <= 10;i++)//you should put it 10 times
	{
		gets(lea);
		for (j = 0;j < 3;j++)//check set the j as 0, or leader[0] will not be counted
			if (strcmp(lea, leader[j].name) == 0)//if the name right, count the times
				leader[j].count++;//remember to use dot
	}
	printf("\nResult:\n");
	for (i = 0;i < 3;i++)
		printf("%5s:%d\n", leader[i].name, leader[i].count);
	return 0;
}

