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

long long modMul(long long a, long long b, long long P)
{
	long long ret = 0;
	for( ; a; a >>= 1) {
		if (a & 1) {
			ret += b;
			if (ret >= P)
				ret -= P;
		}
		b <<= 1;
		if (b >= P) b -= P;
	}
	return ret;
}

long long modPow(long long a, long long u, long long P)
{
	long long ret = 1;
	for( ; u; u >>= 1, a = modMul(a, a, P))
		if (u & 1) ret = modMul(ret, a, P);
	return ret;
}

int strongPseudoPrimetest(long long n, int base)
{
	long long n2 = n - 1, res;
	int s = 0;
	while(n2 % 2 == 0) n2 >>= 1, s ++;
	res = modPow(base, n2, n);
	if (res == 1 || res == n - 1) return 1;
	s --;
	for( ; s >= 0; ) {
		res = modMul(res, res, n);
		if (res == n - 1) return 1;
		s --;
	}
	return 0;
}

int isPrime(long long n)
{
	if (n < 2) return 0;
	if (n < 4) return 1;
	if (strongPseudoPrimetest(n, 2) == 0) return 0;
	if (strongPseudoPrimetest(n, 3) == 0) return 0;
	if (n < 1373653LL) return 1;
	if (strongPseudoPrimetest(n, 5) == 0) return 0;
	if (n < 2532600LL) return 1;
	if (strongPseudoPrimetest(n, 7) == 0) return 0;
	if (n == 3215031751LL) return 0;
	if (n < 25000000000LL) return 1;
	if (strongPseudoPrimetest(n, 11) == 0) return 0;
	if (n < 2152302898747LL) return 1;
	if (strongPseudoPrimetest(n, 13) == 0) return 0;
	if (n < 3474749660383LL) return 1;
	if (strongPseudoPrimetest(n, 17) == 0) return 0;
	if (n < 341550071728321LL) return 1;
	if (strongPseudoPrimetest(n, 19) == 0) return 0;
	if (strongPseudoPrimetest(n, 23) == 0) return 0;
	if (strongPseudoPrimetest(n, 29) == 0) return 0;
	if (strongPseudoPrimetest(n, 31) == 0) return 0;
	if (strongPseudoPrimetest(n, 37) == 0) return 0;
	return 1;
}

long long pollardRho(long long n)
{
	long long i = 1, x = rand() % n;
	long long y = x, k = 2, d = 1;
	do {
		d = __gcd(x - y + n, n);
		if (d != 1 && d != n) return d;
		if (++i == k) y = x, k <<= 1;
		x = (modMul(x, x, n) - 1 + n) % n;
	} while (y != x);
	return n;
}

map<long long, int> s;

void getFactor(long long n)
{
	if (n < 2) return;
	if (isPrime(n)) {
		s[n] ++;
		return;
	}
	long long x = pollardRho(n);
	getFactor(x);
	getFactor(n / x);
}

void solve() {
	long long n, k;
	cin >> n >> k;
	if (k == 1) {
		cout << "inf" << endl;
		return;
	}
	s.clear();
	getFactor(k);
	long long ret = -1;
	for(map<long long, int>::iterator it = s.begin(); it != s.end(); ++ it) {
		long long prime = it->first;
		long long cnt = it->second;
		long long x = 0;
		for(long long tmp = n; tmp; tmp /= prime)
			x += tmp / prime;
		if (ret < 0 || ret > x / cnt) {
			ret = x / cnt;
		}
	}
	cout << ret << endl;
}

int main() {
	int test;
	cin >> test;
	for(int i = 1; i <= test; ++ i) {
		cout << "Case " << i << ": ";
		solve();
	}
	return 0;
}
