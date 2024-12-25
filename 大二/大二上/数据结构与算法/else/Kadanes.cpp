#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int max_sum = 0, current_sum = 0;
    for (int i = 0; i < n; i++){
        current_sum = max(a[i], current_sum + a[i]);    //check if the a[i] is good for the current sum or not, if so, add it to the current sum
        max_sum = max(max_sum, current_sum);
    }
    cout << max_sum << endl;
}