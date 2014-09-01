#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int H = 16, N = 1 << 16, MOD = 786433, R = 10;

int a[H + 1][N + 1];

int ta[N + 1], tb[N + 1], tc[N + 1];

int inverse(int a) {
	return a == 1 ? a : (long long)(MOD - MOD / a) * inverse(MOD % a) % MOD;
}

int powmod(int a, int b) {
	a %= MOD;
	int ret = 1;	
	while (b) {
		if (b & 1) {
			ret = (long long)ret * a % MOD;
		}
		b >>= 1;
		a = (long long)a * a % MOD;
	}
	return ret;
}

void DFT(int P[], int n, int oper) {
	for (int i = 1, j = 0; i < n - 1; ++i) {
		for (int s = n; j ^= s >>= 1, ~j & s;);
		if (i < j) {
			swap(P[i], P[j]);
		}
	}
	for (int d = 0; (1 << d) < n; ++d) {
		int m = 1 << d, m2 = m * 2;
		int unit_p0 = powmod(R, (MOD - 1) / m2);
		if (oper < 0) {
			unit_p0 = inverse(unit_p0);
		}
		for (int i = 0; i < n; i += m2) {
			int unit = 1;
			for (int j = 0; j < m; ++j) {
				int &P1 = P[i + j + m], &P2 = P[i + j];
				int t = (long long)unit * P1 % MOD;
				P1 = (P2 - t + MOD) % MOD;
				P2 = (P2 + t) % MOD;
				unit = (long long)unit * unit_p0 % MOD;
			}
		}
	}
}

void mul(const int aa[N], const int bb[N], int c[N]) {
	for (int i = 0; i < N; ++i) {
		ta[i] = aa[i], tb[i] = bb[i];
	}
	DFT(ta, N, 1);
	DFT(tb, N, 1);
	for (int i = 0; i < N; ++i) {
		tc[i] = (long long)ta[i] * tb[i] % MOD;
	}
	DFT(tc, N, -1);
	int inv = inverse(N);
	for (int i = 0; i < N; ++i) {
		(c[i] += (long long)tc[i] * inv % MOD) %= MOD;
	}
}

void init() {
	a[0][1] = 1;
	a[1][2] = 2;
	a[1][3] = 1;
	for (int i = 2; i <= 15; ++i) {
		mul(a[i - 1], a[i - 1], a[i]);
		mul(a[i - 2], a[i - 1], a[i]);
		mul(a[i - 1], a[i - 2], a[i]);
		for (int j = N - 1; j > 0; --j) {
			a[i][j] = a[i][j - 1];
			a[i][j - 1] = 0;
		}
	}
}

int n, h;

int main() {
	init();
	scanf("%d%d", &n, &h);
	printf("%d\n", a[h][n]);
	return 0;
}

