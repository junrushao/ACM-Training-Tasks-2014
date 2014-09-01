#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <bitset>
#include <string>
#define PQ priority_queue
#define OO 2147483647
#define Max(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((b) & FASTBUFFER | (a) & ~FASTBUFFER))
#define Min(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((a) & FASTBUFFER | (b) & ~FASTBUFFER))
#define Swap(a, b) (a ^= b, b ^= a, a ^= b)

int FASTBUFFER;

using namespace std;

const int N = 305;

int n, m, pre[N], deg[N], vis[N];
int q[N * N];
double dis[N], val[N], to[N][N];
vector <pair <int, double> > v[N];

int ok(double ans) {
	for (int i = 1; i <= n; i++) {
		dis[i] = 1e100;
		pre[i] = 0;
		deg[i] = 0;
	}
	
	for (int i = 1; i <= n; i++) {
		if (dis[i] > 1e90) {
			dis[i] = 0.0;
			q[1] = i;
			deg[i] = 1;
			for (int h = 1, t = 1; h <= t; h++) {
				int now = q[h];
				for (int x = 0; x < (int)v[now].size(); x++) {
					int y = v[now][x].first;
					double cost = v[now][x].second * ans - val[y];
					if (dis[now] + cost < dis[y]) {
						dis[y] = dis[now] + cost;
						pre[y] = now;
						deg[y]++;
						if (deg[y] > n) {
							return y;
						}
						
						q[++t] = y;
					}
				}
			}
		}
	}
	
	return 0;
}

void work() {
	for (int i = 1; i <= n; i++) {
		v[i].clear();
		scanf("%lf", &val[i]);
		for (int j = 1; j <= n; j++) {
			if (i != j) {
				to[i][j] = 1e100;
			} else {
				to[i][j] = 0.0;
			}
		}
	}
	
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		v[a].push_back(make_pair(b, (double)c));
		to[a][b] = min(to[a][b], (double)c);
	}
	
	double l = 0.0, r = 1e10;
	for (int i = 1; i <= 100; i++) {
		double mid = (l + r) * 0.5;
		if (ok(mid)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	
	int s = ok(l);
	for (int i = 1; i <= n; i++) {
		vis[i] = 0;
	}
	
	vis[s] = 1;
	s = pre[s];
	while (vis[s] == 0) {
		vis[s] = 1;
		s = pre[s];
	}
	
	int now = pre[s], ans1 = (int)(val[s] + 1e-8), ans2 = (int)(to[now][s] + 1e-8);
	while (now != s) {
		ans1 += (int)(val[now] + 1e-8);
		ans2 += (int)(to[pre[now]][now] + 1e-8);
		now = pre[now];
	}
	
	printf("%d %d\n", ans1, ans2);
}

int main() {
	while (scanf("%d %d", &n, &m) == 2 && (n + m)) {
		work();
	}
	
	return 0;
}
