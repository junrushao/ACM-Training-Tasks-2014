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

const int N = 10000000 + 10;
int tot, b;
int n, ret;
char s[10], vis[10];
int flag[N];
bool notP[N];
int primes[N];

void dfs(int cur, int a, int first)
{
	if (flag[a] != b && ! notP[a]) {
		flag[a] = b;
		++ ret;
	}
	for(int i = 0; i < n; ++ i) {
		if (vis[i]) continue;
		if (! first && s[i] == '0') continue;
		vis[i] = true;
		dfs(cur + 1, a * 10 + s[i] - '0', 1);
		vis[i] = false;
	}
}

void solve() {
	scanf("%s", s);
	n = strlen(s);
	for(int i = 0; i < n; ++ i) {
		vis[i] = false;
	}
	++ b;
	ret = 0;
	dfs(0, 0, 0);
	cout << ret << endl;
}

int main() {
	tot = 0;
	notP[0] = notP[1] = true;
	for(int i = 2; i < N; ++ i) {
		if (! notP[i]) 
			primes[tot ++] = i;
		for(int j = 0; j < tot; ++ j) {
			if ((long long)i * primes[j] >= N) break;
			notP[i * primes[j]] = true;
			if (i % primes[j] == 0) break;
		}
	}
	int c;
	b = 0;
	cin >> c;
	for( ; c --; ) {
		solve();
	}
}
