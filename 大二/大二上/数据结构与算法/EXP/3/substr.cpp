#include <iostream>
using namespace std;
int main(){
    string s;
    cin>>s;
    int start, len;
    cin>>start>>len;
    cout<<s.substr(start, len);
    cout<<endl;
    cout<<s.length();
}