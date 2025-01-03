#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1000;  // 最大节点数
const int MAXE = MAXN * MAXN;  // 最大边数（完全图）

struct Edge {
    int u, v, cost;

    // 添加构造函数，兼容旧版本 C++
    Edge() {}
    Edge(int u, int v, int cost) : u(u), v(v), cost(cost) {}
};

int n, k;
int c[MAXN][MAXN];  // 邻接矩阵存储图
Edge edges[MAXE];   // 静态数组存储所有边
int edgeCount = 0;  // 边的数量
int parent[MAXN];   // 并查集父节点
int treeSize[MAXN]; // 并查集子树大小
Edge result[MAXN];  // 静态数组存储结果边集
int resultCount = 0;

// 并查集查找
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// 并查集合并
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

// 比较函数，用于排序
bool compareEdges(const Edge &a, const Edge &b) {
    return a.cost < b.cost;
}

// Kruskal算法构造生成树
bool kruskal() {
    int edgeUsed = 0, totalCost = 0;

    for (int i = 0; i < edgeCount; ++i) {
        Edge &e = edges[i];
        if (find(e.u) != find(e.v)) {
            unite(e.u, e.v);
            totalCost += e.cost;
            result[resultCount++] = e;
            edgeUsed++;
            // 如果已经找到了 n-1 条边，生成树构建完成
            if (edgeUsed == n - 1) break;
        }
    }

    // 如果边数满足，输出生成树，不再检查 totalCost == k
    if (edgeUsed == n - 1) {
        return true; // 表示生成树已构建完成
    }

    return false; // 无法构建一个包含 n-1 条边的生成树
}

int main() {
    cin >> n >> k;

    // 读取图的邻接矩阵
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> c[i][j];
            if (i < j && c[i][j] > 0) { // 存储边信息
                edges[edgeCount++] = Edge(i, j, c[i][j]); // 使用构造函数代替列表初始化
            }
        }
    }

    // 按边的费用排序
    sort(edges, edges + edgeCount, compareEdges); // 使用比较函数代替 lambda

    // 初始化并查集
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
        treeSize[i] = 1;
    }

    // 尝试构造生成树
    if (kruskal()) {
        // 输出邻接矩阵结果
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
    
    } else {
        cout << -1 << "\n";
    }

    return 0;
}