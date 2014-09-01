#include <cstdio>
#include <cstring>
#include <algorithm>

int n, m1, m2, maximum[2][501][51];

int main()
{
    int tests = 0;
    while (scanf("%d%d%d", &m1, &m2, &n) == 3 && m1 && m2 && n) {
        memset(maximum, -1, sizeof(maximum));
        maximum[0][0][0] = 0;
        for (int i = 0, t1 = 0, t2 = 0; i < n; ++ i) {
            int price, happiness, special;
            scanf("%d%d%d", &price, &happiness, &special);
            t1 = std::min(t1 + price, m1);
            t2 = std::min(t2 + price, m2);
            for (int free = 1; free >= 0; -- free) {
                for (int v1 = t1; v1 >= 0; -- v1) {
                    for (int v2 = t2; v2 >= 0; -- v2) {
                        int &result = maximum[free][v1][v2];
                        if (special) {
                            result = -1;
                        }
                        if (free && ~maximum[free - 1][v1][v2]) {
                            result = std::max(result, maximum[free - 1][v1][v2] + happiness);
                        }
                        if (v1 >= price && ~maximum[free][v1 - price][v2]) {
                            result = std::max(result, maximum[free][v1 - price][v2] + happiness);
                        }
                        if (v2 >= price && ~maximum[free][v1][v2 - price]) {
                            result = std::max(result, maximum[free][v1][v2 - price] + happiness);
                        }
                    }
                }
            }
        }
        int result = -1;
        for (int free = 1; free >= 0; -- free) {
            for (int v1 = m1; v1 >= 0; -- v1) {
                for (int v2 = m2; v2 >= 0; -- v2) {
                    result = std::max(result, maximum[free][v1][v2]);
                }
            }
        }
        printf("Case %d: %d\n\n", ++ tests, result);
    }
    return 0;
}
