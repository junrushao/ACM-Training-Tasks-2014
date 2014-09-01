#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <utility>
#include <vector>

#define ALL(v) (v).begin(), (v).end()
#define time TIME

const int N = 500;

int n, m, target, length[N], time[N], need[N], by[N];
std::vector <int> inputs[N], outputs[N], included[N], children[N + 1];
char buffer[N];

std::priority_queue <std::pair <int, int> > queue;

void clear(int v)
{
    for (int i = 0; i < (int)included[v].size(); ++ i) {
        int p = included[v][i];
        if (!-- need[p]) {
            int finish = time[v] + length[p];
            queue.push(std::make_pair(-finish, p));
        }
    }
}

void dfs(int u)
{
    putchar('(');
    if (u < n) {
        printf("P%d", u + 1);
    }
    for (int i = 0; i < (int)children[u].size(); ++ i) {
        int v = children[u][i];
        if (i > 0) {
            putchar('|');
        }
        dfs(v);
    }
    putchar(')');
}

int main()
{
    int tests = 0;
    while (scanf("%d%d%d", &n, &m, &target) == 3 && n && m && target) {
        target --;
        scanf("%s", buffer);
        for (int i = 0; i < m; ++ i) {
            included[i].clear();
        }
        for (int i = 0; i < n; ++ i) {
            scanf("%d", length + i);
            int k;
            inputs[i].clear();
            scanf("%d", &k);
            for (int j = 0; j < k; ++ j) {
                int x;
                scanf("%d", &x);
                x --;
                inputs[i].push_back(x);
            }
            std::sort(ALL(inputs[i]));
            inputs[i].erase(std::unique(ALL(inputs[i])), inputs[i].end());
            need[i] = inputs[i].size();
            for (int j = 0; j < need[i]; ++ j) {
                included[inputs[i][j]].push_back(i);
            }
            outputs[i].clear();
            scanf("%d", &k);
            for (int j = 0; j < k; ++ j) {
                int x;
                scanf("%d", &x);
                x --;
                outputs[i].push_back(x);
            }
        }
        memset(time, -1, sizeof(time));
        memset(by, -1, sizeof(by));
        for (int i = 0; i < m; ++ i) {
            if (buffer[i] == '1') {
                by[i] = n;
                time[i] = 0;
                clear(i);
            }
        }
        while (!queue.empty()) {
            int t = -queue.top().first;
            int p = queue.top().second;
            queue.pop();
            for (int i = 0; i < (int)outputs[p].size(); ++ i) {
                int o = outputs[p][i];
                if (time[o] == -1) {
                    by[o] = p;
                    time[o] = t;
                    clear(o);
                }
            }
        }
        for (int i = 0; i < m; ++ i) {
            if (time[i] == -1) {
                time[i] = INT_MAX;
            }
        }
        printf("Case %d: ", ++ tests);
        if (time[target] == INT_MAX) {
            puts("-1");
        } else {
            printf("%d ", time[target]);
            for (int i = 0; i <= n; ++ i) {
                children[i].clear();
            }
            for (int i = 0; i < n; ++ i) {
                int last = -1;
                for (int j = 0; j < (int)inputs[i].size(); ++ j) {
                    int v = inputs[i][j];
                    if (last == -1 || time[v] > time[last]) {
                        last = v;
                    }
                }
                if (time[last] != INT_MAX) {
                    children[by[last]].push_back(i);
                }
            }
            dfs(n);
            puts("");
        }
        puts("");
    }
    return 0;
}
