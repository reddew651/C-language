#include <iostream>
#include <stack>
using namespace std;
const int MAX= 100000;

int Ack(int m, int n){
    if (m==0){
        return n+1;
    }
    if (m!=0 && n==0){
        return Ack(m-1, 1);
    }
    else {
        return Ack(m-1, Ack(m,n-1));
    }
}

int No_recursion(int m, int n) {
    stack<int> stack;
    stack.push(m);
    while (!stack.empty()) {
        m = stack.top();
        stack.pop();
        if (m == 0) {
            n = n + 1;
        } else if (m != 0 && n == 0) {
            stack.push(m - 1);
            n = 1;
        } else {
            stack.push(m - 1);
            stack.push(m);
            n = n - 1;
        }
    }
    return n;
}

int main(){
    int x=Ack(2,1);
    int y=No_recursion(2,1);
    printf("%d\n",x);
    printf("%d\n",y);
}