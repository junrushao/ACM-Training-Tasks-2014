#include <vector>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 500;
int n, dl[N], dr[N], lc[N], rc[N], fa[N];

long long a[N], d[N];

void solve(int u) {
	if (d[u] != -1) {
		return;
	}
	solve(lc[u]);
	solve(rc[u]);
	long long a0 = a[lc[u]] * dl[u],
			  d0 = d[lc[u]] * dl[u],
			  a1 = a[rc[u]] * dr[u],
			  d1 = d[rc[u]] * dr[u],
			  x0 = 0, x1 = 0;
	while (a0 + d0 * x0 != a1 + d1 * x1) {
		if (a0 + d0 * x0 < a1 + d1 * x1) {
			long long inc = ((a1 + d1 * x1) - (a0 + d0 * x0) + d0 - 1) / d0;
			x0 += inc;
		} else {
			long long inc = ((a0 + d0 * x0) - (a1 + d1 * x1) + d1 - 1) / d1;
			x1 += inc;
		}
	}
	long long lcm = d0 * d1 / __gcd(d0, d1);
	a[u] = a[lc[u]] + x0 * d[lc[u]] + a[rc[u]] + x1 * d[rc[u]];
	d[u] = lcm / dl[u] + lcm / dr[u];
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		memset(fa, -1, sizeof(int) * n);
		for (int i = 0; i < n; ++i) {
			char op[2], op2[2];
			scanf("%d%d%s%s%d%d", dl + i, dr + i, op, op2, lc + i, rc + i);
			if (op[0] == 'W') {
				lc[i] += n - 1;
			} else {
				--lc[i];
				fa[lc[i]] = i;
			}
			if (op2[0] == 'W') {
				rc[i] += n - 1;
			} else {
				--rc[i];
				fa[rc[i]] = i;
			}
		}
		for (int i = 0; i < n; ++i) {
			a[i] = -1, d[i] = -1;
		}
		for (int i = n; i <= n * 2; ++i) {
			a[i] = 1, d[i] = 1;
		}
		{
			int id, mins;
			scanf("%d%d", &id, &mins);
			id += n;
			--id;
			a[id] = mins, d[id] = 1;
		}
		int root;
		for (int i = 0; i < n; ++i) {
			if (fa[i] == -1) {
				root = i;
			}
		}
		static int id = 0;
		solve(root);
		printf("Case %d: %d\n", ++id, (int)a[root]);
	}
	return 0;
}
