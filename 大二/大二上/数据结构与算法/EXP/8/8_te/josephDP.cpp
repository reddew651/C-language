#include<stdio.h>

int n,m;


int getJosephI(int n, int m)
{
	int pos=0;
	for(int i=2;i<=n;i++){
		pos=(pos+m)%i;
	}
	
	return pos+1;
}

int getJosephR(int n, int m)
{
	if(n<=1)
		return n;
		
	int pos=(getJosephR(n-1,m)+m)%n;
	
	return pos==0?n:pos;
}

int main()
{
	scanf("%d%d",&n,&m);
	int pos;
	
//	pos=getJosephI(n,m);
	pos=getJosephR(n,m);
	
	printf("%d",pos);	
	
	return 0; 
}
