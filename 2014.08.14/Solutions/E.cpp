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

const int N = 1024 + 1;
const int MOD = 1e9 + 7;

int n;
int a[N];
int f1[N][N], f2[N][N];
int g1[N][N], g2[N][N];

void add(int &a, int b)
{
	a += b;
	if (a >= MOD) a %= MOD;
}

void mul(int &a, int b)
{
	a = (long long)a * b % MOD;
}

void solve() {
	memset(f1, 0, sizeof f1);
	memset(f2, 0, sizeof f2);
	memset(g1, 0, sizeof g1);
	memset(g2, 0, sizeof g2);

	cin >> n;
	for(int i = 0; i < n; ++ i) {
		scanf("%d", a + i);
	}

	f1[0][0] = 1;
	g1[0][0] = 1;
	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j < N; ++ j) {
			if (g1[i][j]) {
				add(g1[i + 1][j], g1[i][j]);
				add(g1[i + 1][j ^ a[i]], g1[i][j]);
				add(f1[i + 1][j ^ a[i]], g1[i][j]);
			}
		}
	}
	for(int i = n; i > 0; -- i) {
		for(int j = 0; j < N; ++ j) {
			if (g2[i][j]) {
				add(g2[i - 1][j], g2[i][j]);
				add(g2[i - 1][j & a[i - 1]], g2[i][j]);
				add(f2[i - 1][j & a[i - 1]], g2[i][j]);
			}
		}
		add(g2[i - 1][a[i - 1]], 1);
		add(f2[i - 1][a[i - 1]], 1);
	}

	int ret = 0;
	for(int i = 0; i < 1024; ++ i) {
		int sum = 0;
		for(int j = 0; j + 1 < n; ++ j) {
			add(sum, f1[j + 1][i]);
			int tmp = sum;
			mul(tmp, f2[j + 1][i]);
			add(ret, tmp);
		}
	}
	cout << ret << endl;
}

int main() {
	int test;
	cin >> test; 
	for( ; test --; ) {
		solve();
	}
	return 0;
}
