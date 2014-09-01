#include<cstdio>
#include<algorithm>
using namespace std;
int a[3005], b[3005], c[3005];
int main() {
	while (1) {
		int n, i, j, l, r, ans = 0;
		scanf("%d", &n);
		if (n == 0) {
			return 0;
		}
		for (i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}
		for (i = 1; i <= n; i++) {
			scanf("%d", &b[i]);
		}
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				if (b[j] == a[i]) {
					c[i] = j;
				}
			}
		}
		for (i = 1; i < n; i++) {
			l = c[i], r = c[i];
			for (j = i + 1; j <= n; j++) {
				l = min(l, c[j]);
				r = max(r, c[j]);
				if (r - l == j - i) {
					ans++;
				}
			}
		}
		printf("%d\n", ans);
	}
}
