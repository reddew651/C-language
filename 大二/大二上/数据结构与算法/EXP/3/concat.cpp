#include <iostream>
using namespace std;
// Function to concatenate two strings
int main(){
    string s1, s2;  //string is a class in C++ STL
    int len1, len2;
    cin>>s1>>s2;
    for (len1 = 0; s1[len1] != '\0'; len1++);
    for (len2 = 0; s2[len2] != '\0'; len2++);
    string s;
    for (int i = 0; i < len2; i++) {
        s1[len1 + i] = s2[i];
    }
    cout<<len1+len2<<endl;
    cout<<s1+s2;
}