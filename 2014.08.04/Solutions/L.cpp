#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long double LD;

vector<pair<int, pair<bool, pair<LD, LD> > > > evt;

int proc(bool op) {
	int ret = 0, n;
	scanf("%d", &n);
	int lx, lz;
	scanf("%d%d", &lx, &lz);
	ret = lz;
	for (int i = 1; i < n; ++i) {
		int x, z;
		scanf("%d%d", &x, &z);
		ret = max(ret, z);
		int dz = z - lz, dx = x - lx;
		if (dz != 0) {
			LD a = (LD)dx / dz, b = lx - a * lz;
			evt.push_back(make_pair(lz, make_pair(op, make_pair(a, b))));
			evt.push_back(make_pair(z, make_pair(op, make_pair(-a, -b))));
		}
		lx = x, lz = z;
	}
	return ret;
}

int main() {
	if (proc(false) != proc(true)) {
		printf("Invalid plan\n");
		return 0;
	}
	sort(evt.begin(), evt.end());
	reverse(evt.begin(), evt.end());
	LD ans = 0, fa = 0, fb = 0, ga = 0, gb = 0;
	for (int i = 0; i < (int)evt.size(); ++i) {
		bool op = evt[i].second.first;
		if (i) {
			LD a = fa * ga, b = fa * gb + ga * fb, c = fb * gb, x0 = evt[i].first, x1 = evt[i - 1].first;
			ans += a * x1 * x1 * x1 / 3 + b * x1 * x1 / 2 + c * x1;
			ans -= a * x0 * x0 * x0 / 3 + b * x0 * x0 / 2 + c * x0;
		}
		LD a = evt[i].second.second.first, b = evt[i].second.second.second;
		if (op) {
			fa += a, fb += b;
		} else {
			ga += a, gb += b;
		}
	}
	printf("%.12f\n", (double)ans);
	return 0;
}

