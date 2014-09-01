
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;

long long l;

long long powerMod(long long base, long long b) {
	long long ret = 1;
	for( ; b; b >>= 1) {
		if (b & 1) ret = ret * base % MOD;
		base = base * base % MOD;
	}
	return ret;
}

void solve() {
	cin >> l;
	long long ans;
	ans = (powerMod(2, l) - 2 + MOD) % MOD * ((l - 1) % MOD * powerMod(2, l) % MOD + 1) % MOD;
	ans -= powerMod(2, 2 * l + 1) - l % MOD * powerMod(2, l + 1) % MOD - l % MOD * powerMod(2, l) % MOD - 2;
	ans = (ans % MOD + MOD) % MOD;
	cout << ans << endl;
}

int main() {
	solve();
	return 0;
}
