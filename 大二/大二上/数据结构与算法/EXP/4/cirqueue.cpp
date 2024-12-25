#include <iostream>
using namespace std;

int main(){
    int m,n;
	cin>>m>>n;
    char que[m];
	int front = 0;
	int rear = 0;
    for(int i = 0; i < n; i++){
    	char a[5];
		cin>>a;
    	if (a[0]=='1'){
    		que[rear]=a[2];
    		rear=(rear+1)%m;	//rear++;	
		}
		else {
			front=(front+1)%m;
		}
		cout<<front<<" "<<rear<<endl;
    }
    while (front != rear){
    	printf("%c",que[front]);
    	front=(front+1)%m;
	}
    return 0;
}
