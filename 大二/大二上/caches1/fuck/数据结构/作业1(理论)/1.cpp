#include <stdio.h>
#include <string.h>

const int max = 10000;
char S[] = "abaabaabab";
int pi[max];

void failure_function() {
    int lens = strlen(S);
    pi[0] = 0;  
    int k = 0;
    for (int i = 1; i < lens; i++) {    
        while (k > 0 && S[k] != S[i]) {     
            k = pi[k - 1];  
        }
        if (S[k] == S[i]) { 
            k++;    
        }
        pi[i] = k;  
    }
}

int main() {
    failure_function();
    int lens = strlen(S);
    for (int i = 0; i < lens; i++) {
        printf("%d ", pi[i]);
    }
    printf("\n");
    return 0;
}