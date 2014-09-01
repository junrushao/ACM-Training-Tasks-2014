#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 1000000000;
const int N = 305;

int n;
int f[N][N], g[N][N], temp[N][N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &f[i][j]);
			if (i == j) {
				g[i][j] = 0;
			} else {
				g[i][j] = INF;
			}
		}
	}

	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (f[i][j] + f[j][i] == 0) {
				g[i][j] = g[j][i] = 0;
			} else if (f[i][j] + f[j][i] == 1) {
				g[i][j] = f[i][j];
				g[j][i] = f[j][i];
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			temp[i][j] = g[i][j];
		}
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (f[i][j] != g[i][j]) {
				printf("NO\n");
				return 0;
			}
		}
	}

	printf("YES\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (temp[i][j] == INF) {
				printf("0");
			} else if (temp[i][j] == 1) {
				printf("2");
			} else if (i != j) {
				printf("1");
			} else {
				printf("0");
			}
		}

		printf("\n");
	}

	return 0;
}

