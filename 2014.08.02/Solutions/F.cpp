#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

#define foreach(e,x) for(__typeof(x.begin()) e=x.begin(); e!=x.end(); ++e)

const int N = 1000000 + 10;
const int M = N * 2;

struct Edge
{
	int t;
	Edge *n;
};

int n, q;
int father[N];
int bfsOrd[N];
int belong[N];
int down[N], up[N];
int f[N];
int value[N], pre[N], suf[N], children[N];
vector<pair<int, int> > vec;
Edge edges[M], *totEdge, *firstEdge[N];

void bfs(int s)
{
	int *que = bfsOrd;
	int qh = 0, qt = 0;
	int u, v;
	father[s] = -1;
	belong[0] = 0;
	for(int i = 0; i < n; ++ i) {
		up[i] = down[i] = N;
	}
	for(Edge *e = firstEdge[s]; e; e = e->n) {
		v = e->t;
		father[v] = s;
		belong[v] = v;
		que[qt ++] = v;
	}
	for( ; qh < qt; ) {
		u = que[qh ++];
		for(Edge *e = firstEdge[u]; e; e = e->n) {
			v = e->t;
			if (v == father[u]) continue;
			father[v] = u;
			belong[v] = belong[u];
			que[qt ++] = v;
		}
	}

	for(int i = qt - 1; i >= 0; -- i) {
		u = que[i];
		for(Edge *e = firstEdge[u]; e; e = e->n) {
			v = e->t;
			if (v == father[u]) continue;
			down[u] = min(down[u], down[v]);
			down[u] = min(down[u], v);
		}
	}

	int tmp;
	for(int i = 0; i < qt; ++ i) {
		u = que[i];
		int tot = 0;
		for(Edge *e = firstEdge[u]; e; e = e->n) {
			v = e->t;
			if (v == father[u]) continue;
			value[tot] = min(down[v], v);
			children[tot ++] = v;
		}

		tmp = N;
		for(int j = 0; j < tot; ++ j) {
			pre[j] = tmp;
			tmp = min(tmp, value[j]);
		}
		tmp = N;
		for(int j = tot - 1; j >= 0; -- j) {
			suf[j] = tmp;
			tmp = min(tmp, value[j]);
		}
		for(int j = 0; j < tot; ++ j) {
			tmp = min(min(pre[j], suf[j]), up[u]);
			v = children[j];
			up[v] = tmp;
		}
	}
	for(int i = 0; i < n; ++ i) {
		f[i] = min(up[i], down[i]);
	}
	f[0] = N;
	vec.clear();
	for(int i = 1; i < n; ++ i) {
		if (i == belong[i]) {
			vec.push_back(make_pair(min(down[i], i), i));
		}
	}
	sort(vec.begin(), vec.end());
	if ((int)vec.size() > 3) {
		vec.resize(3);
	}
}

int getValue(int u, int v)
{
	if (u == 0 && v == 0) {
		return 1;
	}
	if (belong[u] == belong[v]) {
		return 0;
	}
	int ret = N;
	for(int i = 0; i < (int)vec.size(); ++ i) {
		int id = vec[i].second;
		if (id == belong[u] || id == belong[v]) continue;
		ret = min(ret, vec[i].first);
	}
	ret = min(ret, min(f[u], f[v]));
	return ret;
}

int m;

void addEdge(int s, int t)
{
	Edge *e = totEdge ++;
	e->t = t; e->n = firstEdge[s]; firstEdge[s] = e;
}

void solve() {
	cin >> n >> m;
	totEdge = edges;
	for(int i = 0; i < n; ++ i) {
		firstEdge[i] = 0;
	}
	for(int i = 1; i < n; ++ i) {
		int u, v;
		scanf("%d%d", &u, &v);
		-- u, -- v;
		addEdge(u, v);
		addEdge(v, u);
	}
	bfs(0);
	int lastAns;
	for(int i = 0; i < m; ++ i) {
		int u, v;
		scanf("%d%d", &u, &v);
		if (i) {
			u ^= lastAns;
			v ^= lastAns;
		}
		-- u, -- v;
		lastAns = getValue(u, v) + 1;
		printf("%d\n", lastAns);
	}
}

int main() {
	solve();
	return 0;
}
