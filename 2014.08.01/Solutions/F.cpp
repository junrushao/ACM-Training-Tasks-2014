#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

int l;
vector<long long> divids;

long long gcd(long long a, long long b) {
	return b ? gcd(b, a % b) : a;
}

long long mul(long long a, long long b, long long mod) {
	long long delta = a, res = 0;
	while(b) {
		if (b & 1) {
			res += delta;
			if (res >= mod) {
				res -= mod;
			}
		}
		b >>= 1;
		delta += delta;
		if (delta >= mod) {
			delta -= mod;
		}
	}
	return res;
}

long long power(long long a, long long b, long long mod) {
	a %= mod;
	if (b == 0) {
		return 1 % mod;
	}
	long long t = power(a, b >> 1, mod);
	if (b & 1) {
		return mul(mul(t, t, mod), a, mod);
	} else {
		return mul(t, t, mod);
	}
}

long long phi(long long x) {
	long long res = x;
	for(long long i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			x /= i;
			res /= i;
			res *= (i - 1);
			while(x % i == 0) {
				x /= i;
			}
		}
	}
	if (x > 1) {
		res = res / x * (x - 1);
	}
	return res;
}

int main() {
	while(scanf("%d", &l) == 1 && l) {
		static int testCount = 0;
		printf("Case %d: ", ++testCount);
		long long q = 9LL * l;
		for(int i = 0; i < 3; i++) {
			if (q % 2 == 0) {
				q /= 2;
			}
		}
		if (gcd(q, 10) != 1) {
			puts("0");
			continue;
		}
		divids.clear();
		long long qq = phi(q);
		for(long long i = 1; i * i <= qq; i++) {
			if (qq % i == 0) {
				divids.push_back(i);
				if (i * i != qq) {
					divids.push_back(qq / i);
				}
			}
		}
		sort(divids.begin(), divids.end());
		for(int i = 0; i < (int)divids.size(); i++) {
			if (power(10, divids[i], q) == 1) {
				cout << divids[i] << endl;
				break;
			}
		}
	} 
	return 0;
}
