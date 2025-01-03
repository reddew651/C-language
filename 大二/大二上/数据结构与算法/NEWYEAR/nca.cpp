#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1000010;
const int MAXM = 5000010; 

int n, m;
int f[MAXN];                  // 节点的父节点
int parent[MAXN];             // 并查集的父节点
bool visited[MAXN];           // 是否访问过
int ancestor[MAXN];           // 当前节点的最近公共祖先
int head[MAXN], nextEdge[MAXN * 2], to[MAXN * 2]; // 树的邻接表
int headQuery[MAXN], nextQuery[MAXM * 2], queryX[MAXM * 2], queryY[MAXM * 2];
int result[MAXM];             // 存储每个查询的答案
int edgeCount = 0, queryCount = 0;

// 初始化
void init() {
    memset(head, -1, sizeof(head));
    memset(headQuery, -1, sizeof(headQuery));
    memset(visited, false, sizeof(visited));
    edgeCount = queryCount = 0;
}

// 添加边到树的邻接表
void addEdge(int u, int v) {
    to[edgeCount] = v;
    nextEdge[edgeCount] = head[u];
    head[u] = edgeCount++;
}

// 添加查询到查询列表
void addQuery(int u, int v, int index) {
    queryX[queryCount] = u;
    queryY[queryCount] = v;
    nextQuery[queryCount] = headQuery[u];
    headQuery[u] = queryCount++;
    queryX[queryCount] = v;
    queryY[queryCount] = u;
    nextQuery[queryCount] = headQuery[v];
    headQuery[v] = queryCount++;
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// Tarjan 算法的 DFS
void tarjanLCA(int u) {
    parent[u] = u;
    ancestor[u] = u;
    visited[u] = true;

    // 遍历树的子节点
    for (int i = head[u]; i != -1; i = nextEdge[i]) {
        int v = to[i];
        if (!visited[v]) {
            tarjanLCA(v);
            parent[v] = u;
        }
    }

    // 处理与当前节点相关的查询
    for (int i = headQuery[u]; i != -1; i = nextQuery[i]) {
        int v = queryY[i];
        if (visited[v]) {
            result[i / 2] = ancestor[find(v)];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    init();

    for (int i = 2; i <= n; ++i) {
        cin >> f[i];
        addEdge(f[i], i);
    }

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        addQuery(x, y, i);
    }

    tarjanLCA(1);

    for (int i = 0; i < m; ++i) {
        cout << result[i] << "\n";
    }

    return 0;
}