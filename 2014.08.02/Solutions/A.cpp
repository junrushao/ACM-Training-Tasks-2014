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
int n, k;
int a[N], b[N];
int c[N];

void add(int p, int x)
{
	for( ; p < N; p += p & -p) {
		c[p] += x;
	}
}

int ask(int p)
{
	int ret = 0;
	for( ; p; p -= p & -p) 
		ret += c[p];
	return ret;
}

void solve() {
	for(int i = 0; i < n; ++ i) {
		scanf("%d", a + i);
		b[i] = a[i];
	}
	sort(b, b + n);
	int m = unique(b, b + n) - b;
	for(int i = 0; i < n; ++ i) {
		a[i] = lower_bound(b, b + m, a[i]) - b + 1;
	}
	long long ret = 0;
	for(int i = n - 1; i >= 0; -- i) {
		ret += ask(a[i] - 1);
		add(a[i], 1);
	}
	cout << max(0LL, ret - k) << endl;
}

int main() {
	for( ; cin >> n >> k; ) {
		solve();
	}
	return 0;
}
