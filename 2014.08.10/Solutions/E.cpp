#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200005;
int n; 
long long val[N];

vector<int> edge[N];

map<long long, long long> tr[N];

const long long INF = 1ll << 60;

bool mergy(pair<long long, long long> p, pair<long long, long long> q) {
    return p.second >= q.first;
}

pair<long long, long long> merge(pair<long long, long long> p, pair<long long, long long> q) {
    pair<long long, long long> ret;
    ret.first = p.first + max(0ll, q.first - p.second);
    ret.second = p.second - q.first + q.second + (ret.first - p.first);
    return ret;
}

void addFront(int u, long long val) {
    if (val > 0) {
        tr[u][0] += val;
    } else if (tr[u].size() > 0 && val < 0) {
        pair<long long, long long> p = *tr[u].begin();
        p.first += -val;
        tr[u].erase(tr[u].begin());
        while (true) {
            if (tr[u].size() == 0 || tr[u].begin()->first > p.first && p.second > p.first) {
                if (p.first < p.second) {
                    tr[u][p.first] = p.second;
                }
                break;
            } else {
                pair<long long, long long> q = *tr[u].begin();
                tr[u].erase(tr[u].begin());
                p = merge(p, q);
            }
        }
    }
    while (tr[u].size() > 1) {
        map<long long, long long>::iterator it = tr[u].begin();
        pair<long long, long long> p = *it, q = *(++it);
        if (mergy(p, q)) {
            tr[u].erase(tr[u].begin());
            tr[u].erase(tr[u].begin());
            p = merge(p, q);
            tr[u][p.first] = p.second;
        } else {
            break;
        }
    }
}

void insert(int u, pair<long long, long long> val) {
    while (true) {
        map<long long, long long>::iterator it = tr[u].upper_bound(val.first);
        if (it == tr[u].begin()) {
            break;
        }
        --it;
        if (!mergy(*it, val)) {
            break;
        }
        pair<long long, long long> p = *it;
        tr[u].erase(it);
        val = merge(p, val);
    }
    while (true) {
        map<long long, long long>::iterator it = tr[u].upper_bound(val.first);
        if (it == tr[u].end()) {
            break;
        }
        if (!mergy(val, *it)) {
            break;
        }
        pair<long long, long long> p = *it;
        tr[u].erase(it);
        val = merge(val, p);
    }
    tr[u][val.first] = val.second;
}

void merge(int ch, int fa) {
    if (tr[ch].size() > tr[fa].size()) {
        swap(tr[ch], tr[fa]);
    }
    for (map<long long, long long>::iterator it = tr[ch].begin(); it != tr[ch].end(); ++it) {
        insert(fa, *it);
    }
    tr[ch].clear();
}

void debug(int u) {
    cout << "NODE" << ' ' << u + 1 << endl;
    for (map<long long, long long>::iterator it = tr[u].begin(); it != tr[u].end(); ++it) {
        cout << it->first << ' ' << it->second << endl;
    }
    cout << endl;
}

void go(int u, int fa) {
    for (int i = 0; i < (int)edge[u].size(); ++i) {
        int v = edge[u][i];
        if (v == fa) {
            continue;
        }
        go(v, u);
        merge(v, u);
    }
    addFront(u, val[u]);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int target;
        scanf("%d%d", &n, &target);
        for (int i = 0; i <= n; ++i) {
            edge[i].clear();
            tr[i].clear();
        }
        for (int i = 0; i < n; ++i) {
            int tmp;
            scanf("%d", &tmp);
            val[i] = tmp;
        }
        val[n] = INF;
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            scanf("%d%d", &u, &v); 
            --u, --v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        --target;
        edge[target].push_back(n);
        edge[n].push_back(target);
        ++n;
        go(0, -1);
        if (tr[0][0] >= INF) {
            puts("escaped");
        } else {
            puts("trapped");
        }
    }
    return 0;
}
