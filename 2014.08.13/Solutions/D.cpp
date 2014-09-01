#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <ctime>
#include <cmath>
#include <set>
#include <map>

#define foreach(it,e) for (__typeof(e.begin ()) it = e.begin(); it != e.end(); it++)

#define sqr(x) ((x) * (x))
#define abs(x) (((x) > 0) ? (x) : (-(x))) 
#define lowbit(x) ((x) & (-(x)))

using namespace std;

typedef long long i64;
typedef unsigned long long u64;
typedef double dbl;

int const INF = INT_MAX >> 1;
int const limit = 20000;
int const C = 20 + 10;
int const N = 100 + 20;

int n, m, c, s, g;
int dist[C][N][N], fare[C][limit + 100], p[C], q[C][100], r[C][100];
int ans[N][N];

inline void floyd() {
	for (int type = 0; type < c; ++type) {
		for (int k = 0; k < n; ++k) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					dist[type][i][j] = min(dist[type][i][j], dist[type][i][k] + dist[type][k][j]);
				}
			}
		}
	}
}

inline void floyd_ans() {
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				ans[i][j] = min(ans[i][j], ans[i][k] + ans[k][j]);
			}
		}
	}
}

inline void solve() {
	for (int k = 0; k < c; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				dist[k][i][j] = INF;
				ans[i][j] = INF;
			}
		}
	}
	for (int k = 0; k < c; ++k) {
		fare[k][0] = 0;
	}
	while (m--) {
		int x, y, d, c;
		scanf("%d%d%d%d", &x, &y, &d, &c);
		x--; y--; c--;
		dist[c][x][y] = min(dist[c][x][y], d);
		dist[c][y][x] = min(dist[c][y][x], d);
	}
	for (int i = 0; i < c; ++i) {
		scanf("%d", &p[i]);
	}
	for (int i = 0; i < c; ++i) {
		for (int j = 0; j < p[i] - 1; ++j) {
			scanf("%d", &q[i][j]);
		}
		for (int j = 0; j < p[i]; ++j) {
			scanf("%d", &r[i][j]);
		}
	}
	floyd();
	for (int k = 0; k < c; ++k) {
		int now = 0;
		for (int i = 0; i < limit; ++i) {
			if (now < p[k] - 1 && i == q[k][now]) {
				now++;
			}
			fare[k][i + 1] = fare[k][i] + r[k][now];
		}
	}
	for (int k = 0; k < c; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (dist[k][i][j] < INF) {
					ans[i][j] = min(ans[i][j], fare[k][dist[k][i][j]]);
				}
			}
		}
	}
	floyd_ans();
	if (ans[s][g] < INF) {
		printf("%d\n", ans[s][g]);
	} else {
		puts("-1");
	}
}

int main () {
	while(scanf("%d%d%d%d%d", &n, &m, &c, &s, &g) != EOF && n > 0) {
		s--; g--;
		solve();
	}
	return 0;
}
