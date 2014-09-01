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

const int N = 100 + 10;
const double EPS = 1e-8;

struct Point
{
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	Point operator + (const Point &that) const {
		return Point(x + that.x, y + that.y);
	}
	Point operator - (const Point &that) const {
		return Point(x - that.x, y - that.y);
	}
	Point operator * (const double &that) const {
		return Point(x * that, y * that);
	}
	Point operator / (const double &that) const {
		return Point(x / that, y / that);
	}
	double abs() const {
		return hypot(x, y);
	}
	double alpha() const {
		return atan2(y, x);
	}
	Point rotAlpha(double alpha) const {
		double nx = cos(alpha) * x + sin(alpha) * y;
		double ny = -sin(alpha) * x + cos(alpha) * y;
		return Point(nx, ny);
	}
	void scan() {
		scanf("%lf%lf", &x, &y);
	}
	void write() {
		printf("(%.10f,%.10f)\n", x, y);
	}
};

int n, m;
double p;
Point a[N];
Point b[N];

void solve(Point st, Point ed, int left, double p)
{
	if (left == 0) {
		Point ret = st + (ed - st) * p;
		ret.write();
		return;
	}
	double total = 0;
	b[0] = st;
	for(int i = 1; i < n; ++ i) {
		total += (a[i] - a[i - 1]).abs();
		b[i] = st + (a[i] - a[0]).rotAlpha((a[n - 1] - a[0]).alpha() - (ed - st).alpha()) / (a[n - 1] - a[0]).abs() * (ed - st).abs();
	}
	/*
	st.write(); ed.write();
	cout << "now route" << endl;
	for(int i = 0; i < n; ++ i) {
		b[i].write();
	}
	cout << "over" << endl;
	*/
	double cur = 0, last = 0;
	for(int i = 1; i < n; ++ i) {
		last = cur;
		cur += (a[i] - a[i - 1]).abs();
		if (cur / total + EPS > p) {
			solve(b[i - 1], b[i], left - 1, (p - last / total) * total / (a[i] - a[i - 1]).abs());
			return;
		}
	}
}

void solve() {
	cin >> n;
	for(int i = 0; i < n; ++ i) {
		a[i].scan();
	}
	cin >> m;
	cin >> p;
	if (p < EPS) {
		a[0].write();
		return;
	}
	solve(a[0], a[n - 1], m, p);
}

int main() {
	int c;
	cin >> c;
	for( ; c --; ) {
		solve();
	}
	return 0;
}
