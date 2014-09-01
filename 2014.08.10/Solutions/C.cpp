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

const int N = 100000 + 10;
int n;
int tot;
int p[N];
long long b[N];
long long a[N];

void read(long long &x)
{
	scanf("%lld", &x);
}

void solve() {
	cin >> n;
	for(int i = 0; i < n; ++ i) {
		read(a[i]);
	}
	tot = 0;
	long long ret = 0;
	for(int i = 0; i < n; ++ i) {
		int tot2 = 0;
		for(int j = 0; j < tot; ++ j) {
			long long tmp = __gcd(a[i], b[j]);
			if (tot2 && tmp == b[tot2 - 1]) continue;
			p[tot2] = p[j];
			b[tot2 ++] = tmp;
		}
		tot = tot2;
		if (tot == 0 || b[tot - 1] != a[i]) {
			p[tot] = i;
			b[tot ++] = a[i];
		}
		for(int j = 0; j < tot; ++ j) {
			ret = max(ret, b[j] * (i - p[j] + 1));
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
