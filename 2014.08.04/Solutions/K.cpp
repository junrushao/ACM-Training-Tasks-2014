#include <cassert>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
struct node {
	int d, n;
} g[7700007];
bool cmp(const node &a, const node &b) {
	if (a.d != b.d) {
		return a.d < b.d;
	}
	return a.n < b.n;
}
int main() {
	int a, b, c, d, m, n;
	scanf("%d%d%d%d", &a, &b, &c, &d);
	for (m = max(a + 1, c); ; m++) {
		if ((m * a) & 1) {
			continue;
		}
		n = m * b / c;
		if (n < max(b, d + 1)) {
			continue;
		}
		if ((n * d) & 1) {
			continue;
		}
		if (m * b != n * c) {
			continue;
		}
		break;
	}
	printf("%d %d\n", m, n);	
	for (int i = 1; i <= m + n; i++) {
		g[i].d = 0, g[i].n = i;
	}
	for (int i = 1; i <= m; i++) {
		sort(g + i, g + m + 1, cmp);
		if (g[i].d == a) {
			break;
		}
		int k = a - g[i].d;
		for (int j = 1; j <= k; j++) {
			printf("%d %d\n", g[i].n, g[i + j].n);
			g[i].d++, g[i + j].d++;
		}
	}
	for (int i = m + 1; i <= m + n + 1; i++) {
		sort(g + i, g + m + n + 1, cmp);
		if (g[i].d == d) {
			break;
		}
		int k = d - g[i].d;
		for (int j = 1; j <= k; j++) {
			printf("%d %d\n", g[i].n, g[i + j].n);
			g[i].d++, g[i + j].d++;
		}
	}
	for (int i = 1; i <= m; ++i) {
		assert(g[i].d == a);
	}
	for (int i = m + 1; i <= m + n; ++i) {
		assert(g[i].d == d);
	}
	for (int i = 1; i <= m + n; i++) {
		g[i].d = 0;
	}
	for (int i = 1; i <= m; i++) {
		sort(g + m + 1, g + m + n + 1, cmp);
		for (int j = 1; j <= b; j++) {
			printf("%d %d\n", g[i].n, g[m + j].n);
			g[i].d++, g[m + j].d++;
		}
	}
	for (int i = 1; i <= m; ++i) {
		assert(g[i].d == b);
	}
	for (int i = m + 1; i <= m + n; ++i) {
		assert(g[i].d == c);
	}
	return 0;
}

