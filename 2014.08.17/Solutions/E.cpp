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

const int N = 30000000 + 10;
int n, m, k;
int x, y, z;
int a[N], que[N];

void solve() {
	cin >> n >> m >> k;
	cin >> x >> y >> z;
	for(int i = 1; i <= k; ++ i) {
		scanf("%d", &a[i]);
	}
	for(int i = k + 1; i <= n; ++ i) {
		a[i] = a[i - 2] * x + a[i - 1] * y + z;
	}
	int qh = 0, qt = 0;
	long long sum = 0;
	for(int i = 1; i <= n; ++ i) {
		if (qh < qt && que[qh] <= i - m) {
			qh ++;
		}
		for( ; qh < qt ; ) {
			if (a[que[qt - 1]] >= a[i]) {
				-- qt;
			} else break;
		}
		que[qt ++] = i;
		if (i >= m) {
			sum += a[que[qh]];
		}
	}
	cout << sum << endl;
}

int main() {
	solve();
	return 0;
}
