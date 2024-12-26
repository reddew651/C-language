//数组行列转换
//写一个函数，使给定的一个3*3的二维整型数组转置，即行列互换。
//在main函数中：给定下列数组，调用自定义函数，并在main函数中输出转换后的二维数组。
#include <stdio.h>
int main()
{
	//First declare the function
	void convert(int a[][3]);
	//Then declare the array and initialize it
	int a[3][3] = { 1,2,3,3,4,5,4,5,6 },i,j;
	convert(a); //call the function
	//Then print out the array
	for (i = 0;i < 3;i++)
	{
		for (j = 0;j < 3;j++)
		{
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	return 0;
}

//Then define the function
void convert(int a[][3])
{
	int i, j, t;
	for (i = 0;i < 3;i++)
	{
		for (j = i;j < 3;j++)//here you should if j=0,the char a will be converted twice time ,so the result never change ,use j=i
		{
			t = a[i][j]; //Exchange the value
			a[i][j] = a[j][i];
			a[j][i] = t;
		}
	}
}