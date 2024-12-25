#include <iostream>
#include <stdio.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


long long int m[401][401];//mΪ�洢���Ž���Ķ�ά����,�൱�ڱ���¼��m[i][j]�������i����j������˵���С����ֵ
int p[401];
void MatrixChainOrder(int *p,int n)
{
    int l,i,j,k;
    long long int q = 0;
    for (int l=2;l<=n;l++){
    	for (int i=0;i<n-l+1;i++){
    		int j=i+l-1;
    		m[i][j]=99999999;
    		for (int k=i; k<j; k++){
    			int cost = m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j+1];
    			if (cost<m[i][j]){
    				m[i][j]=cost;
				}
			}
		}
	}
    //please finishi this part



    printf("%lld",m[0][n-1]);
}

int main()
{
	int n,i;
	scanf("%d", &n); //��n������

	for (i=0; i<=n; i++){
		scanf("%d",&p[i]);
	}
    MatrixChainOrder(p,n);   //please finishi this part
    return 0;
}
