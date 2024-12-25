#include <iostream>
using namespace std;

// Function to move n disks from source to destination using auxiliary
void hanoi(int n, char source, char auxiliary, char destination) {
    // Base case: if only 1 disk, move it directly
    if (n == 1) {
        cout << "Move disk 1 from " << source << " to " << destination << endl;
        return;
    }
    
    // Step 1: Move n-1 disks from source to auxiliary using destination as auxiliary
    hanoi(n - 1, source, destination, auxiliary);
    
    // Step 2: Move the nth disk from source to destination
    cout << "Move disk " << n << " from " << source << " to " << destination << endl;
    
    // Step 3: Move the n-1 disks from auxiliary to destination using source as auxiliary
    hanoi(n - 1, auxiliary, source, destination);
}

int main() {
    int n;  // Number of disks
    cout << "Enter the number of disks: ";
    cin >> n;
    
    // Call the function to solve the Tower of Hanoi problem
    hanoi(n, 'A', 'B', 'C');  // A = source, B = auxiliary, C = destination
    
    return 0;
}