#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <ctime>
#include <sstream>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <cassert>

using namespace std;
typedef long long LL;
typedef long double LD;

#define PII pair<int, int>
#define sz(X) ((int)((X).size()))

#define Rep(i, a, b) for (int i(a); i <= (b); ++i)

template<class T> T abs(T x){return x < 0 ? -x : x;}

const int MAXN = 100000 + 6;
int a[MAXN], b[MAXN];
bool vis[MAXN];

int main() {
	int n, m;
	scanf("%d%d",&n,&m);
	long long p;
	p = (long long)m;
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) continue;
		int k = 0;
		for (int j = i; !vis[j]; j = a[j]){
			vis[j] = 1;
			++k;
		}
		++b[k];
	}
	long long ans = 1LL;
	for (int i = 1; i <= n; ++i)
		for (long long j = (LL)(b[i]) * (LL)(i); j > 0; j -= (LL)(i)) {
			ans *= j;
			ans %= p;
		}
	cout << ans << endl;
	return 0;
}

