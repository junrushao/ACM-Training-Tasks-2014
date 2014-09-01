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

const int maxn = 33;

struct Node{
	int num, least;

	void update(Node u){
		if (u.num == num){
			least = max(least, u.least);
		} else if (u.num > num){
			num = u.num;
			least = u.least;
		}
	}

	Node operator + (const Node &u){
		Node t;
		if (num == 0 || u.num == 0){
			t.num = 0;
			return t;
		}
		t.num = num + u.num;
		t.least = min(least, u.least);
		return t;
	}

}f[maxn][maxn][maxn][maxn];

int sum[maxn][maxn];
int n, m, power;

int area(int x, int y, int u, int v){
	return sum[u][v] - sum[x - 1][v] - sum[u][y - 1] + sum[x - 1][y - 1];
}

int main(){
	while (scanf("%d%d%d", &n, &m, &power)){
		if (n == 0) break;
		memset(sum, 0, sizeof(sum));
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j){
				int x;
				scanf("%d", &x);
				sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + x;
			}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				for (int u = i; u <= n; ++u)
					for (int v = j; v <= m; ++v)
						f[i][j][u][v].num = 0;
		for (int dx = 0; dx < n; ++dx)
			for (int dy = 0; dy < m; ++dy)
				for (int i = 1; i <= n - dx; ++i)
					for (int j = 1; j <= m - dy; ++j){
						int u = i + dx, v = j + dy;
						if (sum[n][m] - area(i, j, u, v) <= power){
							f[i][j][u][v].num = 1;
							f[i][j][u][v].least = area(i, j, u, v);
						}
						for (int k = 0; k < dx; ++k)
							if (i + k + 1 <= u) f[i][j][u][v].update(f[i][j][i + k][v] + f[i + k + 1][j][u][v]);
						for (int k = 0; k < dy; ++k)
							if (j + k + 1 <= v) f[i][j][u][v].update(f[i][j][u][j + k] + f[i][j + k + 1][u][v]);
					}
		printf("%d %d\n", f[1][1][n][m].num, power - (sum[n][m] - f[1][1][n][m].least));
	}
	return 0;
}
