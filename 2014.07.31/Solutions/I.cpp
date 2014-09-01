#include <iostream>

using namespace std;

typedef long long i64;

i64 n, MOD, ans, Z;

void calc(i64 p, int n) {
	i64 tmp = p % MOD * (p % MOD) % MOD + p % MOD - 1 + MOD;
	tmp %= MOD;
	for (int i = 2; i <= n; i++) {
		tmp = tmp * (p % MOD) % MOD + p - 1 + MOD; 
		tmp %= MOD;
	}
	for (int i = 0; i < n + n - 1; i++)
		tmp = tmp * (p % MOD) % MOD;
	ans = ans * tmp % MOD;
}

int main() {
	cin >> n >> MOD;
	Z = n;
	ans = 1;
	for (int i = 2; n / i >= i; i++) {
		if(n % i == 0) {
			int c = 0;
			while (n % i == 0) c++, n /= i;
			calc(i, c);		
		}
	}
	if (n > 1)
		calc(n, 1);
	n = Z % MOD;
	cout << ((n * n % MOD * n % MOD * n % MOD - ans + MOD) % MOD + MOD) % MOD << endl;
	return 0;
}

