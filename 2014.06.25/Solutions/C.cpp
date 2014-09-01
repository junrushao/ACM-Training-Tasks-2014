
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

const int maxn = 10, maxs = 10000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
int c[maxn][maxn];
bool b[maxn][maxn];
int x[maxs], y[maxs];
int target, n, m, ans;


int check(){
	if (c[1][1] != target) return 0;
	int l = 1, r = 1;
	x[l] = 1; y[l] = 1;
	memset(b, false, sizeof(b));
	b[1][1] = true;
	while (l <= r){
		for (int k = 0; k < 4; ++k){
			int u = x[l] + dx[k], v = y[l] + dy[k];
			if (u == 0 || v == 0 || u > n || v > m) continue;
			if (b[u][v] || c[u][v] != target) continue;
			b[u][v] = true;
			x[++r] = u;
			y[r] = v;
		}
		++l;
	}
	return r;
}

void fill(int color){
	int l = 1, r = 1;
	x[l] = 1; y[l] = 1;
	int cc = c[1][1];
	memset(b, false, sizeof(b));
	b[1][1] = true;
	c[1][1] = color;
	while (l <= r){
		for (int k = 0; k < 4; ++k){
			int u = x[l] + dx[k], v = y[l] + dy[k];
			if (u == 0 || v == 0 || u > n || v > m) continue;
			if (c[u][v] != cc || b[u][v]) continue;
			b[u][v] = true;
			c[u][v] = color;
			x[++r] = u;
			y[r] = v;
		}
		++l;
	}
}

void dfs(int t){
	if (t == 6){
		ans = max(ans, check());
		return;
	}
	int h[10][10];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			h[i][j] = c[i][j];
	for (int i = 1; i <= 6; ++i){
		fill(i);
		dfs(t + 1);
		for (int j = 1; j <= n; ++j)
			for (int k = 1; k <= m; ++k)
				c[j][k] = h[j][k];
	}
}

int main(){
	while (scanf("%d%d%d", &n, &m, &target)){
		if (n == 0) break;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				scanf("%d", &c[i][j]);
		ans = 0;
		dfs(1);
		printf("%d\n", ans);
	}
	return 0;
}
