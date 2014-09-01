#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>

const int N = 100;
const int M = 8;

int n, m, a[N], visited[M], minimum[2][N + 1][(1 << M) + 1][M + 1];

inline void update(int &x, int a)
{
    if (x == -1 || a < x) {
        x = a;
    }
}

int main()
{
    int tests = 0;
    while (scanf("%d%d", &n, &m) == 2 && n && m) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d", a + i);
            a[i] -= 25;
        }
        memset(visited, 0, sizeof(visited));
        for (int used = 0; used <= m; ++ used) {
            for (int mask = 0; mask < 1 << M; ++ mask) {
                for (int last = 0; last <= M; ++ last) {
                    minimum[0][used][mask][last] = !mask && last == M ? 0 : -1;
                }
            }
        }
        for (int i = 0; i < n; ++ i) {
            int i_p = i & 1;
            int i_n = i + 1 & 1;
            for (int used = 0; used <= m; ++ used) {
                for (int mask = 0; mask < 1 << M; ++ mask) {
                    for (int last = 0; last <= M; ++ last) {
                        minimum[i_n][used][mask][last] = -1;
                    }
                }
            }

            for (int mask = 0; mask < 1 << M; ++ mask) {
                for (int last = 0; last <= M; ++ last) {
                    if (last < M && mask >> last & 1) {
                        continue;
                    }
                    for (int used = std::min(i, m); used >= 0; -- used) {
                        int value = minimum[i_p][used][mask][last];
                        if (~value) {
                            update(minimum[i_n][used][mask & ~(1 << a[i])][a[i]], value + (a[i] != last));
                            if (used + 1 <= m) {
                                if (visited[a[i]] && (~mask >> a[i] & 1)) {
                                    update(minimum[i_n][used + 1][mask][last], value);
                                }
                                update(minimum[i_n][used + 1][mask | (1 << a[i])][last], value);
                            }
                        }
                    }
                }
            }
            visited[a[i]] = true;
        }
        int result = -1;
        for (int used = 0; used <= m; ++ used) {
            for (int mask = 0; mask < 1 << M; ++ mask) {
                for (int last = 0; last <= M; ++ last) {
                    int value = minimum[n & 1][used][mask][last];
                    if (~value) {
                        update(result, value + __builtin_popcount(mask));
                    }
                }
            }
        }
        printf("Case %d: %d\n\n", ++ tests, result);
    }
    return 0;
}
