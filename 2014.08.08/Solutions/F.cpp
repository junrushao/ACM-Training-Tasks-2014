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
#include <cmath>

const double EPS = 1e-8;
const double INF = 1e100;
const int N = 305;
const int M = 55;

using namespace std;

struct Point {
	int x, y;
	
	void read() {
		scanf("%d %d", &x, &y);
	}
	
	double abs() {
		return sqrt((double)(x * x + y * y));
	}
	
	Point (const int &x = 0, const int &y = 0) :
		x(x), y(y) {}
		
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	
	friend bool operator < (const Point &a, const Point &b) {
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	}
} p[M], pNow;

int cmp(const int &a, const int &b) {
	return atan2(p[a].y - pNow.y, p[a].x - pNow.x) < atan2(p[b].y - pNow.y, p[b].x - pNow.x);
}

int det(const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}

int inside(const Point &p, const Point &a, const Point &b, const Point &c) {
	int s = (det(b - a, p - a) > 0) + (det(c - b, p - b) > 0) + (det(a - c, p - c) > 0);
	return (s == 0 || s == 3);
}

pair <Point, int> a[N];
int n, m, k;
int mask[M][M][M];
int now[M];
double f[M][1 << 7];

void work() {
	for (int i = 1; i <= n; i++) {
		a[i].first.read();
	}
	
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i].second);
	}
	
	for (int i = 1; i <= m; i++) {
		p[i].read();
	}
	
	sort(p + 1, p + m + 1);
	for (int i = 1; i < m - 1; i++) {
		for (int j = i + 1; j < m; j++) {
			for (int k = j + 1; k <= m; k++) {
				mask[i][j][k] = 0;
				for (int l = 1; l <= n; l++) {
					if (inside(a[l].first, p[i], p[j], p[k])) {
						mask[i][j][k] |= (1 << a[l].second - 1);
					}
				}
			}
		}
	}
	
	int full = (1 << k) - 1;
	double ans = INF;
	for (int i = 1; i <= m; i++) {
		pNow = p[i];
		int tot = 0;
		for (int j = i + 1; j <= m; j++) {
			now[++tot] = j;
		}
		
		sort(now + 1, now + tot + 1, cmp);
		for (int j = 1; j <= tot; j++) {
			f[j][0] = (p[now[j]] - pNow).abs();
			for (int kk = 1; kk <= full; kk++) {
				f[j][kk] = INF;
			}
		}
		
		for (int j = 1; j <= tot; j++) {
			for (int kk = 0; kk <= full; kk++) {
				double x = f[j][kk];
				
				if (x > 1e50) {
					continue;
				}
				
				if (kk == full) {
					ans = min(ans, x + (p[now[j]] - pNow).abs());
				}
				
				for (int l = j + 1; l <= tot; l++) {
					int aa = now[j], bb = now[l];
					if (aa > bb) {
						swap(aa, bb);
					}
					
					f[l][kk | mask[i][aa][bb]] = min(f[l][kk | mask[i][aa][bb]], f[j][kk] + (p[aa] - p[bb]).abs());
				}
			}
		}
	}
	
	if (ans > 1e50) {
		printf("Impossible\n");
	} else {
		printf("%.12f\n", ans);
	}
}

int main() {
	while (scanf("%d %d %d", &n, &m, &k) == 3 && (n + m + k)) {
		work();
	}
	return 0;
}
