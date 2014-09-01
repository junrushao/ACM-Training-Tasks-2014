#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005 * 3;

int n, a[N];

int m, x[N], y[N], d[N];

vector<int> pos;

vector<int> place[N], go[N];

const int D = 51;
long long vis[N];

int len[N];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		pos.push_back(a[i]);
	}
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		scanf("%d%d%d", y + i, x + i, d + i);
		pos.push_back(x[i]);
		pos.push_back(y[i]);
	}
	sort(pos.begin(), pos.end());
	pos.erase(unique(pos.begin(), pos.end()), pos.end());
	for (int i = 0; i < n; ++i) {
		a[i] = lower_bound(pos.begin(), pos.end(), a[i]) - pos.begin();
		place[a[i]].push_back(i);
	}
	for (int i = 0; i < m; ++i) {
		x[i] = lower_bound(pos.begin(), pos.end(), x[i]) - pos.begin();
		y[i] = lower_bound(pos.begin(), pos.end(), y[i]) - pos.begin();
		go[x[i]].push_back(i);
	}
	for (int i = 0; i < n; ++i) {
		len[i] = -1;
	}
	for (int i = 0; i < (int)pos.size(); ++i) {
		for (int j = 0; j < (int)go[i].size(); ++j) {
			int id = go[i][j];
			vis[y[id]] |= 1ll << d[id];
		}
		for (int j = 0; j < (int)place[i].size(); ++j) {
			int u = place[i][j];
			for (int l = min(50, n - u); l >= 2; --l) {
				int v = u + l - 1;
				if (vis[a[v]] >> l & 1) {
					len[u] = l;
					break;
				}
			}
		}
		for (int j = 0; j < (int)go[i].size(); ++j) {
			int id = go[i][j];
			vis[y[id]] = 0;
		}
	}
	int best = -1;
	for (int i = 0; i < n; ++i) {
		best = max(best, i + len[i] - 1);
		printf("%d", best >= i ? 1 : 0);
	}
	printf("\n");
	return 0;
}

