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

const int N = 50 + 10;

int n, g;
int a[N];
double f[N][N];
double binom[N][N];

void solve() {
	cin >> g >> n;
	for(int i = 0; i <= n; ++ i)
		for(int j = 0; j <= g; ++ j)
			f[i][j] = 0;
	
	binom[0][0] = 1;
	for(int i = 1; i <= g; ++ i) {
		binom[i][0] = 1;
		for(int j = 1; j <= i; ++ j) {
			binom[i][j] = binom[i - 1][j - 1] / (double)n + binom[i - 1][j];
		}
	}
	for(int i = 0; i < n; ++ i) {
		cin >> a[i];
	}
	f[0][0] = 1;
	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j <= g; ++ j) {
			if (! f[i][j]) continue;
			for(int k = a[i]; k + j <= g; ++ k) {
				f[i + 1][k + j] += f[i][j] * binom[g - j][k];
			}
		}
	}
	printf("%.6f\n", 100 * f[n][g]);
}

int main() {
	int test;
	cin >> test;
	for(int i = 1; i <= test; ++ i) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
