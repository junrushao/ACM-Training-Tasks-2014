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

void solve() {
}

int main() {
	int x, y, z;
	for( ; cin >> x >> y >> z; ) {
		int a = x * y;
		int b = z - y;
		int c = __gcd(a, b);
		a /= c;
		b /= c;
		cout << a << '/' << b << endl;
	}
}