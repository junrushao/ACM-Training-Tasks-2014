#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 405;
int k, f;

int xk[N], yk[N];
int xf[N], yf[N];
long long dis[N][N];

int a[25][25];

int match[N], b[N], c[N];

const long long INF = 1ll << 60;

int pre[N]; 
long long lx[N], ly[N], slack[N];
bool vx[N], vy[N];

bool find (const int i) {
	vx[i] = true;
	for (int j = 1; j <= f; ++j) {
		if (!vy[j]) {
			if (lx[i] + ly[j] == dis[i][j]) {
				vy[j] = true;
				if (pre[j] == -1 || find(pre[j])) {
					pre[j] = i;
					return true;
				}
			} else {
				slack[j] = min(slack[j], lx[i] + ly[j] - dis[i][j]);
			}
		}
	}
	return false;
}

void km() {
	for (int i = 1; i <= f; ++i) {
		for (int j = 1; j <= f; ++j) {
			dis[i][j] = -dis[i][j];
		}
	}
	for (int i = 1; i <= f; ++i) {
		pre[i] = -1;
		lx[i] = -INF;
		ly[i] = 0;
	}
	for (int i = 1; i <= f; ++i) {
		for (int j = 1; j <= f; ++j) {
			lx[i] = max(lx[i], dis[i][j]);
		}
	}
	for (int i = 1; i <= f; ++i) {
		for (int j = 1; j <= f; ++j) {
			vx[j] = vy[j] = 0;
		}
		for (int j = 1; j <= f; ++j) {
			slack[j] = INF;
		}
		while (!find(i)) {
			long long delta = INF;
			for (int j = 1; j <= f; ++j) {
				if (!vy[j]) {
					delta = min(slack[j], delta);
				}
			}
			for (int j = 1; j <= f; ++j) {
				if (vx[j]) {
					lx[j] -= delta;
				}
			}
			for (int j = 1; j <= f; ++j) {
				if (vy[j]) {
					ly[j] += delta;
				} else {
					slack[j] -= delta;
				}
			}
			for (int j = 1; j <= f; ++j) {
				vx[j] = vy[j] = 0;
			}
		}
	}
	for (int i = 1; i <= f; ++i) {
		match[pre[i]] = i;
	}
	for (int i = 1; i <= f; ++i) {
		for (int j = 1; j <= f; ++j) {
			dis[i][j] = -dis[i][j];
		}
	}
}

int main() {
	memset(dis, 0, sizeof(dis));
	int n, m, s;
	scanf("%d%d%d%d", &n, &m, &k, &s);
	for (int i = 1; i <= k; i++) {
		scanf("%d%d", &xk[i], &yk[i]);
		a[xk[i]][yk[i]] = 1;
	}
	for (int i = 1; i <= s; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[x][y] = 1;
	}
	f = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == 0) {
				f++;
				xf[f] = i, yf[f] = j;
			}
		}
	}
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= f; j++) {
			dis[i][j] = (long long)(abs(xk[i] - xf[j]) + abs(yk[i] - yf[j])) * 100000000 + xf[j] * 10000 + yf[j];
		}
	}
	km();
	for (int i = 1; i <= k; i++) {
		int o = 0;
		for (int j = 1; j <= k; j++) {
			if (b[j] == 0) {
				int q = 0;
				for (int p = 1; p <= f; p++) {
					if (c[p] == 0 && dis[j][p] < dis[j][match[j]]) {
						q = p;
						break;
					}
				}
				if (q == 0) {
					b[j] = 1;
					c[match[j]] = 1;
					o = j;
					break;
				}
			}
		}
		printf("%d%c", o, i == k ? '\n' : ' ');
	}
	return 0;
}
