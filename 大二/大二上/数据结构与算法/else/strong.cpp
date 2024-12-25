#include <iostream>
using namespace std;
int main(){
    int a[8] = {6,5,8,7,2,1,4,3};
    int num = 0;
    for (int i = 0; i < 8;i++){
        for (int j = i+1; j < 8;j++){
            if (a[i] > a[j]){
                num++;
            }
        }
    }
    cout << num << endl;
}