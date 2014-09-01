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
int c[N], d[N], a[N], b[N], e[N];
int vis[N], last[N];

int ask(int *c, int p)
{
	++ p;
	int ret = 0;
	for( ; p; p -= p & -p) {
		ret += c[p];
	}
	return ret;
}

void add(int *c, int p, int x)
{
	++ p;
	for( ; p < N; p += p & -p) {
		c[p] += x;
	}
}

void solve() {
	cin >> n;
	for(int i = 0; i < n; ++ i) {
		scanf("%d", a + i);
		e[i] = a[i];
	}
	sort(e, e + n);
	int m = unique(e, e + n) - e;
	for(int i = 0; i < n; ++ i) {
		b[i] = lower_bound(e, e + m, a[i]) - e + 1;
	}

	int tot = 0;
	for(int i = 0; i < n; ++ i) {
		if (vis[b[i]]) {
			printf("%d", tot - ask(c, last[b[i]]) + 1);
			add(c, last[b[i]], -1);
			last[b[i]] = i;
			add(c, last[b[i]], 1);
		} else {
			vis[b[i]] = true;
			printf("%d", tot - ask(d, b[i]) + a[i]);
			++ tot;
			add(d, b[i], 1);
			last[b[i]] = i;
			add(c, last[b[i]], 1);
		}
		if (i != n - 1) printf(" ");
		else printf("\n");
	}
}

int main() {
	solve();
	return 0;
}
