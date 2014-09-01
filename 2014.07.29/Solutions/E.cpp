#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define foreach(e,x) for(__typeof(x.begin()) e=x.begin(); e!=x.end(); ++e)

const int MOD = 1e9 + 7;
const int N = 100000 + 10;

int n, t;
int a[N];

void solve() {
	cin >> n >> t;
	for(int i = 0; i < n; ++ i) {
		scanf("%d", a + i);
	}
	sort(a, a + n);
	int ptr = 0;
	long long ans = 1;
	for(int i = 0; i < n; ++ i) {
		for( ; ptr < i && a[ptr] + t < a[i]; ++ ptr);
		ans = ans * (i - ptr + 1) % MOD;
	}
	cout << ans << endl;
}

int main() {
	solve();
	return 0;
}

