#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 20;
const int N = 200005;

int e[N], succ[N], last[N], sum;
int type[N], dis[N], q[N];
int f[N][MAX + 5];
int n;

void add(int a, int b) {
	e[++sum] = b, succ[sum] = last[a], last[a] = sum;
}

int lca(int a, int b) {
	int i;
	if (dis[a] < dis[b]) {
		swap(a, b);
	}

	for (int i = MAX; i >= 0; i--) {
		if (dis[f[a][i]] >= dis[b]) {
			a = f[a][i];
		}
	}

	for (int i = MAX; i >= 0; i--) {
		if (f[a][i] != f[b][i]) {
			a = f[a][i], b = f[b][i];
		}
	}

	if (a == b) {
		return a;
	}

	return f[a][0];
}

int calc(int a, int b) {
	return dis[a] + dis[b] - (dis[lca(a, b)] << 1);
}

void work() {
	for (int i = 1; i <= n; i++) {
		last[i] = 0;
	}

	sum = 0;
	for (int i = 2; i <= n; i++) {
		int x;
		scanf("%d %d", &x, &type[i]);
		add(x, i);
	}

	dis[1] = 0;
	q[1] = 1;
	for (int h = 1, t = 1; h <= t; h++) {
		int now = q[h];
		for (int x = last[now]; x != 0; x = succ[x]) {
			f[e[x]][0] = now;
			dis[e[x]] = dis[now] + 1;
			q[++t] = e[x];
		}
	}

	for (int j = 1; j <= MAX; j++) {
		for (int i = 1; i <= n; i++) {
			f[i][j] = f[f[i][j - 1]][j - 1];
		}
	}
	
	long long sum = 0;
	int a = 1, b = 1, s = 1, ans = 0;
	for (int i = 2; i <= n; i++) {
		int now = calc(i, a), s1, s2;
		if (now > ans) {
			ans = now, s1 = i, s2 = a;
		}

		now = calc(i, b);
		if (now > ans) {
			ans = now, s1 = i, s2 = b;
		}

		a = s1, b = s2;
		if (type[i] != 0) {
			s = i;
		}
		
		sum += max(calc(s, a), calc(s, b));		
	}

	cout << sum << endl;
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		work();
	}

	return 0;
}
