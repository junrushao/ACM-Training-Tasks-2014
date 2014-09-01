#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int K = 1111111;

int n, m, k, x[K], y[K], r[K], c[K], next[K], result[K], sqrtResult[K];

long long square(long long x) {
    return x * x;
}

long long squareRoot(long long x) {
    long long r = max((int)sqrt((double)x) - 5, 0);
    while (square(r + 1) <= x) {
        r ++;
    }
    return r;
}

int find(int i) {
    if (next[i] != i) {
        next[i] = find(next[i]);
    }
    return next[i];
}

void cover(int a, int b, int c) {
    for (int i = find(a); i <= b; i = find(i)) {
        result[i] = c;
        next[i] = i + 1;
    }
}

int main() {
    for (int i = 0; i <= 50000; ++ i) {
        sqrtResult[i] = squareRoot(i);
    }
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < k; ++ i) {
        scanf("%d%d%d%d", x + i, y + i, r + i, c + i);
    }
    for (int j = 0; j < m; ++ j) {
        for (int i = 0; i <= n; ++ i) {
            next[i] = i;
            result[i] = 0;
        }
        for (int i = k - 1; i >= 0; -- i) {
            if (abs(j - y[i]) <= r[i]) {
                int d = sqrtResult[square(r[i]) - square(j - y[i])];
                cover(max(x[i] - d, 0), min(x[i] + d, m - 1), c[i]);
            }
        }
        for (int i = 0; i < n; ++ i) {
            printf("%d", result[i]);
        }
        puts("");
    }
    return 0;
}

