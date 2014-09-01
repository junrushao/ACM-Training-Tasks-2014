#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int n, k, l;

const int N = 20;
int a[N];

const int K = 6;
int p[K], q[K];

int ans;

int s[K << 2];

int stamp, vis[255];

void brute() {
	for (int i = 0; i < 6; ++i) {
		q[i] = p[i];
	}
	sort(p, p + k);
	do {
		for (int i = 0; i < k * 2; ++i) {
			s[i + 1] = s[i] ^ p[i % k];
		}
		++stamp;
		for (int i = 0; i < k; ++i) {
			for (int j = 1; j <= k; ++j) {
				vis[s[i] ^ s[i + j]] = stamp;
			}
		}
		int maxans = 0, cnt = l;
		while (vis[cnt] == stamp) {
			maxans = cnt;
			++cnt;
		}
		ans = max(ans, maxans);
	} while (next_permutation(p, p + k));
	for (int i = 0; i < 6; ++i) {
		p[i] = q[i];
	}
}

void update() {
	++stamp;	
	for (int i = 0; i < 1 << k; ++i) {
		int x = 0;
		for (int j = 0; j < k; ++j) {
			if (i >> j & 1) {
				x ^= p[j];
			}
		}
		vis[x] = stamp;
	}
	int maxans = 0, cnt = l;
	while (vis[cnt] == stamp) {
		maxans = cnt;
		++cnt;
	}
	if (maxans > ans) {
		brute();
	}
}

void dfs(int i, int j) {
	if (j == k) {
		update();
		return;
	}
	if (i == n) {
		return;
	}
	p[j] = a[i];
	dfs(i + 1, j + 1);
	dfs(i + 1, j);
}

int main() {
	while (scanf("%d%d%d", &n, &k, &l) == 3) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", a + i);
		}
		ans = 0;
		dfs(0, 0);
		printf("%d\n", ans);
	}
	return 0;
}

