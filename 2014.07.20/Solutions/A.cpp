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

const double PI = acos(-1.);
const double EPS = 1e-8;
const int N = 2000 + 10;

inline int sign(double x)
{
	return x < -EPS ? -1 : x > EPS;
}

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
	double det(const Point &that) const {
		return x * that.y - that.x * y;
	}
	double len() const {
		return hypot(y, x);
	}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
};

#define cross(p1, p2, p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))

Point isSS(Point p1, Point p2, Point q1, Point q2)
{
	double a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return (p1 * a2 + p2 * a1) / (a1 + a2);
}

vector<Point> convecCut(const vector<Point> &ps, Point q1, Point q2)
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
double r;
Point info[N];

double dot(const Point &a, const Point &b)
{
	return a.x * b.x + a.y * b.y;
}

double Cross(const Point &a, const Point &b)
{
	return a.x * b.y - a.y * b.x;
}

double area2(Point pa, Point pb)
{
	if (pa.len() < pb.len()) swap(pa, pb);
	if (pb.len() < EPS) return 0;
	double a, b, c, B, C, sinB, cosB, sinC, cosC, S, h, theta;
	a = pb.len();
	b = pa.len();
	c = (pb - pa).len();
	cosB = dot(pb, pb - pa) / a / c;
	B = acos(cosB);
	cosC = dot(pa, pb) / a / b;
	C = acos(cosC);
	if (a > r) {
		S = (C / 2) * r * r;
		h = a * b * sin(C) / c;
		if (h < r && B < PI / 2) S -= (acos(h / r) * r * r - h * sqrt(r * r - h * h));
	} else if (b > r) {
		theta = PI - B - asin(sin(B) / r * a);
		S = .5 * a * r * sin(theta) + (C - theta) / 2 * r * r;
	} else {
		S = .5 * sin(C) * a * b;
	}
	return S;
}

double area() {
	double S = 0;
	for(int i = 0; i < n; ++ i) {
		S += area2(info[i], info[i + 1]) * sign(Cross(info[i], info[i + 1]));
	}
	return fabs(S);
}

Point cherry;
Point a[N], b[N];

void solve() {
	cin >> r >> n;
	for(int i = 0; i < n; ++ i) {
		a[i].read();
		b[i].read();
	}
	cherry.read();
	vector<Point> vec;
	vec.push_back(Point(-r, -r));
	vec.push_back(Point(-r, r));
	vec.push_back(Point(r, r));
	vec.push_back(Point(r, -r));
	for(int i = 0; i < n; ++ i) {
		if (crossOp(a[i], b[i], cherry) < 0)
			swap(a[i], b[i]);
		vec = convecCut(vec, a[i], b[i]);
	}
	n = vec.size();
	for(int i = 0; i < n; ++ i) {
		info[i] = vec[i];
	}
	info[n] = info[0];

	double ret = area() / (PI * r * r);
	printf("%.5f%%\n", ret * 100);
}

int main() {
	int test;
	cin >> test;
	for(int i = 1; i <= test; ++ i) {
		cout << "Case " << i << ": ";
		solve();
	}
}
