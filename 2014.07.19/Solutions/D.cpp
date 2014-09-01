#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

const int N = 20 + 2;
const int INF = 10000;
const int S = (1 << 16) + 1;
const int di[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
const int dj[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

int n;
int x[N], y[N];
char a[N][N];
int id[N][N];
int bom[N][N];
int f[S];

int valid(int i, int j)
{
	return i >= 0 && i < 10 && j >= 0 && j < 10;
}

void solve() {
	n = 0;
	for(int i = 0; i < 10; ++ i) {
		scanf("%s", a[i]);
		for(int j = 0; j < 10; ++ j) {
			if (a[i][j] == 'e') {
				x[n] = i;
				y[n] = j;
				id[i][j] = n ++;
			} else id[i][j] = -1;
		}
	}
	if (n == 0) {
		cout << 0 << ' ' << 0 << endl;
		return;
	}
	for(int i = 0; i < 10; ++ i) {
		for(int j = 0; j < 10; ++ j) {
			bom[i][j] = 0;
			for(int k = 0; k < 9; ++ k) {
				int ni = i + di[k];
				int nj = j + dj[k];
				if (valid(ni, nj)) {
					if (a[ni][nj] == 'g') {
						bom[i][j] = 0;
						break;
					}
					if (a[ni][nj] == 'e') {
						bom[i][j] += 1 << id[ni][nj];
					}
				}
			}
		}
	}

	int s = 1 << n;
	for(int i = 0; i < s; ++ i) {
		f[i] = INF;
	}
	f[s - 1] = 0;
	int ni, nj;
	int ret0 = 0, ret1 = 0;
	for(int i = s - 1; i > 0; -- i) {
		if (f[i] == INF) continue;
		//cout << i << ' ' << f[i] << endl;
		for(int j = 0; j < n; ++ j) {
			if (i >> j & 1) {
				for(int k = 0; k < 9; ++ k) {
					ni = x[j] + di[k];
					nj = y[j] + dj[k];
					if (valid(ni, nj) && (bom[ni][nj] & i)) {
						f[i - (bom[ni][nj] & i)] = min(f[i - (bom[ni][nj] & i)], f[i] + 1);
					}
				}
			}
		}
	}
	for(int i = 0; i < s; ++ i) {
		if (f[i] == INF) continue;
		int tot = 0;
		for(int j = 0; j < n; ++ j) {
			if (i >> j & 1) continue;
			++ tot;
		}
		if (tot > ret0 || tot == ret0 && f[i] < ret1) {
			ret0 = tot;
			ret1 = f[i];
		}
	}
	cout << ret0 << ' ' << ret1 << endl;
}

int main() {
	int test;
	cin >> test;
	for( ; test --; ) {
		solve();
	}
	return 0;
}
