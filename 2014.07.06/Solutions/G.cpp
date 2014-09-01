#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int COL = 100000;
const int N = 333;
int n, ca, cb, a[N][N], b[N][N], sumcol[COL + 10], ans;
vector<int> e[2 * COL + 10];

void update(int &a, int b) {
    a = min(a, b);
}

bool check1()
{
    static int s1[N], s2[N];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            s1[j] = a[i][j];
            s2[j] = b[i][j];
        }
        sort(s1 + 1, s1 + n + 1);
        sort(s2 + 1, s2 + n + 1);
        for (int j = 1; j <= n; j++)
            if (s1[j] != s2[j])
                return 0;
    }
    return 1;
}

vector<pair<int, int> > source[COL + 10], target[COL + 10];
int visit[N][N];
int DFN[COL * 2 + 10], low[COL * 2 + 10], stk[COL * 2 + 10], inStk[COL * 2 + 10], color[COL * 2 + 10], top, tot, totColor;
vector<pair<int, int> > mat[N][N];

void tarjan(int x) {
    DFN[x] = low[x] = ++tot;
    stk[++top] = x;
    inStk[x] = 1;
    for(int i = 0; i < (int)e[x].size(); i++) {
        int y = e[x][i];
        if (!DFN[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (inStk[y]) {
            low[x] = min(low[x], DFN[y]);
        }
    }
    if (DFN[x] == low[x]) {
        ++totColor;
        while(stk[top] != x) {
            color[stk[top]] = totColor;
            inStk[stk[top]] = 0;
            top--;
        }
        color[x] = totColor;
        inStk[x] = 0;
        top--;
    }
}

int getID(pair<int, int> c) {
    return c.first + c.second * COL;
}

bool check2() {
    for(int i = 1; i <= 2 * COL; i++) {
        e[i].clear();
    }
    for(int i = 1; i <= COL; i++) {
        source[i].clear();
        target[i].clear();
    }
    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= n; j++) {
            source[a[i][j]].push_back(make_pair(i, j));
            target[b[i][j]].push_back(make_pair(i, j));
            visit[i][j] = 0;
            mat[i][j].clear();
        }
    for(int i = 1; i <= COL; i++) {
        if ((int)source[i].size() == 0)
            continue;
        if ((int)source[i].size() == 1) {
            visit[source[i][0].first][target[i][0].second]++;
        } else {
            if (source[i][0].first == source[i][1].first) {
                if (target[i][0].second == target[i][1].second)
                    return false;
                visit[source[i][0].first][target[i][0].second]++;
                visit[source[i][0].first][target[i][1].second]++;
            } else if (target[i][0].second == target[i][1].second) {
                visit[source[i][0].first][target[i][0].second]++;
                visit[source[i][1].first][target[i][0].second]++;
            } else {
                mat[source[i][0].first][target[i][0].second].push_back(make_pair(i, 0));
                mat[source[i][1].first][target[i][1].second].push_back(make_pair(i, 0));
                mat[source[i][0].first][target[i][1].second].push_back(make_pair(i, 1));
                mat[source[i][1].first][target[i][0].second].push_back(make_pair(i, 1));
            }
        }
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++) {
            if (visit[i][j] > 1)
                return false;
            if (visit[i][j] == 1) {
                for(int k = 0; k < (int)mat[i][j].size(); k++) {
                    pair<int, int> item = mat[i][j][k];
                    e[getID(item)].push_back(getID(make_pair(item.first, item.second ^ 1)));
                }
            } else {
                for(int k = 0; k < (int)mat[i][j].size(); k++)
                    for(int l = 0; l < (int)mat[i][j].size(); l++) {
                        if (k == l)
                            continue;
                        pair<int, int> item1 = mat[i][j][k], item2 = mat[i][j][l];
                        e[getID(item1)].push_back(getID(make_pair(item2.first, item2.second ^ 1)));
                    }
            }
        }
    top = 0;
    tot = 0;
    totColor = 0;
    for(int i = 1; i <= COL * 2; i++) {
        inStk[i] = 0;
        DFN[i] = low[i] = 0;
    }
    for(int i = 1; i <= COL * 2; i++) {
        if (!DFN[i])
            tarjan(i);
    }
    for(int i = 1; i <= COL; i++)
        if (color[i] == color[i + COL])
            return false;
    return true;
}

int main()
{
    int test;
    scanf("%d", &test);
    for (int tt = 1; tt <= test; tt++) {
        scanf("%d%d%d", &n, &ca, &cb);
        fill(sumcol + 1, sumcol + COL + 1, 0);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                scanf("%d", &a[i][j]);
                sumcol[a[i][j]]++;
            }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                scanf("%d", &b[i][j]);
                sumcol[b[i][j]]--;
            }
        printf("Case #%d: ", tt);
        bool eq = true;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if (a[i][j] != b[i][j])
                    eq = false;
        if (eq) {
            printf("0\n");
            continue;
        }
        bool noans = 0;
        for (int i = 1; i <= COL; i++) {
            if(sumcol[i] != 0) {
                noans = 1;
                break;
            }
        }
        if (noans) {
            printf("Take off the shoes!\n");
            continue;
        }
        ans = min(ca + ca + cb, cb + cb + ca);
        for(int times = 0; times < 2; times++) {
            if (check1())
                update(ans, ca);
            if (check2())
                update(ans, ca + cb);
            for (int i = 1; i <= n; i++)
                for (int j = i; j <= n; j++) {
                    swap(a[i][j], a[j][i]);
                    swap(b[i][j], b[j][i]);
                }
            swap(ca, cb);
        }
        printf("%d\n", ans);
    }
    return 0;
}
