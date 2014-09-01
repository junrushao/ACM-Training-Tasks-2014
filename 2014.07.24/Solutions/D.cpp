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

const double EPS = 1e-8;
const double PI = acos(-1.);

int sign(double x)
{
	return x < -EPS ? -1 : x > EPS;
}

struct Point
{
	double x, y;

	Point() {}
	Point(double x, double y) : x(x), y(y) {}

	void read() {
		scanf("%lf%lf", &x, &y);
	} 
	void write() {
		printf("%.10f %.10f\n", x, y);
	}
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

	Point rot90() {
		return Point(-y, x);
	}
	double abs() {
		return hypot(y, x);
	}
	double abs2() {
		return x * x + y * y;
	}
	double distTo(const Point &that) const {
		return (*this - that).abs();
	}
	Point unit() {
		return *this / abs();
	}
};

#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))

Point isSS(Point p1, Point p2, Point q1, Point q2)
{
	double a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return (p1 * a2 + p2 * a1) / (a1 + a2);
}

vector<Point> intersectionLineToCircle(Point c, double r, Point l1, Point l2)
{
	Point c2 = c + (l2 - l1).rot90();
	c2 = isSS(c, c2, l1, l2);
	double t = sqrt(max(0.0, r * r - (c2 - c).abs2()));
	Point p1 = c2 + (l2 - l1).unit() * t;
	Point p2 = c2 - (l2 - l1).unit() * t;
	vector<Point> ret;
	ret.push_back(p1); ret.push_back(p2);
	return ret;
}

vector<Point> intersectionCircleToCircle(Point c1, double r1, Point c2, double r2)
{
	double t = (1 + (r1 * r1 - r2 * r2) / (c1 - c2).abs2()) / 2;
	Point u = c1 + (c2 - c1) * t;
	Point v = u + (c2 - c1).rot90();
	return intersectionLineToCircle(c1, r1, u, v);
}

int isIntersectCircleToCircle(Point c1, double r1, Point c2, double r2)
{
	double dis = c1.distTo(c2);
	return sign(dis - abs(r1 - r2)) >= 0 && sign(dis - (r1 + r2)) <= 0;
}

double r;
Point c, w1, w2;
Point ret1, ret2;

int checkOk(Point c1, Point c2)
{
	int f1 = sign(c1.distTo(c) - r) <= 0;
	int f2 = sign(c2.distTo(c) - r) <= 0;
	if (sign(c1.distTo(c2) - r) <= 0) {
		f1 |= f2;
		f2 |= f1;
	}
	int v1 = (sign(w1.distTo(c1) - r) <= 0 && f1) || (sign(w1.distTo(c2) - r) <= 0 && f2);
	int v2 = (sign(w2.distTo(c1) - r) <= 0 && f1) || (sign(w2.distTo(c2) - r) <= 0 && f2);
	return v1 && v2;
}

int solve() {
	cin >> r;
	c.read();
	w1.read();
	w2.read();

	double d1 = w1.distTo(c);
	double d2 = w2.distTo(c);
	if (sign(d1 - 2 * r) <= 0 && sign(d2 - 2 * r) <= 0) {
		ret1 = (c + w1) * 0.5;
		ret2 = (c + w2) * 0.5;
		return true;
	}
	if (sign(d1 - 3 * r) > 0 || sign(d2 - 3 * r) > 0) {
		return false;
	}
	if (d1 < d2) {
		swap(d1, d2);
		swap(w1, w2);
	}

	vector<Point> tmp;
	vector<pair<Point, Point> > vec;
	if ((w1.distTo(w2) - 2 * r) <= 0) {
		tmp = intersectionCircleToCircle(w1, r, w2, r);
		vec.push_back(make_pair(tmp[0], (tmp[0] + c) * 0.5));
		vec.push_back(make_pair(tmp[1], (tmp[1] + c) * 0.5));
		if (isIntersectCircleToCircle(w1, r, c, 2 * r)) {
			tmp = intersectionCircleToCircle(w1, r, c, 2 * r);
			vec.push_back(make_pair(tmp[0], (tmp[0] + c) * 0.5));
			vec.push_back(make_pair(tmp[1], (tmp[1] + c) * 0.5));
		}
		if (isIntersectCircleToCircle(w2, r, c, 2 * r)) {
			tmp = intersectionCircleToCircle(w2, r, c, 2 * r);
			vec.push_back(make_pair(tmp[0], (tmp[0] + c) * 0.5));
			vec.push_back(make_pair(tmp[1], (tmp[1] + c) * 0.5));
		}
	}
	if ((w2.distTo(c) - 2 * r) <= 0) {
		tmp = intersectionCircleToCircle(w2, r, c, r);
		vec.push_back(make_pair(tmp[0], (tmp[0] + w1) * 0.5));
		vec.push_back(make_pair(tmp[1], (tmp[1] + w1) * 0.5));
		if (isIntersectCircleToCircle(c, r, w1, 2 * r)) {
			tmp = intersectionCircleToCircle(c, r, w1, 2 * r);
			vec.push_back(make_pair(tmp[0], (tmp[0] + w1) * 0.5));
			vec.push_back(make_pair(tmp[1], (tmp[1] + w1) * 0.5));
		}
		if (isIntersectCircleToCircle(w2, r, w1, 2 * r)) {
			tmp = intersectionCircleToCircle(w2, r, w1, 2 * r);
			vec.push_back(make_pair(tmp[0], (tmp[0] + w1) * 0.5));
			vec.push_back(make_pair(tmp[1], (tmp[1] + w1) * 0.5));
		}
	}
	for(int i = 0; i < (int)vec.size(); ++ i) {
		if (checkOk(vec[i].first, vec[i].second)) {
			ret1 = vec[i].first;
			ret2 = vec[i].second;
			return true;
		}
	}
	return false;
}

int main() {
	if (solve()) {
		cout << "Now we have enough power" << endl;
		ret1.write();
		ret2.write();
		return 0;
	}
	cout << "Death" << endl;
	return 0;
}
