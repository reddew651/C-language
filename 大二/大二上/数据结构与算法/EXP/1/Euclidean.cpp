#include <iostream>
using namespace std;
int gcd(int a, int b) {
    return b ==  0?a :gcd (b, a % b);   //fabulous, isn't it?
}
int main(){
    int a,b;
    cin>>a>>b;
    cout<<gcd(a,b)<<endl;
    return 0;
}