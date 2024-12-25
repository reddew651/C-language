#include <iostream>
using namespace std;
int isprime(int n){
    if (n==1) return 0;
    for (int i=2;i*i<=n;i++){
        if (n%i==0) return 0;
    }
    return 1;
}
int main(){
    int n;
    cin>>n;
    int k=n+1;
    while (isprime(k)==0) k++;
    cout<<k<<endl;
}