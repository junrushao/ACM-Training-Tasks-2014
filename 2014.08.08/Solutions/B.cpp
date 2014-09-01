#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1005;
const int M = 200005;
const int INF = 1000000000;

int n, m, k;
int e[M << 1], succ[M << 1], last[N << 1], val[M << 1], sum;
int dis[N], pre[N], gap[N], cur[N];
int a[N][N];
int h1[N][N], h2[N][N];

void add(const int &a, const int &b, const int &c) {
	e[++sum] = b, succ[sum] = last[a], last[a] = sum;
	e[++sum] = a, succ[sum] = last[b], last[b] = sum;
	val[sum - 1] = c;
	val[sum] = 0;
}

int sap(int s, int t) {
	int ans = 0;
	gap[0] = t;
	for (int now = s; dis[now] < t; ) {
		for (int &i = cur[now]; i; i = succ[i]) {
			if (val[i] && dis[now] == dis[e[i]] + 1) {
				pre[e[i]] = i;
				now = e[i];
				break;
			}
		}

		if (now == t) {
			int flow = INF;
			for (now = t; now != s; now = e[pre[now] ^ 1]) {
				flow = min(flow, val[pre[now]]);
			}

			ans += flow;
			for (now = t; now != s; now = e[pre[now] ^ 1]) {
				val[pre[now]] -= flow;
				val[pre[now] ^ 1] += flow;
			}
		} else if (cur[now] == 0) {
			if (gap[dis[now]] == 1) {
				return ans;
			}

			int _min = t;
			for (int i = last[now]; i; i = succ[i]) {
				if (val[i] && dis[e[i]] + 1 < _min) {
					_min = dis[e[i]] + 1;
					cur[now] = i;
				}
			}

			gap[dis[now]]--, gap[_min]++, dis[now] = _min;
			if (now != s) {
				now = e[pre[now] ^ 1];
			}
		}
	}

	return ans;
}

int ok() {
	for (int i = 1; i < m; i++) {
		for (int j = i + 1; j <= m; j++) {
			h1[i][j] = h2[i][j] = 0;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < m; j++) {
			for (int l = j + 1; l <= m; l++) {
				if (a[i][j] < k && a[i][l] > 0 && h1[j][l]) {
					return 1;
				}

				if (a[i][j] > 0 && a[i][l] < k && h2[j][l]) {
					return 1;
				}
			}
		}

		for (int j = 1; j < m; j++) {
			for (int l = j + 1; l <= m; l++) {
				if (a[i][j] < k && a[i][l] > 0) {
					h2[j][l] = 1;
				}

				if (a[i][j] > 0 && a[i][l] < k) {
					h1[j][l] = 1;
				}
			}
		}
	}

	return 0;
}

void work() {
	int source = n + m + 1, target = n + m + 2;
	for (int i = 1; i <= target; i++) {
		last[i] = dis[i] = pre[i] = gap[i] = 0;
	}

	sum = 1;
	int s1 = 0, s2 = 0;
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x), s1 += x;
		add(source, i, x);
	}

	for (int i = 1; i<= m; i++) {
		int x;
		scanf("%d", &x), s2 += x;
		add(n + i, target, x);
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			add(i, n + j, k);
		}
	}

	if (s1 != s2 || sap(source, target) != s1) {
		printf("Impossible\n");
		return;
	}

	for (int i = 1; i <= n; i++) {
		for (int x = last[i]; x; x = succ[x]) {
			int y = e[x];
			if (y > n && y <= n + m) {
				a[i][y - n] = val[x ^ 1];
			}
		}
	}

	if (ok()) {
		printf("Not Unique\n");
		return; 
	}

	printf("Unique\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (j == m) {
				printf("%d\n", a[i][j]);
			} else {
				printf("%d ", a[i][j]);
			}
		}
	}
}

int main() {
	while (scanf("%d %d %d", &n, &m, &k) == 3 && (n + m + k)) {
		work();
	}
	return 0;
}
