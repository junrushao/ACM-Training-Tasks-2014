#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 305;

int n, m;
pair <long long, int> f[N][N];

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			f[i][j] = make_pair((i != j) * (1LL << 60), 0);
		}
	}

	for (int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		pair <long long, int> now = make_pair(c, 1);
		f[a][b] = f[b][a] = min(f[a][b], now);
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				f[i][j] = min(f[i][j], make_pair(f[i][k].first + f[k][j].first, f[i][k].second + f[k][j].second));
			}
		}
	}

	double ans = 0.0;
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			ans += f[i][j].second;
		}
	}

	ans /= (double)(n * (n - 1) / 2);
	printf("%.12f\n", ans);
	return 0;
}

