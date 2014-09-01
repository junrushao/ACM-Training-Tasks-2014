#include <stdio.h>
#include <algorithm>
using namespace std;
int min(int a, int b) {
	return a <= b ? a : b;
}
int max(int a, int b) {
	return a >= b ? a : b;
}
struct node {
	int x, y;
} a[50005];
bool cmp(node a, node b) {
	return a.x < b.x;
}
int ans[60005], now[60005];
int main() {
	int i, j, k, M, n, l, r, m, T, TT, x, y, tot;
	scanf("%d", &TT);
	for (T = 1; T <= TT; T++) {
		scanf("%d%d", &M, &n);
		scanf("%d%d%d%d", &a[1].x, &a[1].y, &a[2].x, &a[2].y);
		l = min(a[1].x, a[2].x), r = max(a[1].x, a[2].x);
		m = a[1].y;
		j = 0;
		for (i = 3; i <= n; i++) {
			scanf("%d%d", &x, &y);
			if (x <= l || x >= r) {
				continue;
			}
			++j, a[j].x = x, a[j].y = y;
		}
		n = j;
		sort(a + 1, a + n + 1, cmp);
		for (i = 1; i <= n; i++) {
			a[i].y -= m;
			if (a[i].y < 0) {
				a[i].y = -a[i].y;
			}
		}
		j = 1;
		for (i = l; i <= r; i++) {
			ans[i] = 100000;
		}
		for (i = l; i <= r; i++) {
			while (j <= n && a[j].x < i) {
				j++;
			}
			if (i == l) {
				now[i] = -1;
				ans[i] = min(ans[i], now[i]);
				continue;
			}
			now[i] = now[i-1] + 1;
			while (j <= n && a[j].x == i) {
				now[i] = min(now[i], a[j].y - 1);
				j++;
			}
			ans[i] = min(ans[i], now[i]);
		}
		j = n;
		for (i = r; i >= l; i--) {
			while (j >= 1 && a[j].x > i) {
				j--;
			}
			if (i == r) {
				now[i] = -1;
				ans[i] = min(ans[i], now[i]);
				continue;
			}
			now[i] = now[i+1] + 1;
			while (j >= 1 && a[j].x == i) {
				now[i] = min(now[i], a[j].y - 1);
				j--;
			}
			ans[i] = min(ans[i], now[i]);
		}
		tot = 0;
		for (i = l; i <= r; i++) {
			if (ans[i] == -1) {
				continue;
			}
			x = min(ans[i], m), y = min(ans[i], M-m-1);
			tot += x + y + 1;
		}
		printf("%d\n", tot);
	}
	return 0;
}
