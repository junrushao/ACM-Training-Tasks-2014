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

const int N = 1000 + 10;
int n, m;
int a[N][N];

void solve() {
	for(int i = 2; i <= n; ++ i) {
		a[1][i] = (i - 1) * 1000;
		if (m) {
			m --;
			printf("%d %d %d\n", 1, i, a[1][i]);
		}
	}
	for(int i = 2; i <= n; ++ i) {
		int x = 999;
		for(int j = i + 1; j <= n; ++ j) {
			a[i][j] = x;
			if (m) {
				m --;
				printf("%d %d %d\n", i, j, a[i][j]);
			}
			x += 1000;
		}
	}
}

int main() {
	cin >> n >> m;
	solve();
}
