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

const int N = 1000000 + 10;
const int INF = 1000000000 + 10;

int n;
int length;
int xa[N], xb[N];
int ya[N], yb[N];
int za[N], zb[N];

int check(int *xa, int *ya, int *za, int *xb, int *yb, int *zb)
{
	int minX = INF, maxX = -INF;
	int minY = INF, maxY = -INF;
	int minZ = INF, maxZ = -INF;
	int tot0 = 0, tot1 = 0;
	for(int i = 0; i < n; ++ i) {
		if (xa[i] == xb[i]) {
			++ tot0;
			minX = min(minX, xa[i]);
			maxX = max(maxX, xa[i]);
			minY = min(minY, ya[i]);
			maxY = max(maxY, ya[i]);
			minZ = min(minZ, za[i]);
			maxZ = max(maxZ, za[i]);
		} else {
			++ tot1;
		}
	}
	if (tot0 == 0 || tot1 == 0)
		return false;

	int l, r, u, d;
	for(int i = 0; i < n; ++ i) {
		if (xa[i] != xb[i]) {
			if (xa[i] >= minX || xb[i] <= maxX)
				return false;
			l = ya[i] - length;
			r = yb[i];
			u = za[i] - length;
			d = zb[i];
			if (minY <= l || maxY >= r || minZ <= u || maxZ >= d)
				return false;
		}
	}
	return true;
}

void solve() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++ i) {
		scanf("%d%d%d%d%d%d", xa + i, ya + i, za + i, xb + i, yb + i, zb + i);
		if (xa[i] > xb[i]) {
			swap(xa[i], xb[i]);
		}
		if (ya[i] > yb[i]) {
			swap(ya[i], yb[i]);
		}
		if (za[i] > zb[i]) {
			swap(za[i], zb[i]);
		}
	}
	
	length = max(max(xb[0] - xa[0], yb[0] - ya[0]), zb[0] - za[0]);
	if (length == 0) {
		puts("NO");
		return;
	}
	int ret = 0;
	ret += check(xa, ya, za, xb, yb, zb);
	ret += check(ya, xa, za, yb, xb, zb);
	ret += check(za, xa, ya, zb, xb, yb);
	if (ret >= 1) {
		puts("YES");
	} else {
		puts("NO");
	}
}

int main() {
	int test;
	cin >> test;
	for(int i = 0; i < test; ++ i) {
		solve();
	}
	return 0;
}
