#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10005;
const int M = 100005;
const int INF = 1000000000 + 1;
int a[N];
bool b[N];
vector<pair<int, int> > e[N];
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= m; i++) {
		int z, x, y;
		scanf("%d%d%d", &z, &x, &y);
		e[x].push_back(make_pair(z, y));
		e[y].push_back(make_pair(z, x));
	}
	for (int i = 1; i <= n; i++) {
		int k, v = INF;
		for (int j = 1; j <= n; j++) {
			if (b[j] == 0 && a[j] < v) {
				k = j, v = a[j];
			}
		}
		b[k] = 1;
		if (k == 1) {
			break;
		}
		for (int j = 0; j < (int)e[k].size(); j++) {
			int z = e[k][j].first, y = e[k][j].second;
			if (b[y] == 1 && a[z] > v + a[y]) {
				a[z] = v + a[y];
			}
		}
	}
	printf("%d\n", a[1]);
	return 0;
}

