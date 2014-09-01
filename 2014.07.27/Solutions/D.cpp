#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define next NEXT

using namespace std;

const int N = 200005;

int n, now, test;
int a[N], succ[N], next[N], A[N];
pair <int, int> b[N];

void add(int a, int b) {
	for (int i = a; i <= now; i += (i & (0 - i))) {
		A[i] = max(A[i], b);
	}
}

int ask(int a) {
	int ret = 0;
	for (int i = a; i; i -= (i & (0 - i))) {
		ret = max(ret, A[i]);
	}

	return ret;
}

void work() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		b[i] = make_pair(a[i], i);
	}

	sort(b + 1, b + n + 1);
	now = 0;
	for (int i = 1; i <= n; i++) {
		if (i == 1 || b[i].first != b[i - 1].first) {
			now++;
		}

		a[b[i].second] = now;
	}

	succ[1] = next[n] = 1;
	for (int i = 2; i <= n; i++) {
		if (a[i] > a[i - 1]) {
			succ[i] = succ[i - 1] + 1;
		} else {
			succ[i] = 1;
		}
	}

	for (int i = n - 1; i >= 1; i--) {
		if (a[i] < a[i + 1]) {
			next[i] = next[i + 1] + 1;
		} else {
			next[i] = 1;
		}
	}

	for (int i = 1; i <= now; i++) {
		A[i] = 0;
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = max(ans, next[i] + ask(a[i] - 1));
		add(a[i], succ[i]);
	}

	printf("%d\n", ans);
}

int main() {
	scanf("%d", &test);
	while (test--) {
		work();
	}

	return 0;
}

