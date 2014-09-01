#include <cstdio>
#include <cstring>
#include <vector>

const int MOD = (int)1e4 + 7;

const int N = 50000;
const int K = 500;

int n, k, parent[N], queue[N], down[N][K + 1], up[N][K + 1], stirling[K + 1][K + 1];
std::vector <int> tree[N];

int add(int a, int b) {
    a += b;
    if (a < 0) {
        a += MOD;
    }
    if (a >= MOD) {
        a -= MOD;
    }
    return a;
}

void update(int* u, int* v, int dir) {
    for (int i = 0; i <= k; ++ i) {
        u[i] = add(u[i], dir * v[i]);
        if (i > 0) {
            u[i] = add(u[i], dir * v[i - 1]);
        }
    }
}

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        scanf("%d%d", &n, &k);
        for (int i = 0; i < n; ++ i) {
            tree[i].clear();
        }
        for (int i = 0; i < n - 1; ++ i) {
            int a, b;
            scanf("%d%d", &a, &b);
            a --, b --;
            tree[a].push_back(b);
            tree[b].push_back(a);
        }
        int tail = 0;
        queue[tail ++] = 0;
        parent[0] = -1;
        for (int head = 0; head < tail; ++ head) {
            int u = queue[head];
            for (int _ = 0; _ < (int)tree[u].size(); ++ _) {
                int v = tree[u][_];
                if (v != parent[u]) {
                    parent[v] = u;
                    queue[tail ++] = v;
                }
            }
        }
        memset(down, 0, sizeof(down));
        for (int i = n - 1; i >= 0; -- i) {
            int u = queue[i];
            down[u][0] = 1;
            for (int _ = 0; _ < (int)tree[u].size(); ++ _) {
                int v = tree[u][_];
                if (v != parent[u]) {
                    update(down[u], down[v], +1);
                }
            }
        }
        memset(up, 0, sizeof(up));
        for (int i = 0; i < n; ++ i) {
            int u = queue[i];
            for (int j = 0; j <= k; ++ j) {
                up[u][j] = add(up[u][j], down[u][j]);
            }
            for (int _ = 0; _ < (int)tree[u].size(); ++ _) {
                int v = tree[u][_];
                if (v != parent[u]) {
                    update(up[u], down[v], -1);
                    update(up[v], up[u], +1);
                    update(up[u], down[v], +1);
                }
            }
        }
        memset(stirling, 0, sizeof(stirling));
        stirling[0][0] = 1;
        for (int i = 1; i <= k; ++ i) {
            for (int j = 1; j <= i; ++ j) {
                stirling[i][j] = (int)((long long)(stirling[i - 1][j] + stirling[i - 1][j - 1]) * j % MOD);
            }
        }
        for (int i = 0; i < n; ++ i) {
            int result = 0;
            for (int j = 0; j <= k; ++ j) {
                result = add(result, (int)((long long)up[i][j] * stirling[k][j] % MOD));
            }
            printf("%d\n", result);
        }
    }
    return 0;
}