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
#include <cassert>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

const int N = 20000 + 10;
const double EPS = 1e-8;

struct Point
{
	int x, y;
	int id;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
	Point operator - (const Point &that) const {
		return Point(x - that.x, y - that.y);
	}
	long long abs() const {
		return x * x + y * y;
	}
	int operator < (const Point &that) const {
		long long tmp = (long long)x * that.y - (long long)y * that.x;
		if (tmp) return tmp > 0;
		return abs() < that.abs();
	}
	void scan() {
		scanf("%d%d", &x, &y);
	}
};

bool equal(Point a, Point b)
{
	long long tmp = (long long)a.x * b.y - (long long)a.y * b.x;
	return tmp == 0;
}

int n;
Point a[N];
Point b[N];

void solve() {
	cin >> n;
	int c = 0;
	for(int i = 0; i < n; ++ i) {
		a[i].scan();
		a[i].id = i;
		if (a[i].y < a[c].y || (a[i].y == a[c].y && a[i].x < a[c].x)) {
			c = i;
		}
	}
	int tot = 0;
	for(int i = 0; i < n; ++ i) {
		if (i == c) continue;
		b[tot] = a[i] - a[c];
		b[tot ++].id = a[i].id;
	} 
	sort(b, b + tot);
	int cur = tot - 1;
	for( ; cur && equal(b[cur - 1], b[cur]); ) -- cur;
	reverse(b + cur, b + tot);
	printf("%d", a[c].id);
	for(int i = 0; i < tot; ++ i) {
		printf(" %d", b[i].id);
		assert(b[i].id != c);
	}
	cout << endl;
	assert(tot == n - 1);
}

int main() {
	int c;
	cin >> c;
	for( ; c --; ) {
		solve();
	}
	return 0;
}
