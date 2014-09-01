#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 105;
int n, c, a[N];

bool constant(int l, int r) {
	for (int i = l; i <= r; ++i) {
		if (a[i] != a[l]) {
			return false;
		}
	}
	return true;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &c);
		for (int i = 0; i < n; ++i) {
			scanf("%d", a + i);
		}
		int dgr = 0;
		for (int i = 0; !constant(i, n - 1); ++i) {
			++dgr;
			for (int j = n - 1; j > i; --j) {
				a[j] -= a[j - 1];
			}
		}
		for (int i = 0; i < c; ++i) {
			a[n + i] = a[n - 1];
		}
		while (dgr--) {
			for (int i = dgr + 1; i < n + c; ++i) {
				a[i] += a[i - 1];
			}
		}
		for (int i = 0; i < c; ++i) {
			printf("%d%c", a[n + i], i == c - 1 ? '\n' : ' ');
		}
	}
	return 0;
}
