#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 7, M = 60, L = 7;

int n, m, l;
int p[3][L];

long long cb(int n, int k) {
    long long ret = 1;
    for (int i = 0; i < k; ++i) {
        ret = ret * (n - i) / (i + 1);
    }
    return ret;
}

long long mat;

int rnk[L];

bool match() {
    int ori[3], need[3 * L];
    for (ori[0] = 0; ori[0] < l; ++ori[0]) {
        for (ori[1] = 0; ori[1] < l; ++ori[1]) {
            for (ori[2] = 0; ori[2] < l; ++ori[2]) {
                memset(need, 0, sizeof(need));
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < l; ++j) {
                        need[rnk[ori[i]] + j] += p[i][j];
                    }
                }
                for (int i = 0; i < l; ++i) {
                    --need[rnk[i]];
                }
                bool flag = true;
                for (int i = 0; i < 3 * L && flag; ++i) {
                    if (need[i] > 0) {
                        flag = false;
                    }
                } 
                if (flag) {
                    return true;
                }
            }
        }
    }
    return false;
}

long long count() {
    long long ret = 1;
    int empty = m - 1 - rnk[l - 1], block = 2;
    for (int i = 0; i + 1 < l; ++i) {
        if (rnk[i + 1] - rnk[i] > 1) {
            ++block;
        }
    }
    ret = ret * cb(empty + block - 1, block - 1);
    for (int i = 0; i < l; ++i) {
        int j = i;
        while (j < l && rnk[j] == rnk[i]) {
            ++j;
        }
        ret = ret * cb(n, j - i);
        i = j - 1;
    }
    return ret;
}

void go(int i) {
    if (rnk[i - 1] >= m) {
        return;
    }
    if (i == l) {
        if (match()) {
            mat += count();
        }
        return;
    }
    for (int delta = 0; delta < 3; ++delta) {
        rnk[i] = rnk[i - 1] + delta;
        go(i + 1);
    }
}

int main() {
    while (scanf("%d%d%d", &n, &m, &l) == 3 && (n * m)) {
        memset(p, 0, sizeof(p));
        {
            char buf[10];
            for (int i = 0; i < l; ++i) {
                scanf("%s", buf);
                if (buf[0] == '*') {
                    continue;
                }
                ++p[buf[0] - 'a'][strlen(buf) - 1];
            }
        }
        mat = 0;
        rnk[0] = 0;
        go(1);
        printf("%.12f\n", (double)((long double)mat / cb(n * m, l)));
    }
    return 0;
}
