#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 105;

struct Point {
	double x, y;

	Point (double x = 0, double y = 0) : x(x), y(y) {}
	
	void in() {
		scanf("%lf%lf", &x, &y);
	}

	double len() {
		return sqrt(x * x + y * y);
	}

	double len2() {
		return x * x + y * y;
	}

	double ang() {
		return atan2(y, x);
	}

	Point rotate(double ang) {
		return Point(x * cos(ang) - y * sin(ang),
					 x * sin(ang) + y * cos(ang));
	}
};

Point operator + (const Point &a, const Point &b) {
	return Point(a.x + b.x, a.y + b.y);
}

Point operator - (const Point &a, const Point &b) {
	return Point(a.x - b.x, a.y - b.y);
}

Point operator * (const Point &a, const double &k) {
	return Point(a.x * k, a.y *k);
}

Point operator / (const Point &a, const double &k) {
	return Point(a.x / k, a.y / k);
}

double det (const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}

inline double sqr(const double &x) {
	return x * x;
}

inline int sign(const double &x, const double eps = 1e-9) {
	return x < -eps ? -1 : x > eps;
}

const double PI = acos(-1);

struct Circle {
	Point o;
	double r;

	Circle (Point o = Point(0, 0), double r = 0) : o(o), r(r) {}
};

struct Event {
	Point p;
	double ang;
	int delta;

	Event (Point p = Point(0, 0), double ang = 0, double delta = 0) : p(p), ang(ang), delta(delta) {}
};

bool operator < (const Event &a, const Event &b) {
	return a.ang < b.ang;
}

void addEvent(const Circle &a, const Circle &b, vector<Event> &evt, int &cnt) {
	double d2 = (a.o - b.o).len2(),
				dRatio = ((a.r - b.r) * (a.r + b.r) / d2 + 1) / 2,
				pRatio = sqrt(-(d2 - sqr(a.r - b.r)) * (d2 - sqr(a.r + b.r)) / (d2 * d2 * 4));
	Point d = b.o - a.o, p = d.rotate(PI / 2),
		  q0 = a.o + d * dRatio + p * pRatio,
		  q1 = a.o + d * dRatio - p * pRatio;
	double ang0 = (q0 - a.o).ang(),
		   ang1 = (q1 - a.o).ang();
	evt.push_back(Event(q1, ang1, 1));
	evt.push_back(Event(q0, ang0, -1));
	cnt += ang1 > ang0;
}

bool issame(const Circle &a, const Circle &b) {
	return sign((a.o - b.o).len()) == 0 && sign(a.r - b.r) == 0;
}

bool overlap(const Circle &a, const Circle &b) {
	return sign(a.r - b.r - (a.o - b.o).len()) >= 0;
}

bool intersect(const Circle &a, const Circle &b) {
	return sign((a.o - b.o).len() - a.r - b.r) < 0;
}

int C;
Circle c[N];
double area[N];

void solve() {
	memset(area, 0, sizeof(double) * (C + 1));
	for (int i = 0; i < C; ++i) {
		int cnt = 1;
		vector<Event> evt;
		for (int j = 0; j < i; ++j) {
			if (issame(c[i], c[j])) {
				++cnt;
			}
		}
		for (int j = 0; j < C; ++j) {
			if (j != i && !issame(c[i], c[j]) && overlap(c[j], c[i])) {
				++cnt;
			}
		}
		for (int j = 0; j < C; ++j) {
			if (j != i && !overlap(c[j], c[i]) && !overlap(c[i], c[j]) && intersect(c[i], c[j])) {
				addEvent(c[i], c[j], evt, cnt);
			}
		}
		if (evt.size() == 0) {
			area[cnt] += PI * c[i].r * c[i].r;
		} else {
			sort(evt.begin(), evt.end());
			evt.push_back(evt.front());
			for (int j = 0; j + 1 < (int)evt.size(); ++j) {
				cnt += evt[j].delta;
				area[cnt] += det(evt[j].p, evt[j + 1].p) / 2;
				double ang = evt[j + 1].ang - evt[j].ang;
				if (ang < 0) {
				ang += PI * 2;
				}
				area[cnt] += ang * c[i].r * c[i].r / 2 - sin(ang) * c[i].r * c[i].r / 2;
			}
		}
	}
}

Circle makeCircle(const Point &a, const Point &b) {
	return Circle((a + b) / 2, (b - a).len() / 2);
}

int n;

int main() {
	scanf("%d", &n);
	C = n;
	for (int i = 0; i < n; ++i) {
		c[i].o.in();
		scanf("%lf", &c[i].r);
	}
	solve();
	double ans[2] = {0, 0};
	for (int i = 1; i <= n; ++i) {
		double add = area[i] - area[i + 1];
		ans[i & 1] += add;
	}
	printf("%.5f %.5f\n", ans[1], ans[0]);
	return 0;
}
