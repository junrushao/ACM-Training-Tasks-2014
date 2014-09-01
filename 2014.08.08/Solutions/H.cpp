#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 205, INF = 1000000000;
int n, m;

int g[N][N];

vector<int> edge[N];

int used[N];

pair<int, int> ori[N];

int tmp[N];

int f[N][N][N], best[N][N], size[N];

void go(int u, int fa) {
    for (int i = 0; i < (int)edge[u].size(); ++i) {
        int v = edge[u][i];
        if (v == fa) {
            continue;
        }
        go(v, u);
    }
    for (int k = 0; k < n; ++k) {
        if (used[k]) {
            continue;
        }

        size[u] = 1;
        f[u][0][k] = f[u][1][k] = INF;
        if (make_pair(g[u][k], k) < ori[u]) {
            f[u][1][k] = 1;
        } else {
            f[u][0][k] = 1;
        }
        for (int _ = 0; _ < (int)edge[u].size(); ++_) {
            int v = edge[u][_];
            if (v == fa) {
                continue;
            }

            for (int j = 0; j <= size[u]; ++j) {
                tmp[j] = f[u][j][k];
            }
            
            for (int j = 0; j <= size[u] + size[v]; ++j) {
                f[u][j][k] = INF;
            }

            for (int j = 0; j <= size[u]; ++j) {
                for (int l = 0; l <= size[v]; ++l) {
                    f[u][j + l][k] = min(f[u][j + l][k], min(tmp[j] + f[v][l][k] - 1, tmp[j] + best[v][l]));
                }
            }
            size[u] += size[v];
        }
    } 
    for (int j = 0; j <= size[u]; ++j) {
        best[u][j] = INF;
        for (int k = 0; k < n; ++k) {
            if (!used[k]) {
                best[u][j] = min(best[u][j], f[u][j][k]);
            }
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                g[i][j] = INF;
            }
            g[i][i] = 0;
        }
        for (int i = 0; i < n; ++i) {
            edge[i].clear();
        }
        for (int i = 0; i < n - 1; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            --u, --v;
            g[u][v] = g[v][u] = w;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            scanf("%d", used + i);
        }        
        for (int i = 0; i < n; ++i) {
            ori[i] = make_pair(INF, INF);
            for (int j = 0; j < n; ++j) {
                if (used[j]) {
                    ori[i] = min(ori[i], make_pair(g[i][j], j));
                }
            }
        }
        go(0, -1);
        int ans = 0;
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (!used[k] && f[0][j][k] <= m) {
                    ans = max(ans, j);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
