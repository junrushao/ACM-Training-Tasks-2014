#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

const int N = 105;

int n;
int g[N][N], ori[N][N];

int m;
int f[N];

int main() {
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%d", &g[i][j]);
				if (i != j && g[i][j] == 0) {
					g[i][j] = INF;
				}
				ori[i][j] = g[i][j];
			}
		}
		for (int k = 0; k < n; ++k) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
				}
			}
		}
		scanf("%d", &m);
		vector<int> v(m);
		for (int i = 0; i < m; ++i) {
			scanf("%d", &v[i]);
		}
		for (int i = 0; i <= m; ++i) {
			f[i] = m + 1;
		}
		f[0] = 0;
		for (int i = 0; i < m; ++i) {
			int len0 = 0;
			for (int j = i; j < m; ++j) {
				int len1 = g[v[i]][v[j]];
				if (len0 == len1) {
					f[j + 1] = min(f[j + 1], f[i] + (j != m - 1));
				}
				if (j + 1 < m) {
					len0 += ori[v[j]][v[j + 1]];
				}
			}
		}
		static int id = 0;
		printf("Case %d: %d\n", ++id, f[m]);
	}
	return 0;
}
