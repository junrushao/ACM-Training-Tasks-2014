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

int n;
const long double pi = acos(-1.0);

double solve() {
	if (n % 3 == 0) n /= 3;
	if (n == 1) return sqrt(3.0) / 4;
	long double t = 2 * pi / 3 / n;
	long double S = sin(t) - (1 - cos(t)) * tan((n - 1) / 3.0 / n * pi);
	return S * n / 2;
}

int main() {
	while (cin >> n && n) printf("%.10f\n", solve());
	return 0;
}
