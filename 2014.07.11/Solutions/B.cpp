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

const int N = 500 + 10;

int n, m;
int a[N][N];
int w[N];

void solve() {
	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j < n; ++ j) {
			a[i][j] = 0;
		}
	}
	int ret = 0;
	for(int i = 0; i < n; ++ i) {
		scanf("%d", w + i);
		ret = max(ret, w[i]);
	}
	int u, v;
	vector< pair<int, int> > vec;
	for(int i = 0; i < m; ++ i) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		vec.push_back(make_pair(u, v));
		a[u][v] = a[v][u] = true;
	}
	for(int i = 0; i < m; ++ i) {
		u = vec[i].first;
		v = vec[i].second;
		ret = max(ret, w[u] + w[v]);
		for(int j = i + 1; j < m; ++ j) {
			int x = vec[j].first;
			int y = vec[j].second;
			if (x == u || x == v || y == u || y == v) continue;
			if (a[u][x] == 0 || a[u][y] == 0 || a[v][x] == 0 || a[v][y] == 0) continue;
			ret = max(ret, w[u] + w[v] + w[x] + w[y]);
		}
		for(int j = 0; j < n; ++ j) {
			if (j == u || j == v) continue;
			if (a[u][j] == 0 || a[v][j] == 0) continue;
			ret = max(ret, w[u] + w[v] + w[j]);
		}
	}
	cout << ret << endl;
}

int main() {
	for( ; cin >> n >> m; ) {
		solve();
	}
	return 0;
}