#include <iostream>
#include <vector>   // 引入vector头文件，使用动态数组

using namespace std;

void selectsort(vector<int>& arr) { //vector<int>& arr是引用传递，可以直接修改arr的值,不需要返回值，其中&表示引用
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minindex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minindex]) {
                minindex = j;
            }
        }
        swap(arr[i], arr[minindex]);
    }
}

int main() {
    int n;
    cin >> n;  // 读取数组大小
    vector<int> arr(n); // 定义大小为n的数组,vector是动态数组
    for (int i = 0; i < n; i++) {
        cin >> arr[i];  // 读取数组元素
    }

    selectsort(arr);  // 调用选择排序函数

    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) {
            cout << " ";  // 输出空格分隔的元素
        }
    }
    cout << endl;  // 输出换行符

    return 0;
}