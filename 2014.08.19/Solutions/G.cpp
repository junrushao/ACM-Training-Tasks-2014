#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2000005;
const int base = 131;

int minWork(char a[], const int &n) {
	int i = 1, j = 2, k = 0, t = 0;
	do {
		k = 0;
		while (a[i + k] == a[j + k]) {
			k++;
		}

		if (a[i + k] > a[j + k]) {
			i = i + k + 1;
		} else {
			j = j + k + 1;
		}

		if (i == j) {
			i++;
		}

		if (i > j) {
			swap(i, j);
		}
	} while (j <= n);

	return i;
}

int n, m;
char s1[N], s2[N], a[N];
long long h1[N], h2[N], power[N];

long long get(long long A[], const int &l, const int &r) {
	return A[r] - A[l - 1] * power[r - l + 1];
}

int ok(const int &st) {
	int l = 0, r = n;
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		if (h2[mid] == get(h1, st, st + mid - 1)) {
			l = mid;
		} else {
			r = mid - 1;
		}
	}

	if (l == n || l == n - 1) {
		return 1;
	}

	return get(h2, l + 2, n) == get(h1, st + l + 1, st + n - 1);
}

int getAns() {
	if (ok(1)) {
		return 1;
	}

	int a = 2, b = m;
	while (1) {
		if (ok(a)) {
			return a;
		}

		if (ok(b)) {
			return b;
		}

		a++, b--;
	}
}

int main() {
	power[0] = 1;
	for (int i = 1; i <= N - 5; i++) {
		power[i] = power[i - 1] * base;
	}

	scanf("%d %d", &m, &n);
	scanf("%s", s1 + 1);
	scanf("%s", a + 1);
	for (int i = 1; i <= n; i++) {
		a[i + n] = a[i];
	}
	
	int x = minWork(a, n);
	for (int i = 0; i < n; i++) {
		s2[i + 1] = a[x + i];
	}

	printf("%s\n", s2 + 1);
	for (int i = 1; i <= n; i++) {
		h2[i] = h2[i - 1] * base + s2[i];
	}

	for (int i = 1; i <= m; i++) {
		s1[i + m] = s1[i];
	}

	for (int i = 1; i <= (m << 1); i++) {
		h1[i] = h1[i - 1] * base + s1[i];
	}

	x = getAns();
	for (int i = 0; i < m; i++) {
		printf("%c", s1[x + i]);
	}

	printf("\n");
	return 0;
}
