#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>
#include<vector>

using namespace std;

const double eps = 1e-8;
const int MaxN = 10 + 2;
const double pi = acos(-1.0);

#define sqr(x) ((x) * (x))

struct Point {
	double x, y;	
	Point() {}
	Point(double _x, double _y): x(_x), y(_y) {}
	void load() {
		scanf("%lf%lf", &x, &y);
	}
	bool operator == (const Point &t) const {
		return fabs(x - t.x) < eps && fabs(y - t.y) < eps;
	}
	bool operator < (const Point &t) const {
		if (fabs(x - t.x) < eps) return y < t.y;
		return x < t.x;
	}
	Point operator + (const Point &t) const {
		return Point(x + t.x, y + t.y);
	}
	Point operator - (const Point &t) const {
		return Point(x - t.x, y - t.y);
	}
	Point operator * (double t) const {
		return Point(x * t, y * t);
	}
	Point operator / (double t) const {
		return Point(x / t, y / t);
	}
	double norm() const {
		return sqrt(sqr(x) + sqr(y));
	}
	double dis(const Point &t) const {
		return sqrt(sqr(x - t.x) + sqr(y - t.y));
	}
	Point normalize() const {
		double t = norm();
		return *this / t;
	}
	Point turn() const {
		return Point(-y, x);
	}
	void out() const {
		printf("%.8f %.8f\n", x, y);	
	}
}stars[MaxN];

struct Circle {
	Point o; double r;
	Circle() {}
	Circle(Point _o, double _r): o(_o), r(_r) {}
	bool contains(const Point &t) const {
		return t.dis(o) < r + eps;
	}
	bool intersected(const Circle &t) const {
		if (o == t.o && fabs(r - t.r) < eps) return false;
		double d = o.dis(t.o);
		return d > fabs(r - t.r) - eps && d < r + t.r + eps;
	}
	Point intersect(const Circle &t) const {
		double d = o.dis(t.o);
		double x = 0.5 * ((sqr(r) - sqr(t.r)) / d + d);
		double h = sqrt(sqr(r) - sqr(x));
		return (o * (d - x) + t.o * x) / d + (t.o - o).turn().normalize() * h;
	}
}circles[MaxN][MaxN][2];

int N, tag;

void add(int t1, int t2, double ang) {
	Point a = stars[t1], b = stars[t2];
	if (ang > pi / 2) ang = pi - ang;
	double half = a.dis(b) / 2.0;
	double t = half / tan(ang);
	double R = half / sin(ang);
	Point dir = (b - a).turn().normalize();
	circles[t1][t2][0] = Circle((a + b) / 2 + dir * t, R);
	circles[t1][t2][1] = Circle((a + b) / 2 - dir * t, R);
}

vector<Circle> List;
vector<Point> Pts;

void getPts() {
	Pts.clear();
	for (int i = 0; i < (int)List.size(); ++i) 
		for (int j = i + 1; j < (int)List.size(); ++j)
			if (List[i].intersected(List[j])) {
				Pts.push_back(List[i].intersect(List[j]));
				Pts.push_back(List[j].intersect(List[i]));
			}
	sort(Pts.begin(), Pts.end());
	Pts.resize(unique(Pts.begin(), Pts.end()) - Pts.begin());
}

bool judgeInside(Point now) {
	for (int i = 0; i < N; ++i)
		if (now.dis(stars[i]) < 1 - eps) return false;
	if (tag) {
		for (int i = 0; i < N; ++i)
			for (int j = i + 1; j < N; ++j)
				if (circles[i][j][0].contains(now) && circles[i][j][1].contains(now))
					continue;
				else return false;
	}
	else {
		for (int i = 0; i < N; ++i)
			for (int j = i + 1; j < N; ++j)
				if (circles[i][j][0].contains(now) || circles[i][j][1].contains(now))
					continue;
				else return false;
	}
	return true;
}

Point Ans;

bool check() {
	for (int i = 0; i < (int)Pts.size(); ++i) 
		if (judgeInside(Pts[i])) {
			Ans = Pts[i];
			return true;
		}
	return false;
}

int main() {

	scanf("%d", &N);	
	for (int i = 0; i < N; ++i) 
		stars[i].load();
	for (int i = 0; i < N; ++i)
		for (int j = i + 1; j < N; ++j) {
			if (stars[i] == stars[j]) {
				Point(100000.0, 100000.0).out();
				return 0;
			}
		}
	if (N == 2) {
		((stars[0] + stars[1]) / 2.0).out();
		return 0;
	}
	double l = eps, r = pi - eps, mid;
	while (l + eps < r) {
		mid = (l + r) / 2;
		if (mid > pi / 2) tag = 1;
		else tag = 0;
		List.clear();
		for (int i = 0; i < N; ++i)
			for (int j = i + 1; j < N; ++j) {
				add(i, j, mid);
				List.push_back(circles[i][j][0]);
				List.push_back(circles[i][j][1]);
			}
		for (int i = 0; i < N; ++i) 
			List.push_back(Circle(stars[i], 1));
		getPts();
		if (check()) l = mid; else r = mid;
	}
	Ans.out();

	return 0;

}
