#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MO = 2007;
const int N = 15;

long long n, k, x, ans, mo;
long long C[N][N];

long long mul(long long a, long long b) {
	long long ret = 0, c = a;
	while (b) {
		if (b & 1) {
			(ret += c) %= mo;
		}

		(c += c) %= mo;
		b >>= 1;
	}

	return ret;
}

long long power(long long a, long long b) {
	long long ret = 1, c = a;
	while (b) {
		if (b & 1) {
			ret = mul(ret, c);
		}

		c = mul(c, c);
		b >>= 1;
	}

	return ret;
}

int main() {
	cin >> n >> k;
	x = 1;
	for (int i = 1; i <= k; i++) {
		x *= i;
	}

	mo = x * MO;
	C[0][0] = 1;
	for (int i = 1; i <= k; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mo;
		}
	}

	ans = 0;
	for (int i = k; i >= 1; i--) {
		if ((i - k) % 2 == 0) {
			(ans += mul(power(i, n), C[k][i])) %= mo;
		} else {
			(ans -= mul(power(i, n), C[k][i])) %= mo;
		}

		//cout << ans << endl;
	}

	while (ans < 0) {
		ans += mo;
	}

	//cout << ans << endl;
	cout << ans / x << endl;
	return 0;
}

