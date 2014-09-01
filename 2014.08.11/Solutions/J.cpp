#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
typedef long long LL;
using namespace std;
 
const int INF = 1000000000;
const int N = 22;
const int M = N * N * 8;
int dx[4] = {-1, 0, 1, 0}; 
int dy[4] = {0, 1, 0, -1};
 
int st[N][N], et[N][N];
int dis[N][N][4], dol[N][N][4][2];
 
int n, m, sx, sy, ex, ey;
 
struct node {
	int x, y, f, t, c;
};
 
bool operator < (node a, node b) {
	return a.t > b.t;
}
 
int dijkstra(int sx, int sy, int ex, int ey, int t, int fvck) {
	if (sx == ex && sy == ey) {
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 0; k < 4; k++) {
				dol[i][j][k][0] = dol[i][j][k][1] = (INF << 1) | 1;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		dol[sx][sy][i][0] = t;
	}
	priority_queue<node> a;
	node x, y;
	int tt = t;
	x.x = sx, x.y = sy, x.t = t, x.c = 0;
	for (int i = 0; i < 4; i++) {
		x.f = i;
		a.push(x);
	}
	while (!a.empty()) {
		x = a.top();
		if (x.x == ex && x.y == ey) {
			break;
		}
		a.pop();
		for (int i = 0; i < 4; i++) {
			y.x = x.x + dx[i], y.y = x.y + dy[i], y.f = i, y.c = x.c;
			t = x.t + dis[x.x][x.y][y.f];
			if (y.x < 1 || y.x > n || y.y < 1 || y.y > m) {
				continue;
			}
			if (i == ((x.f + 1) & 3)) {
				y.t = t;
				if (dol[y.x][y.y][i][y.c] > y.t) {
					dol[y.x][y.y][i][y.c] = y.t;
					a.push(y);
				}
			} else if (x.t <= et[x.x][x.y]) {
				y.t = max(x.t, st[x.x][x.y] + 1) + dis[x.x][x.y][y.f];
				if (dol[y.x][y.y][i][y.c] > y.t) {
					dol[y.x][y.y][i][y.c] = y.t;
					a.push(y);
				}
				if (y.c == 0 && fvck) {
					y.t = t, y.c = 1;
					if (dol[y.x][y.y][i][y.c] > y.t) {
						dol[y.x][y.y][i][y.c] = y.t;
						a.push(y);
					}
				}
			} else if (y.c == 0 && fvck) {
				y.t = t, y.c = 1;
				if (dol[y.x][y.y][i][y.c] > y.t) {
					dol[y.x][y.y][i][y.c] = y.t;
					a.push(y);
				}
			}
		}
	}
	if (a.empty()) {
		return INF;
	}
	return x.t - tt;
}
int artskjid(int sx, int sy, int ex, int ey, int t, int fvck) {
	if (sx == ex && sy == ey) {
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 0; k < 4; k++) {
				dol[i][j][k][0] = dol[i][j][k][1] = (INF << 1) | 1;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		dol[sx][sy][i][0] = -t;
	}
	priority_queue<node> a;
	node x, y;
	int tt = -t;
	x.x = sx, x.y = sy, x.t = -t, x.c = 0;
	for (int i = 0; i < 4; i++) {
		x.f = i;
		a.push(x);
	}
	while (!a.empty()) {
		x = a.top();
		if (x.x == ex && x.y == ey) {
			break;
		}
		a.pop();
		y = x;
		y.x += dx[x.f], y.y += dy[x.f];
		t = x.t + dis[x.x][x.y][x.f];
		if (t > 0 || y.x < 1 || y.x > n || y.y < 1 || y.y > m) {
			continue;
		}
		for (int i = 0; i < 4; i++) {
			y.f = i, y.c = x.c;
			if (i == ((x.f + 3) & 3)) {
				y.t = t;
				if (dol[y.x][y.y][i][y.c] > y.t) {
					dol[y.x][y.y][i][y.c] = y.t;
					a.push(y);
				}
			} else if (t > st[y.x][y.y]) {
				y.t = max(t, -et[y.x][y.y]);
				if (dol[y.x][y.y][i][y.c] > y.t) {
					dol[y.x][y.y][i][y.c] = y.t;
					a.push(y);
				}
				if (y.c == 0 && fvck) {
					y.t = t, y.c = 1;
					if (dol[y.x][y.y][i][y.c] > y.t) {
						dol[y.x][y.y][i][y.c] = y.t;
						a.push(y);
					}
				}
			} else if (y.c == 0 && fvck) {
				y.t = t, y.c = 1;
				if (dol[y.x][y.y][i][y.c] > y.t) {
					dol[y.x][y.y][i][y.c] = y.t;
					a.push(y);
				}
			}
		}
	}
	if (a.empty()) {
		return INF;
	}
	return x.t - tt;
}

int main() {
	int T = 0;
	while (scanf("%d%d", &n, &m) != EOF) {
		T++;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%d", &st[i][j]);
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%d", &et[i][j]);
				if (st[i][j] >= et[i][j]) {
					st[i][j] = et[i][j] = -1;
				}
			}
		}
		int v;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j < m; j++) {
				scanf("%d", &v);
				dis[i][j][1] = dis[i][j + 1][3] = v;
			}
		}
		for (int i = 1; i < n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%d", &v);
				dis[i][j][2] = dis[i + 1][j][0] = v;
			}
		}
		scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
		st[1][1] = st[1][m] = st[n][1] = st[n][m] = st[sx][sy] = st[ex][ey] = -1;
		et[1][1] = et[1][m] = et[n][1] = et[n][m] = et[sx][sy] = et[ex][ey] = INF;
		int ans = INF;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (et[i][j] >= 0) {
					ans = min(ans, min(min(dijkstra(i, j, ex, ey, st[i][j] + 1, 0) + artskjid(i, j, sx, sy, st[i][j] + 1, 1), 
									   dijkstra(i, j, ex, ey, et[i][j], 0) 	+ artskjid(i, j, sx, sy, et[i][j], 1)),
									   min(dijkstra(i, j, ex, ey, st[i][j] + 1, 1) + artskjid(i, j, sx, sy, st[i][j] + 1, 0), 
									   dijkstra(i, j, ex, ey, et[i][j], 1) 	+ artskjid(i, j, sx, sy, et[i][j], 0))));
				}
			}
		}
		printf("Case #%d: ", T);
		if (ans < INF) {
			printf("%d\n", ans);
		} else {
			printf("-1\n");
		}
	}
	return 0;
}
