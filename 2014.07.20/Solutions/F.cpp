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

const int N = 1000 + 10;
const int M = 200000 + 10;
const long long O = 1000000 + 10;
const long long INF = O * O;

int n, m;

struct Edge
{
	int t;
	long long c;
	Edge *n, *r;
} edges[M], *firstEdge[N], *totEdge;

Edge* makeEdge(int s, int t, long long c)
{
	Edge* e = totEdge ++;
	e->t = t; e->c = c;
	e->n = firstEdge[s]; firstEdge[s] = e;
	return e;
}

void addEdge(int s, int t, long long cst, long long cts)
{
	Edge *st = makeEdge(s, t, cst), *ts = makeEdge(t, s, cts);
	st->r = ts; ts->r = st;
}

long long maxflow(int s, int t, int tot)
{
	static int que[N];
	static int h[N];
	static int cnt[N];
	static long long aug[N];
	static Edge* prev[N];
	static Edge* cur[N];
	int qh = 0, qt = 0;
	fill(cnt, cnt + tot, 0);
	fill(h, h + tot, tot);
	que[qt ++] = t;
	h[t] = 0;
	for( ; qh < qt; ) {
		int u = que[qh ++];
		++ cnt[h[u]];
		for(Edge *e = firstEdge[u]; e; e = e->n) {
			int v = e->t;
			if (h[v] == tot && e->r->c) {
				h[v] = h[u] + 1;
				que[qt ++] = v;
			}
		}
	}

	for(int i = 0; i < tot; ++ i) {
		cur[i] = firstEdge[i];
	}
	int u = s, v;
	Edge *e;
	aug[s] = INF;
	long long flow = 0;
	for( ; h[s] < tot; ) {
		for(e = cur[u]; e; e = e->n) {
			v = e->t;
			if (e->c && h[v] + 1 == h[u]) {
				break;
			}
		}
		
		if (e) {
			v = e->t;
			aug[v] = min(aug[u], e->c);
			prev[v] = cur[u] = e;
			if ((u = v) == t) {
				long long by = aug[v];
				for( ; u != s; ) {
					prev[u]->c -= by;
					prev[u]->r->c += by;
					u = prev[u]->r->t;
				}
				flow += by;
			}
		} else {
			if (!--cnt[h[u]]) return flow;
			h[u] = tot;
			for(Edge *e = firstEdge[u]; e; e = e->n)
				if (h[e->t] + 1 < h[u] && e->c)
					h[u] = h[e->t] + 1, cur[u] = e;
			++ cnt[h[u]];
			if (u != s)
				u = prev[u]->r->t;
		}
	}
	return flow;
}

void solve() {
	cin >> n >> m;
	totEdge = edges;
	for(int i = 0; i < n; ++ i) {
		firstEdge[i] = 0;
	}
	int u, v, c, d;
	for(int i = 0; i < m; ++ i) {
		scanf("%d%d%d%d", &u, &v, &c, &d);
		if (d) {
			addEdge(u, v, c * O + 1, c * O + 1);
		} else {
			addEdge(u, v, c * O + 1, 0);
		}
	}
	long long ret = maxflow(0, n - 1, n) % O;
	cout << ret << endl;
}

int main() {
	int test;
	cin >> test;
	for(int i = 1; i <= test; ++ i) {
		cout << "Case " << i << ": ";
		solve();
	}
}
