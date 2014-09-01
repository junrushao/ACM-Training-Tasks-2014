#include <cstdio>

int a[1005];

int main() {
	int i, j, k, T, TT, n, ans;
	scanf("%d", &TT);
	for (T = 1; T <= TT; T++) {
		scanf("%d", &n);
		for (i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}
		ans = 0;
		for (i = 1; i < n; i++) {
			for(j = i+1; j <= n; j++) {
				if (a[i] <= a[j]) {
					ans++;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

