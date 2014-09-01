#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

const int N = 10000 + 10;

int n, k;
double x[N], y[N];
pair<double, int> a[N];

void solve() {
	cin >> n >> k;
	int o = 0;
	for(int i = 0; i < n; ++ i) {
		scanf("%lf%lf", x + i, y + i);
		if (y[i] < y[o]) {
			o = i;
		}
	}
	int tot = 0;
	for(int i = 0; i < n; ++ i) {
		if (i == o) continue;
		a[tot ++] = make_pair(atan2(y[i] - y[o], x[i] - x[o]), i);
	}
	sort(a, a + tot);
	for(int i = 0; i < k - 1; ++ i) {
		printf("%d\n", a[i].second + 1);
	}
	printf("%d\n", o + 1);
}

int main() {
	int t; cin >> t;
	for( ; t --; ) {
		solve();
	}
}
