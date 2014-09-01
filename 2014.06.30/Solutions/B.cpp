
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = (1 << 20) + 10;

int n, s, m;
int tot;
int minr, maxr;
int lim;
int a[N];
int p[N];

void dfs(int x, int minv, int maxv, int cur)
{
	if (x < 0 || x > n) return;
	minv = min(minv, x);
	maxv = max(maxv, x);

	if (cur == lim) {
		p[tot ++] = x;
		return;
	}

	dfs(x + a[cur], minv, maxv, cur + 1);
	dfs(x - a[cur], minv, maxv, cur + 1);
}

void dfs2(int x, int minv, int maxv, int cur)
{
	minv = min(minv, x);
	maxv = max(maxv, x);
	if (minv < -n || maxv > n) return;

	if (cur == m) {
		int tomin = - minv;
		int tomax = maxv;
		int toret = x;

		int tmp;

		tmp = lower_bound(p, p + tot, tomin) - p;
		if (tmp != tot && p[tmp] >= tomin && p[tmp] + tomax <= n) {
			minr = min(minr, p[tmp] + toret);
		}
		tmp = upper_bound(p, p + tot, n - tomax) - p;
		if (tmp != 0 && p[tmp - 1] >= tomin && p[tmp - 1] + tomax <= n) {
			maxr = max(maxr, p[tmp - 1] + toret);
		}
		return;
	}

	dfs2(x + a[cur], minv, maxv, cur + 1);
	dfs2(x - a[cur], minv, maxv, cur + 1);
}

void solve()
{
	cin >> n >> s >> m;
	for(int i = 0; i < m; ++ i) {
		cin >> a[i];
	}
	minr = n + 1;
	maxr = -1;
	lim = (m + 1) / 2;
	tot = 0;
	dfs(s, s, s, 0);
	sort(p, p + tot);
	tot = unique(p, p + tot) - p;
	dfs2(0, 0, 0, lim);
	cout << minr << ' ' << maxr << endl;
}

int main()
{
	solve();
	return 0;
}
