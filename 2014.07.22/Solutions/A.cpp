#include<cstdio>
int a[1005];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int f, w, i, j, m, n, ans = 0;
		scanf("%d%d", &m, &n);
		for (i = 1; i <= m; i++) {
			scanf("%d", &a[i]);
			if (a[i] > 1) {
				f = a[i] - 2;
				w = i;
				a[i] = 1;
			}
		}
		i = w;
		for (j = 0; j <= n; j++) {
			if (a[i] == 0) {
				ans++;
			}
			if (i == m && f == 0) {
				f = 1;
				i = m - 1;
			} else if (i == 1 && f == 1) {
				f = 0;
				i = 2;
			} else if (f == 0) {
				i++;
			} else if (f == 1) {
				i--;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
