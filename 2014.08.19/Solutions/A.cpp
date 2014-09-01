#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 30;

int n, m, k;
int a[N], now[N][N], f[N][N * N];

const int M = 21 * 21;

int ans[M];
bool g[M][M], use[M];

const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

void dfs(int sur, int color, int i, int j) {
	if (j > m) {
		i++, j = 1;
	}

	/*printf("sur = %d, color = %d, i = %d, j = %d\n", sur, color, i, j);
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= m; y++) {
			printf("%d ", now[x][y]);
		}

		printf("\n");
	}*/

	if (f[k][sur] == 0) {
		return;
	}
	
	if (sur == 0) {
		printf("YES\n");
		memset(g, 0, sizeof(g));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				for (int d = 0; d < 4; ++d) {
					int tx = i + dx[d], ty = j + dy[d];
					if (tx >= 1 && tx <= n && ty >= 1 && ty <= m) {
						int u = now[i][j], v = now[tx][ty];
						if (u != v) {
							g[u][v] = true;
						}
					}
				}
			}
		}
		for (int i = 1; i < color; ++i) {
			memset(use, 0, sizeof(use));
			for (int j = 1; j < i; ++j) {
				if (g[i][j]) {
					use[ans[j]] = true;
				}
			}
			ans[i] = 1;
			while (use[ans[i]]) {
				++ans[i];
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				printf("%c", ans[now[i][j]] + 'a' - 1);
			}

			printf("\n");
		}

		exit(0);
	}

	if (now[i][j]) {
		dfs(sur, color, i, j + 1);
		return;
	}

	for (int use = 1; use <= k; use++) {
		int size = a[use];
		if (j + size - 1 <= m) {
			int flag = 1;
			for (int l = j; l <= j + size - 1; l++) {
				if (now[i][l]) {
					flag = 0;
					break;
				}
			}

			if (flag) {
				for (int l = j; l <= j + size - 1; l++) {
					now[i][l] = color;
				}
			
				dfs(sur - size, color + 1, i, j + size);
				for	(int l = j; l <= j + size - 1; l++) {
					now[i][l] = 0;
				}
			}
		}

		if (i + size - 1 <= n) {
			int flag = 1;
			for (int l = i; l <= i + size - 1; l++) {
				if (now[l][j]) {
					flag = 0;
					break;
				}
			}

			if (flag) {
				for (int l = i; l <= i + size - 1; l++) {
					now[l][j] = color;
				}

				dfs(sur - size, color + 1, i, j + 1);
				for (int l = i; l <= i + size - 1; l++) {
					now[l][j] = 0;
				}
			}
		}
	}
}

int main() {
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= k; i++) {
		scanf("%d", &a[i]);
		if (a[i] > max(n, m)) {
			i--, k--;
		}
	}

	if (k == 0) {
		printf("NO\n");
		return 0;
	}

	sort(a + 1, a + k + 1);
	k = unique(a + 1, a + k + 1) - a - 1;
	f[0][0] = 1;
	for (int i = 1; i <= k; i++) {
		for (int j = 0; j <= n * m; j++) {
			f[i][j] = f[i - 1][j];
			if (j >= a[i]) {
				f[i][j] |= f[i][j - a[i]];
			}
		}
	}

	dfs(n * m, 1, 1, 1);
	printf("NO\n");
	return 0;
}

