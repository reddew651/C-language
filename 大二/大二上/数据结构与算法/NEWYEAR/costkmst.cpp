#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1000;
const int MAXE = MAXN * MAXN;

struct Edge {
    int u, v, cost;
    Edge() {}
    Edge(int u, int v, int cost) : u(u), v(v), cost(cost) {}
};

int n, k;
int c[MAXN][MAXN];
Edge edges[MAXE];
int edgeCount = 0;
int parent[MAXN];
int treeSize[MAXN];
Edge result[MAXN];
int resultCount = 0;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (treeSize[rootX] > treeSize[rootY]) {
            parent[rootY] = rootX;
            treeSize[rootX] += treeSize[rootY];
        } else {
            parent[rootX] = rootY;
            treeSize[rootY] += treeSize[rootX];
        }
    }
}

bool compareEdges(const Edge &a, const Edge &b) {
    return a.cost < b.cost;
}

// Modified Kruskal's algorithm
bool kruskal() {
    int edgeUsed = 0, totalCost = 0;
    resultCount = 0;

    // Try all possible combinations
    for (int i = 0; i < edgeCount && edgeUsed < n - 1; ++i) {
        Edge &e = edges[i];
        if (find(e.u) != find(e.v)) {
            unite(e.u, e.v);
            totalCost += e.cost;
            result[resultCount++] = e;
            edgeUsed++;
        }
    }

    return (edgeUsed == n - 1 && totalCost == k);
}

bool isConnected() {
    int root = find(1);
    for (int i = 2; i <= n; ++i) {
        if (find(i) != root) return false;
    }
    return true;
}

int main() {
    cin >> n >> k;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> c[i][j];
            if (i < j && c[i][j] > 0) {
                edges[edgeCount++] = Edge(i, j, c[i][j]);
            }
        }
    }

    sort(edges, edges + edgeCount, compareEdges);
    
    bool found = false;
    for (int mask = 0; mask < (1 << edgeCount) && !found; ++mask) {
        // Reset union-find data structures
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
            treeSize[i] = 1;
        }
        
        int totalCost = 0;
        resultCount = 0;
        
        // Try current combination
        for (int i = 0; i < edgeCount; ++i) {
            if (mask & (1 << i)) {
                Edge &e = edges[i];
                if (find(e.u) != find(e.v)) {
                    unite(e.u, e.v);
                    result[resultCount++] = e;
                    totalCost += e.cost;
                }
            }
        }
        
        if (isConnected() && totalCost == k && resultCount == n - 1) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "-1\n";
        return 0;
    }

    int a[MAXN][MAXN];
    memset(a, 0, sizeof(a));
    for (int i = 0; i < resultCount; ++i) {
        Edge &e = result[i];
        a[e.u][e.v] = a[e.v][e.u] = 1;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}