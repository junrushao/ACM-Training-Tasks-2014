#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <utility>
#include <bitset>
#include <complex>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <cctype>
using namespace std;

const int MO = 100000;

int ways[2][17][17][17][17][5], cnt, last;
int X1[211], Y1[211], X2[211], Y2[211];
int g[20][20][20][20][4];
bool vis[20][20][20][20];
int N, M;

inline bool checkmax(int &a, int b) {
    if (b > a) {
        a = b;
        return 1;
    }
    return 0;
}

inline void addto(int &a, int b) {
    a += b; if (a >= MO) a -= MO;
}

void dfs(int a, int b, int c, int d) {
    if (vis[a][b][c][d]) return;
    int *ret = g[a][b][c][d];
    vis[a][b][c][d] = true;
    if (a == N && b == N && c == N && d == N) {
        for (int i = 0; i < 4; ++i) ret[i] = N;
        return;
    }
    int cnt[4] = {a, b, c, d};
    for (int i = 0; i < M; ++i) {
        if (Y1[i] < cnt[X1[i]] && Y2[i] >= cnt[X2[i]]) {
            int tmp = cnt[X2[i]];
            cnt[X2[i]] = Y2[i] + 1;
            dfs(cnt[0], cnt[1], cnt[2], cnt[3]);
            for (int j = 0; j < 4; ++j) ret[j] = g[cnt[0]][cnt[1]][cnt[2]][cnt[3]][j];
            cnt[X2[i]] = tmp;
            return;
        }
    }
    for (int i = 0; i < 4; ++i) ret[i] = cnt[i];
}

void main2() {
    scanf("%d%d", &N, &M);
    memset(g, -1, sizeof g);
    for (int i = 0; i < M; ++i) {
        scanf("%d%d%d%d", &X1[i], &Y1[i], &X2[i], &Y2[i]);
        X1[i]--;
        Y1[i]--;
        X2[i]--;
        Y2[i]--;
        X2[i + M] = X1[i]; Y2[i + M] = Y1[i]; X1[i + M] = X2[i]; Y1[i + M] = Y2[i];
    }
    M *= 2;
    memset(vis, 0, sizeof vis);
    memset(ways, 0, sizeof ways);
    cnt = 0; 
    last = 1;
    ways[cnt][0][0][0][0][0] = 1;
    for (int i = 0; i < 256; ++i) {
        cnt ^= 1;
        last ^= 1;
        memset(ways[cnt], 0, sizeof ways[cnt]);
        for (int a = 0; a <= N; ++a) {
            for (int b = 0; b <= N; ++b) {
                for (int c = 0; c <= N; ++c) {
                    for (int d = 0; d <= N; ++d) {
                        for (int bef = 0; bef <= 4; ++bef) if (ways[last][a][b][c][d][bef]) {
                            int &m = ways[last][a][b][c][d][bef];
                            if (bef == 4) {
                                addto(ways[cnt][a][b][c][d][0], m);
                                continue;
                            }
                            int co[4] = {a, b, c, d};
                            addto(ways[last][a][b][c][d][bef + 1], m);
                            int j = bef;
                            if (co[j] < N) {
                                co[j]++;
                                dfs(co[0], co[1], co[2], co[3]);
                                int *next = g[co[0]][co[1]][co[2]][co[3]];
                                bool good = true;
                                for (int k = 0; k < j && good; ++k) if (next[k] > co[k]) good = false;
                                if (good) {
                                    //cout << next[0] << " " << next[1] << " " << next[2] << " " << next[3] << " " << bef << endl;
                                    addto(ways[last][next[0]][next[1]][next[2]][next[3]][bef], m);
                                }
                                co[j]--;
                            }
                        }
                    }
                }
            }
        }
    }
    //cout << ways[last][1][1][0][0][0] << endl;
    printf("%05d\n", ways[cnt][N][N][N][N][0]);
}

int main() {
    //freopen("B.in", "r", stdin);
    int T, caseId = 1;
    for (scanf("%d", &T); T--; ) {
        printf("Case %d: ", caseId++);
        main2();
    }
    return 0;
}