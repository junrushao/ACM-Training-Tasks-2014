#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int N = 505;
pair <int, int> a[N], b[N];
int n, test, tot, ans;

void up(int x, int &ans1, int &ans2) {
	if (x > ans2) {
		ans2 = x;
		if (ans2 > ans1) {
			swap(ans1, ans2);
		}
	}
}

void calc(int n, pair <int, int> a[]) {
	int s = 0, ans1 = 0, ans2 = 0;
	for (int i = 1; i <= n; i++) {
		s += a[i].second;
		if (s > a[i].first) {
			up(s - a[i].first, ans1, ans2);
		}
	}

	ans = min(ans, ans1 + ans2);
	/*if (ans1 + ans2 == 4) {
		for (int i = 1; i <= n; i++) {
			printf("%d %d\n", a[i].first, a[i].second);
		}
	}*/
}

void work() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i].second, &a[i].first);
	}
	
	sort(a + 1, a + n + 1);
	ans = 2000000000;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			tot = 0;
			for (int k = 1; k <= n; k++) {
				if (i == k) {
					continue;
				}

				if (tot + 1 == j) {
					b[++tot] = a[i];
				}

				b[++tot] = a[k];
			}

			if (tot + 1 == j) {
				b[++tot] = a[i];
			}

			calc(n, b);
		}
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
