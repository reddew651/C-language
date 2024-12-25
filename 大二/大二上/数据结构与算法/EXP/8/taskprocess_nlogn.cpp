#include <iostream>
using namespace std;

int main(){
  int n,a[100],t,s=1;
  cin >> n;
  for (int i=1;i<=n;i++){
    cin >> t;
    if (i==1) a[1]=t;
    if(t>a[s]) a[++s] = t;
    else{
      int head =1, tail=s,middle;
      while (head<tail){
        middle=(head+tail)/2;
        if(t>a[middle]) head=middle+1;
        else tail=middle-1;
      }
      a[head]=t;
    }
  }
  cout << s;
}