#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <ctime>
#include <sstream>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <assert.h>

using namespace std;
typedef long long LL;
typedef long double LD;

#define PII pair<int, int>
#define sz(X) ((int)((X).size()))

template<class T> T abs(T x){return x < 0 ? -x : x;}

const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

const int maxn = 31, maxs = 100000;
int d[maxn][maxn][4][maxn][maxn], ans[maxn][maxn];
bool b[maxn][maxn];
bool g[maxn][maxn][4];
int x[maxs], y[maxs], s[maxs];
int n, m;

void bfs(int tx, int ty, int tk){
	int l = 1, r = 1;
	x[l] = n; y[r] = m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			d[tx][ty][tk][i][j] = -1;
	d[tx][ty][tk][n][m] = 0;
	while (l <= r){
		for (int k = 0; k < 4; ++k)
			if (g[x[l]][y[l]][k]){
				int u = x[l] + dx[k], v = y[l] + dy[k];
				if (u == 0 || v == 0 || u > n || v > m) continue;
				if (d[tx][ty][tk][u][v] != -1) continue;
				d[tx][ty][tk][u][v] = d[tx][ty][tk][x[l]][y[l]] + 1;
				x[++r] = u;
				y[r] = v;
			}
		++l;
	}
}

void spfa(){
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j){
			b[i][j] = false;
			ans[i][j] = -1;
		}
	int l = 1, r = 1;
	b[1][1] = true;
	ans[1][1] = 0;
	x[l] = 1; y[l] = 1; s[l] = 0;
	while (l <= r){
		int i = x[l], j = y[l];
		for (int k = 0; k < 4; ++k)
			if (g[i][j][k]){
				int u = i + dx[k], v = j + dy[k];
				if (d[i][j][k][i][j] == -1) continue;
				int tmp = max(ans[i][j], s[l] + d[i][j][k][i][j]);
				if (ans[u][v] == -1 || tmp < ans[u][v]){
					ans[u][v] = tmp;
					if (!b[u][v]){
						b[u][v] = true;
						x[++r] = u;
						y[r] = v;
						s[r] = s[l] + 1;
					}
				}
			}
		b[i][j] = false;
		++l;
	}
	printf("%d\n", ans[n][m]);
}

int main(){
	while (scanf("%d%d", &n, &m)){
		if (n == 0) break;
		memset(g, false, sizeof(g));
		for (int i = 1; i <= n; ++i){

			for (int j = 1; j <= m - 1; ++j){
				int x;
				scanf("%d", &x);
				if (x == 0){
					g[i][j][0] = true;
					g[i][j + 1][1] = true;
				}
			}

			if (i != n){
				for (int j = 1; j <= m; ++j){
					int x;
					scanf("%d", &x);
					if (x == 0){
						g[i][j][2] = true;
						g[i + 1][j][3] = true;
					}
				}
			}
		}

		bool ok = true;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				for (int k = 0; k < 4; ++k)
					if (g[i][j][k]){
						int t, u = i + dx[k], v = j + dy[k];
						if (k <= 1) t = 1 - k; else t = 5 - k;
						g[i][j][k] = false;
						g[u][v][t] = false;
						bfs(i, j, k);
						if (d[i][j][k][1][1] == -1){
							ok = false;
						}
						g[i][j][k] = true;
						g[u][v][t] = true;
					}
		if (!ok){
			puts("-1");
			continue;
		}
		spfa();

	}
	return 0;
}

