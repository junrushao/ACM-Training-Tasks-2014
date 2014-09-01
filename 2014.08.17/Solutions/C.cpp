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

int n, x[333], y[333];
long long p[333];
vector<long long> all;
set<long long> h;
int ans;

int gcd(int a, int b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	if (!b) return a;
	return __gcd(a, b);
}

int main() {
	p[0] = 1;
	for (int i = 1; i <= 310; i++) p[i] = p[i - 1] * 31;
	scanf("%d", &n);
	REP(i, n) scanf("%d%d", &x[i], &y[i]);
	REP(i, n) REP(j, n) if (x[i] < x[j] || (x[i] == x[j] && y[i] < y[j])) {
		int dx = x[j] - x[i];
		int dy = y[j] - y[i];
		long long len = dx * dx + dy * dy;
		long long tl = 0, tr = 0;
		long long ll = p[i], lr = p[j];
		int ok = 1;
		REP(k, n) if (k != i && k != j) {
			int xx = x[k] - x[i];
			int yy = y[k] - y[i];
			if (xx * dy == yy * dx) {
				long long tmp = xx * dx + yy * dy;
				if (tmp < 0) ll += p[k];
				if (tmp > len) lr += p[k];
				if (0 < tmp && tmp < len) {
					ok = 0;
					break;
				}
			} else {
				if (xx * dy > yy * dx)
					tl += p[k];
				else
					tr += p[k];
			}
		}
		if (ok) {
			all.push_back(ll + tl);
			all.push_back(ll + tr);
			all.push_back(lr + tl);
			all.push_back(lr + tr);
		}
	}
	sort(all.begin(), all.end());
	all.erase(unique(all.begin(), all.end()), all.end());
	printf("%d\n", (int)all.size());
}
