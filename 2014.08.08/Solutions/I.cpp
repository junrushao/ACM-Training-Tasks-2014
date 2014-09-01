#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 2005;

struct Point {
	double x, y;

	Point (double x = 0, double y = 0) : x(x), y(y) {}

	void in() {
		scanf("%lf%lf", &x, &y);
	}

	double len() {
		return sqrt(len2());
	}

	double len2() {
		return x * x + y * y;
	}

	Point rotate(double ang) {
		return Point(x * cos(ang) - y * sin(ang),
					 x * sin(ang) + y * cos(ang));
	}

	double ang() {
		return atan2(y, x);
	}
};

inline double sqr(const double &x) {
	return x * x;
}

Point operator - (const Point &a, const Point &b) {
	return Point(a.x - b.x, a.y - b.y);
}

Point operator + (const Point &a, const Point &b) {
	return Point(a.x + b.x, a.y + b.y);
}

Point operator * (const Point &a, const double &k) {
	return Point(a.x * k, a.y * k);
}

Point operator / (const Point &a, const double &k) {
	return Point(a.x / k, a.y / k);
}

double det(const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}

struct Center {
	Point p;
	double sumw;

	Center (Point p = Point(0, 0), double sumw = 0) : p(p), sumw(sumw) {}

	Point getp() {
		return p / sumw;
	}
};

Center rCenter(const Point &p, const double &s) {
	return Center(p * s, s);	
}

Center operator + (const Center &a, const Center &b) {
	return Center(a.p + b.p, a.sumw + b.sumw);	
}

Center operator - (const Center &a, const Center &b) {
	return Center(a.p - b.p, a.sumw - b.sumw);
}

Center caltri(const Point &a, const Point &b, const Point &c) {
	return rCenter((a + b + c) / 3, det(b - a, c - a) / 2);
}

Center caltriABS(const Point &a, const Point &b, const Point &c) {
	return rCenter((a + b + c) / 3, fabs(det(b - a, c - a)) / 2);
}

const double PI = acos(-1);

struct Circle {
	Point o;
	double r;

	Circle (Point o = Point(0, 0), double r = 0) : o(o), r(r) {}
};

Center calcir(const Circle &c) {
	return rCenter(c.o, c.r * c.r * PI);
}

inline int sign(double x, double eps = 1e-8) {
	return x < -eps ? -1 : x > eps;
}

Center calfan(const Circle &c, const double &ang1, const double &ang2) {
	double dang = ang2 - ang1, mang = (ang1 + ang2) / 2;
	if (sign(dang) < 0) {
		dang += PI * 2;
		mang += PI;
	}
	if (sign(dang) == 0) {
		return Center(Point(0, 0), 0);
	}
	double r = c.r, d = 4 * r * sin(dang / 2) / (3 * dang);
	return rCenter(c.o + Point(cos(mang), sin(mang)) * d, r * r * dang / 2);
}

struct Tevent {
	Point p;
	double ang;
	int add;

	Tevent(Point p = Point(0, 0), double ang = 0, int add = 0) : p(p), ang(ang), add(add) {}

	bool operator < (const Tevent &a) const {
		return ang < a.ang;
	}
} eve[maxn * 2];

int E, cnt;

void circleCrossCircle (const Circle &a, const Circle &b) {
	double l = (a.o - b.o).len2();
	double s = ((a.r - b.r) * (a.r + b.r) / l + 1) * .5;
	double t = sqrt(-(l - sqr(a.r - b.r)) * (l - sqr(a.r + b.r)) / (l * l * 4));
	Point dir = b.o - a.o;
	Point Ndir = Point(-dir.y, dir.x);
	Point aa = a.o + dir * s + Ndir * t;
	Point bb = a.o + dir * s - Ndir * t;
	double A = atan2(aa.y - a.o.y, aa.x - a.o.x);
	double B = atan2(bb.y - a.o.y, bb.x - a.o.x);
	eve[E++] = Tevent(bb, B, 1);
	eve[E++] = Tevent(aa, A, -1);
	if (B > A) {
		cnt++;
	}
}

bool g[maxn][maxn];
Center cen[maxn];
Circle c[maxn];
int C;

Center solve() {
	for (int i = 0; i <= C; ++i) cen[i] = Center(Point(0, 0), 0);
	for (int i = 0; i < C; ++i) {
		E = 0;
		cnt = 1;
		for (int j = 0; j < C; ++j) {
			if (i != j && g[i][j]) {
				circleCrossCircle(c[i], c[j]);
			}
		}
		if (E == 0) {
			cen[cnt] = cen[cnt] + calcir(c[i]);
		} else {
			double counts = 0;
			sort(eve, eve + E);
			eve[E] = eve[0];
			for (int j = 0; j < E; ++j) {
				cnt += eve[j].add;
				cen[cnt] = cen[cnt] + caltri(Point(0, 0), eve[j].p, eve[j + 1].p);
				double theta = eve[j + 1].ang - eve[j].ang;
				if (theta < 0) {
					theta += PI * 2;
				}
				cen[cnt] = cen[cnt] + calfan(c[i], eve[j].ang, eve[j + 1].ang) - caltri(c[i].o, c[i].o + Point(cos(eve[j].ang), sin(eve[j].ang)) * c[i].r,
				c[i].o + Point(cos(eve[j + 1].ang), sin(eve[j + 1].ang)) * c[i].r);
			}
		}
	}
	return cen[1];
}

bool overlap(const Circle &a, const Circle &b) {
	return sign(a.r - b.r - (a.o - b.o).len()) >= 0;
}

bool intersect(const Circle &a, const Circle &b) {
	return sign((a.o - b.o).len() - a.r - b.r) < 0;
}

bool issame(const Circle &a, const Circle &b) {
	return sign(a.o.x - b.o.x) == 0 && sign(a.o.y - b.o.y) == 0 && sign(a.r - b.r) == 0;
}

Center calpoly(vector<Point> &p) {
	Center ret;
	p.push_back(p.front());
	for (int i = 0; i + 1 < (int)p.size(); ++i) {
		ret = ret + caltri(Point(0, 0), p[i], p[i + 1]);
	}
	return ret;
}

int n, m, p;

int main() {
	while (scanf("%d%d%d", &n, &m, &p) == 3) {
		vector<Point> poly(n);
		for (int i = 0; i < n; ++i) {
			poly[i].in();
		}
		Center ans = calpoly(poly);
		vector<Circle> cc(m);
		for (int i = 0; i < m; ++i) {
			cc[i].o.in();
			scanf("%lf", &cc[i].r);
		}
		C = 0;
		for (int i = 0; i < m; ++i) {
			bool flag = false;
			for (int j = 0; j < m && !flag; ++j) {
				if (i == j) {
					continue;
				}
				if (issame(cc[i], cc[j]) && i > j ||
					!issame(cc[i], cc[j]) && overlap(cc[j], cc[i])) {
					flag = true;
				}
			}
			if (!flag) {
				c[C++] = cc[i];
			}
		}
		for (int i = 0; i < C; ++i) {
			for (int j = 0; j < C; ++j) {
				g[i][j] = intersect(c[i], c[j]);
			}
		}
		Center ans2 = solve();
		Point cen = (ans - ans2).getp();
		--p;
		double ang = -((cen - poly[p]).ang() + PI / 2);
		for (int i = 0; i < n; ++i) {
			poly[i] = (poly[i] - poly[p]).rotate(ang) + poly[p];
			printf("%.12f %.12f\n", poly[i].x, poly[i].y);
		}
	}
	return 0;
}
