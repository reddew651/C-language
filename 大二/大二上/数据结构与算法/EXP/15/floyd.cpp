#include <iostream>
#include <vector>
using namespace std;

const int maxn = 1000; 
int c[maxn][maxn];
int path[maxn][maxn];
int n;

void Print(int x, int y){
	if(!path[x][y]){
		printf(" %d", y);
		return;
	}
	Print(x, path[x][y]);
	Print(path[x][y],y);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> c[i][j];
            if (c[i][j] == 0 && i != j) {
                c[i][j] = 1e9; 
            }
        }
    }
	for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (c[i][k] != 1e9 && c[k][j] != 1e9 && c[i][k] + c[k][j] < c[i][j]) {
                    c[i][j] = c[i][k] + c[k][j];
                    path[i][j] = k;
            	}
        	}
    	}
    }
    
    for (int i = 1; i < n; i++) {
    	if (c[i][i+1]==1e9){
    		printf("-1\n");
    		continue;
		}
		printf("%d",i);
		Print(i, i+1);
		printf("\n");
    }

    return 0;
}
