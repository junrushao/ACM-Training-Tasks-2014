#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 60 * 2;
const int M = N * N * 2;
const int INF = 1000000000;

struct pile {
	int x, y, v;
} a[N];

int n, m, d, w, s, t;
int beg[N], nex[M], to[M], c[M], v[M], tot = 1;
bool bine(int x, int y) {
	return (a[x].x - a[y].x) * (a[x].x - a[y].x) + (a[x].y - a[y].y) * (a[x].y - a[y].y) <= d * d;
}

void add(int x, int y, int z, int cost) {
	nex[++tot] = beg[x], beg[x] = tot, to[tot] = y, c[tot] = z, v[tot] = cost;
	nex[++tot] = beg[y], beg[y] = tot, to[tot] = x, c[tot] = 0, v[tot] = -cost;
}

int dis[N], fa[N];

bool inque[N];

int augment() {
	for (int i = 1; i <= t; ++i) {
		dis[i] = INF, fa[i] = 0;
		inque[i] = false;
	}
	queue<int> q;
	dis[s] = 0;
	inque[s] = true;
	q.push(s);
	while (q.size()) {
		int u = q.front();
		q.pop();
		inque[u] = false;
		for (int j = beg[u]; j != 0; j = nex[j]) {
			if (c[j] == 0) {
				continue;
			}
			int v = to[j];
			if (dis[v] > dis[u] + ::v[j]) {
				dis[v] = dis[u] + ::v[j];
				fa[v] = j;
				if (!inque[v]) {
					q.push(v);
					inque[v] = true;
				}
			}
		}
	}
	if (dis[t] != INF) {
		int u = t;
		while (u != s) {
			int j = fa[u];
			--c[j], ++c[j ^ 1];
			u = to[j ^ 1];
		}
	}
	return dis[t];
}

int need[N], f[N];

int main() {
	scanf("%d%d%d%d", &n, &m, &d, &w);
	if (d >= w) {
		printf("1\n");
		return 0;
	}
	s = 1, t = (n << 1) + 2;
	tot = 1;
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].v);
		if (a[i].y <= d) {
			add(s, i << 1, INF, 1);
		}
		if (a[i].y + d >= w) {
			add(i << 1 | 1, t, INF, 1);
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (bine(i, j)) {
				add(i << 1 | 1, j << 1, INF, 1);
				add(j << 1 | 1, i << 1, INF, 1);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		add(i << 1, i << 1 | 1, a[i].v, 0);
	}
	for (int i = 0; i < m; ++i) {
		need[i] = augment();
	}
	if (need[0] == INF) {
		printf("IMPOSSIBLE\n");	
	} else {
		f[0] = 0;
		for (int i = 1; i <= m; ++i) {
			f[i] = INF;
			for (int j = 1; j <= i; ++j) {
				f[i] = min(f[i], max(f[i - j] + 1, need[j - 1]));
			}
		}
		printf("%d\n", f[m]);
	}
	return 0;
}

