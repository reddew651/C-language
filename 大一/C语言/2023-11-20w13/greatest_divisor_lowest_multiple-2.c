//求两个整数的最大公约数和最小公倍数

#include  "stdio.h"
int main() 
{
	int hcf(int,int);
	int lcd(int,int,int);
	int u,v,h,l;
	scanf("%d %d",&u,&v);
	h=hcf(u,v);
	printf("hcf=%d\n",h);
	l=lcd(u,v,h);
	printf("lcd=%d",l);
	return 0;
}
int hcf(int u,int v)
{
	int t,r;
	if (v>u)
	{
		t=u;
		u=v;
		v=t;
	}
	while ((r=u%v)!=0) //i think this the best way writng Euclidean algorithm
	{
		u=v;
		v=r;
	}
	return(v);
}
int lcd(int u,int v,int h) {
	return(u*v/h);
}