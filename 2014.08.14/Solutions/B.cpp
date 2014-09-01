#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1005 << 1;

int n, k;
char s[N];

int lcp[N][N];

int cmp(int l0, int r0, int l1, int r1) {
    int len = min(min(r0 - l0 + 1, r1 - l1 + 1), lcp[l0][l1]);
    char c0 = l0 + len <= r0 ? s[l0 + len] : '\0',
         c1 = l1 + len <= r1 ? s[l1 + len] : '\0';
    if (c0 == c1) {
        return 0;
    } else if (c0 < c1) {
        return -1;
    } else {
        return 1;
    }
}

bool cmp2(const pair<int, int> &a, const pair<int, int> &b) {
    return cmp(a.first, a.second, b.first, b.second) == -1;
}

int jump[N], ord[N];

bool check(pair<int, int> str) {
    for (int i = 0; i < n; ++i) {
        int l = min(lcp[i][str.first], str.second - str.first + 1);
        if (cmp2(make_pair(i, i + l), str)) {
            jump[i] = n;
        } else {
            jump[i] = l;
        }
    }
    for (int i = 0; i < n; ++i) {
        jump[i + n] = jump[i];
    }
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        int cnt = 0, last = i, maxJump = i + jump[i];
        while (cnt <= k) {
            if (last >= i + n) {
                ++ret;
                break;
            }
            if (last == maxJump) {
                break;
            }
            ++cnt;
            int oldMax = maxJump;
            for (int i = last + 1; i <= oldMax && i < 2 * n; ++i) {
                maxJump = max(maxJump, i + jump[i]);
            }
            last = oldMax;
        }
    }
    return ret >= k;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        scanf("%s", s);
        for (int i = 0; i < n; ++i) {
            s[i + n] = s[i];
        }
        for (int i = 0; i <= n * 2; ++i) {
            lcp[i][n * 2] = lcp[n * 2][i] = 0;
        }
        for (int i = n * 2 - 1; i >= 0; --i) {
            for (int j = n * 2 - 1; j >= 0; --j) {
                if (s[i] == s[j]) {
                    lcp[i][j] = lcp[i + 1][j + 1] + 1;
                } else {
                    lcp[i][j] = 0;
                }
                lcp[i][j] = min(n, lcp[i][j]);
            }
        }
        vector<pair<int, int> > str;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                str.push_back(make_pair(i, i + j));
            } 
        }
        sort(str.begin(), str.end(), cmp2);
        int l = 0, r = (int)str.size() - 1;
        while (l < r) {
            int m = l + r >> 1;
            if (check(str[m])) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        s[str[l].second + 1] = '\0';
        puts(s + str[l].first);
    }
    return 0;
}
