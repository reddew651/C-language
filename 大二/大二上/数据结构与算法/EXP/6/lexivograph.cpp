#include <iostream>
using namespace std;

void printLexicographical(int current, int N) {
    if (current > N) return; // Base case: Stop if the number exceeds N
    if (current != 0) cout << current << endl;
    
    for (int i = 0; i <= 9; i++) {
        if (current == 0 && i == 0) continue; // Skip leading zero case
        int next = current * 10 + i;          // Append next digit
        if (next <= N) printLexicographical(next, N); // Recurse if valid
    }
}

int main() {
    int N;
    cout << "Enter N: ";
    cin >> N;

    for (int i = 1; i <= 9; i++) {
        printLexicographical(i, N); // Start from each digit 1 to 9
    }

    return 0;
}