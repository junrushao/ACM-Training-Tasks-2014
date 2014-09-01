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
const long double PI = acos(-1.);
const long double EPS = 1e-8;

inline int sign(long double x)
{
	return x < -EPS ? -1 : x > EPS;
}

struct Point
{
	long double x, y;
	int duep;
	Point() {}
	Point(long double _x, long double _y) : x(_x), y(_y) {}
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
	Point rot90() const {
		return Point(-y, x);
	}
	void write() {
		cout << "( " << x << "," << y << " )" << endl;
	}
};

#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))

Point isSS(Point p1, Point p2, Point q1, Point q2)
{
	long double a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return (p1 * a2 + p2 * a1) / (a1 + a2);
}

vector<Point> convexCut(const vector<Point> &ps, Point q1, Point q2)
{
	vector<Point> qs;
	int n = ps.size();
	for(int i = 0; i < n; ++ i) {
		Point p1 = ps[i], p2 = ps[(i + 1) % n];
		int d1 = crossOp(q1, q2, p1), d2 = crossOp(q1, q2, p2);
		if (d1 >= 0)
			qs.push_back(p1);
		if (d1 * d2 < 0)
			qs.push_back(isSS(p1, p2, q1, q2));
	}
	return qs;
}

int n;
int X, Y;
Point a[N];
vector<Point> vor[N];
int x[N], y[N];
int live[N];

inline long double sqr(long double x)
{
	return x * x;
}

long double calcX(vector<Point> vec, Point s)
{
	long double ret = 0;
	for(int i = 0; i < (int)vec.size(); ++ i) {
		Point u = vec[i];
		Point v = vec[(i + 1) % vec.size()];
		ret += (sqr(u.x - s.x) * u.y + 2 * sqr((u.x + v.x) * 0.5 - s.x) * (u.y + v.y) + sqr(v.x - s.x) * v.y) * (u.x - v.x) / 6;
	}
	return abs(ret);
}

long double calcAns(vector<Point> vec, Point s)
{
	if (vec.size() < 3) return 0;
	long double ret = calcX(vec, s);
	for(int i = 0; i < (int)vec.size(); ++ i) 
		swap(vec[i].x, vec[i].y);
	swap(s.x, s.y);
	ret += calcX(vec, s);
	return ret;
}

void solve() {
	cin >> n >> X >> Y;
	for(int i = 0; i < n; ++ i) {
		live[i] = true;
		cin >> x[i] >> y[i];
	}
	int tot = 0;
	for(int i = 0; i < n; ++ i) {
		if (! live[i]) continue;
		int flag = false;
		for(int j = i + 1; j < n; ++ j) {
			if (! live[j]) continue;
			if (x[i] == x[j] && y[i] == y[j]) {
				live[j] = false;
				flag = true;
			}
		}
		a[tot].duep = flag;
		a[tot].x = x[i];
		a[tot].y = y[i];
		tot ++;
	}

	n = tot;
	double ret = 0;
	for(int i = 0; i < n; ++ i) {
		vor[i].clear();
		vor[i].push_back(Point(0, 0));
		vor[i].push_back(Point(X, 0));
		vor[i].push_back(Point(X, Y));
		vor[i].push_back(Point(0, Y));

		for(int j = 0; j < n; ++ j) {
			if (i == j) continue;
			Point u = (a[i] + a[j]) * 0.5;
			Point v = (a[j] - a[i]).rot90() + u;
			vor[i] = convexCut(vor[i], u, v);
		}
		
		/*
		cout << "voronoi of " << i << endl;
		for(int j = 0; j < (int)vor[i].size(); ++ j) {
			vor[i][j].write();
		}
		cout << endl;
		*/

		if (a[i].duep) {
			ret += calcAns(vor[i], a[i]);
			continue;
		}

		for(int j = 0; j < n; ++ j) {
			if (i == j) continue;
			vector<Point> cur = vor[i];
			for(int k = 0; k < n; ++ k) {
				if (k == i || k == j) continue;
				Point u = (a[j] + a[k]) * 0.5;
				Point v = (a[k] - a[j]).rot90() + u;
				cur = convexCut(cur, u, v);
			}
			ret += calcAns(cur, a[j]);
		}
	}

	printf("%.12f\n", (double)ret / X / Y);
}

int main() {
	int test;
	cin >> test;
	for( ; test --; ) {
		solve();
	}
	return 0;
}
