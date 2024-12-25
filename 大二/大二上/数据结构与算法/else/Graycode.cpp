#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
// 使用公式生成 Gray Code
vector<int> generateGrayCodeFormula(int n) {
    vector<int> grayCode;
    int numCodes = 1 << n; // 2^n 个 Gray Code
    printf("%d", numCodes);
    for (int i = 0; i < numCodes; ++i) {
        grayCode.push_back(i ^ (i >> 1));
    }

    return grayCode;
}

int main() {
    int n = 3; // 生成 3 位 Gray Code
    vector<int> grayCode = generateGrayCodeFormula(n);
    for (int code : grayCode) {
        cout << bitset<3>(code) << endl;
    }

    return 0;
}