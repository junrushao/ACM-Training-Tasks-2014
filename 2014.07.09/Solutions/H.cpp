#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

const int V = 800;

int vv, match[V], head, tail, queue[V], predecessor[V], base[V];
bool in_queue[V], in_blossom[V];
std::vector <int> graph[V];

void push(int u)
{
    queue[tail ++] = u;
    in_queue[u] = true;
}

int pop()
{
    return queue[head ++];
}

int start, finish;
bool in_path[V];

int find(int u, int v)
{
    memset(in_path, 0, sizeof(bool) * vv);
    while (true) {
        u = base[u];
        in_path[u] = true;
        if (u == start) {
            break;
        }
        u = predecessor[match[u]];
    }
    while (true) {
        v = base[v];
        if (in_path[v]) {
            break;
        }
        v = predecessor[match[v]];
    }
    return v;
}

int new_base;

void reset(int u)
{
    int v;
    while (base[u] != ::new_base) {
        v = match[u];
        in_blossom[base[u]] = in_blossom[base[v]] = true;
        u = predecessor[v];
        if (base[u] != ::new_base) {
            predecessor[u] = v;
        }
    }
}

void contract(int u, int v)
{
    ::new_base = find(u, v);
    memset(in_blossom, 0, sizeof(bool) * vv);
    reset(u);
    reset(v);
    if (base[u] != ::new_base) {
        predecessor[u] = v;
    }
    if (base[v] != ::new_base) {
        predecessor[v] = u;
    }
    for (int i = 0; i < vv; ++ i) {
        if (in_blossom[base[i]]) {
            base[i] = ::new_base;
            if (!in_queue[i]) {
                push(i);
            }
        }
    }
}

bool augment(int u)
{
    for (int i = 0; i < vv; ++ i) {
        predecessor[i] = -1;
        base[i] = i;
    }
    memset(in_queue, 0, sizeof(bool) * vv);
    start = u;
    finish = -1;
    head = tail = 0;
    push(start);
    while (head < tail) {
        int u = pop();
        for (int i = 0; i < (int)graph[u].size(); ++ i) {
            int v = graph[u][i];
            if (base[u] != base[v] && match[u] != v) {
                if (v == start || ~match[v] && ~predecessor[match[v]]) {
                    contract(u, v);
                } else if (predecessor[v] == -1) {
                    predecessor[v] = u;
                    if (~match[v]) {
                        push(match[v]);
                    } else {
                        finish = v;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool solve()
{
    memset(match, -1, sizeof(match));
    for (int i = 0; i < vv; ++ i) {
        if (match[i] == -1) {
            if (augment(i)) {
                int u = finish;
                while (~u) {
                    int v = predecessor[u];
                    int w = match[v];
                    match[v] = u;
                    match[u] = v;
                    u = w;
                }
            } else {
                return false;
            }
        }
    }
    for (int i = 0; i < vv; ++ i) {
        if (match[i] == -1) {
            return false;
        }
    }
    return true;
}

const int N = 50;
const int M = 200;

int n, m, vs[M << 1], degree[N];

void add_edge(int a, int b)
{
    graph[a].push_back(b);
    graph[b].push_back(a);
    assert(a != b);
}

int main()
{
    int tests;
    scanf("%d", &tests);
    for (int t = 1; t <= tests; ++ t) {
        scanf("%d%d", &n, &m);
        memset(degree, 0, sizeof(degree));
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d", vs + (i << 1), vs + (i << 1 | 1));
        }
        for (int i = 0; i < m << 1; ++ i) {
            degree[-- vs[i]] ++;
        }
        bool valid = true;
        for (int i = 0; i < n; ++ i) {
            int bound;
            scanf("%d", &bound);
            degree[i] -= bound;
            valid &= degree[i] >= 0;
        }
        if (valid) {
            for (int i = 0; i < V; ++ i) {
                graph[i].clear();
            }
            for (int i = 0; i < m; ++ i) {
                add_edge(i << 1, i << 1 | 1);
            }
            vv = m << 1;
            for (int i = 0; i < n; ++ i) {
                for (int j = 0; j < degree[i]; ++ j) {
                    for (int k = 0; k < m << 1; ++ k) {
                        if (vs[k] == i) {
                            add_edge(vv + j, k);
                        }
                    }
                }
                vv += degree[i];
            }
            valid &= solve();
        }
        printf("Case %d: %s\n", t, valid ? "YES" : "NO");
    }
    return 0;
}