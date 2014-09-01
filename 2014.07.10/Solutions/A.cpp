#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>

const int N = 50;

const int V = 300000;
const int E = 2000000;

int edge_count, head[V], to[E], capacity[E], next[E];

void __add_edge(int u, int v, int w)
{
    to[edge_count] = v;
    capacity[edge_count] = w;
    next[edge_count] = head[u];
    head[u] = edge_count ++;
}

void _add_edge(int a, int b, int c)
{
    __add_edge(a, b, c);
    __add_edge(b, a, 0);
}

void add_edge(int t, int a, int b, int c)
{
    if (t) {
        std::swap(a, b);
    }
    _add_edge(a, b, c);
}

int n, m, l, cost[2][N][N], vertices[2][6][6][N][N];

int my_log(int n)
{
    int k = 0;
    while (1 << k + 1 <= n) {
        k ++;
    }
    return k;
}

int current[V], level[V], queue[V];

bool bfs(int source, int target)
{
    int tail = 0;
    queue[tail ++] = source;
    memset(level, -1, sizeof(level));
    level[source] = 0;
    for (int k = 0; k < tail; ++ k) {
        int u = queue[k];
        for (int it = head[u]; ~it; it = next[it]) {
            if (capacity[it]) {
                int v = to[it];
                if (level[v] == -1) {
                    level[v] = level[u] + 1;
                    queue[tail ++] = v;
                }
            }
        }
    }
    return level[target] != -1;
}

int dfs(int u, int target, int left)
{
    if (u == target) {
        return left;
    }
    int delta = 0;
    for (int &it = current[u]; ~it; it = next[it]) {
        if (capacity[it]) {
            int v = to[it];
            if (level[u] + 1 == level[v]) {
                int r = dfs(v, target, std::min(capacity[it], left - delta));
                delta += r;
                capacity[it] -= r;
                capacity[it ^ 1] += r;
                if (delta == left) {
                    return delta;
                }
            }
        }
    }
    level[u] = -1;
    return delta;
}

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        scanf("%d%d%d", &n, &m, &l);
        int result = 0;
        for (int _ = 0; _ < 2; ++ _) {
            for (int i = 0; i < n; ++ i) {
                for (int j = 0; j < m; ++ j) {
                    scanf("%d", &cost[_][i][j]);
                    result += cost[_][i][j];
                }
            }
        }
        edge_count = 0;
        memset(head, -1, sizeof(head));
        int node_count = n * m;
        int source = node_count ++;
        int target = node_count ++;
        for (int _ = 0; _ < 2; ++ _) {
            for (int i = 0; i < n; ++ i) {
                for (int j = 0; j < m; ++ j) {
                    vertices[_][0][0][i][j] = i * m + j;
                }
            }
            for (int k = 0; k < 6; ++ k) {
                for (int kk = 0; kk < 6; ++ kk) {
                    int length = 1 << k - 1;
                    int llength = 1 << kk - 1;
                    if (k) {
                        for (int i = 0; i + length + length <= n; ++ i) {
                            for (int j = 0; j + llength + llength <= m; ++ j) {
                                add_edge(_, node_count, vertices[_][k - 1][kk][i][j], INT_MAX);
                                add_edge(_, node_count, vertices[_][k - 1][kk][i + length][j], INT_MAX);
                                vertices[_][k][kk][i][j] = node_count ++;
                            }
                        }
                    } else if (kk) {
                        for (int i = 0; i + length + length <= n; ++ i) {
                            for (int j = 0; j + llength + llength <= m; ++ j) {
                                add_edge(_, node_count, vertices[_][k][kk - 1][i][j], INT_MAX);
                                add_edge(_, node_count, vertices[_][k][kk - 1][i][j + llength], INT_MAX);
                                vertices[_][k][kk][i][j] = node_count ++;
                            }
                        }
                    }
                }
            }
        }
        while (l --) {
            int x1, y1, x2, y2, type, cost;
            scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &type, &cost);
            x1 --, y1 --, x2 --, y2 --;
            type ^= 1;
            int kx = my_log(x2 - x1 + 1);
            int ky = my_log(y2 - y1 + 1);
            add_edge(type, node_count, vertices[type][kx][ky][x1][y1], INT_MAX);
            add_edge(type, node_count, vertices[type][kx][ky][x2 - (1 << kx) + 1][y1], INT_MAX);
            add_edge(type, node_count, vertices[type][kx][ky][x1][y1 - (1 << ky) + 1], INT_MAX);
            add_edge(type, node_count, vertices[type][kx][ky][x2 - (1 << kx) + 1][y1 - (1 << ky) + 1], INT_MAX);
            add_edge(type, type ? target : source, node_count ++, cost);
            result += cost;
        }
        for (int _ = 0; _ < 2; ++ _) {
            for (int i = 0; i < n; ++ i) {
                for (int j = 0; j < m; ++ j) {
                    add_edge(_, _ ? target : source, vertices[_][0][0][i][j], cost[_][i][j]);
                }
            }
        }
        while (bfs(source, target)) {
            for (int i = 0; i < node_count; ++ i) {
                current[i] = head[i];
            }
            result -= dfs(source, target, INT_MAX);
        }
        printf("%d\n", result);
    }
    return 0;
}