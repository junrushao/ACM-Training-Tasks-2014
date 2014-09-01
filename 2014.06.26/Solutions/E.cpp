/*
 * 1.cpp
 *
 *  Created on:
 *      Author:
 */

#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <climits>
#include <cassert>

#include <iostream>
#include <sstream>

#include <string>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <bitset>

#include <utility>
#include <numeric>
#include <functional>
#include <algorithm>

#define INF 1000000000
#define LL_INF 4000000000000000000ll

#define Lowbit(x) ((x) & (-(x)))
#define Lc(x) ((x) << 1)
#define Rc(x) (Lc(x) + 1)
#define Pow2(x) (1 << (x))
#define Contain(a, x) (((a) >> (x)) & 1)

#define Rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define Til(i, a, b) for(int i = (a); i >= (b); --i)
#define Foru(i, a, b) for(int i = (a); i < (b); ++i)
#define Ford(i, a, b) for(int i = (a); i > (b); --i)

#define It iterator
#define For(i, x) for(__typeof(x.begin()) i = x.begin(); i != x.end(); ++i)

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int, int> pii;
typedef vector<int> VI;
typedef vector<string> VS;

//inline int rand(int a, int b) { return rand() % (b - a + 1) + a; }

template <class T> inline bool Up(T &a, const T &b) { if(a < b) {a = b; return true;} return false; }
template <class T> inline bool Down(T &a, const T &b) { if(a > b) {a = b; return true;} return false; }

inline int getus() { int tmp, c; while(tmp = fgetc(stdin), tmp < '0' || tmp > '9'); tmp -= '0'; while(c = fgetc(stdin), '0' <= c && c <= '9') tmp = tmp * 10 + c - '0'; return tmp; }
inline int getint() { int tmp, c, flag; while(flag = fgetc(stdin), flag != '-' && (flag < '0' || flag > '9')); if(flag == '-') tmp = 0; else tmp = flag - '0'; while(c = fgetc(stdin), '0' <= c && c <= '9') tmp = tmp * 10 + c - '0'; return flag == '-' ? -tmp : tmp; }


#define MAXN 1033

const double eps = 1e-8;

inline int sign(double a) {
	if (a < -eps) return -1;
	if (a > eps) return 1;
	return 0;
}

struct point {
	double x, y;
	point(): x(0), y(0) {}
	point(double a, double b): x(a), y(b) {}
	point operator - (const point &b) const {
		return point(x - b.x, y - b.y);
	}
	point operator + (const point &b) const {
		return point(x + b.x, y + b.y);
	}
//	double operator * (const point &b) const {
//		return x * b.y - y * b.x;
//	}
	point operator * (const double &k) const {
		return point(x * k, y * k);
	}
} P[MAXN];

inline double det(const point &a, const point &b) {
	return a.x * b.y - b.x * a.y;
}

inline bool lineIntersect(const point &a, const point &b, const point &c, const point &d, point &e) {
	double s1 = det(c - a, d - a);
	double s2 = det(d - b, c - b);
	if (!sign(s1 + s2) ) return 0;
	e = (b - a) * (s1 / (s1 + s2)) + a;
	return 1;
}

struct polygon {
	point list[MAXN];
	int n;
	
	polygon(): n(0) {
	}

	polygon(const polygon &a) {
		n = a.n;
		Foru(i, 0, n) list[i] = a.list[i];
	}

	polygon operator = (const polygon &a) {
		if (this != &a) {
			n = a.n;
			Foru(i, 0, n) list[i] = a.list[i];
		}
		return *this;
	}

	polygon cut(const point &a, const point &b) {
		static polygon res;
		point curr;
		
		res.n = 0;
		Foru(i, 0, n) {
			int s1 = sign(det(list[i] - a, b - a));
			int s2 = sign(det(list[(i + 1) % n] - a, b - a));
			if (s1 <= 0) res.list[res.n++] = list[i];
			if (s1 * s2 < 0) {
				lineIntersect(a, b, list[i], list[(i + 1) % n], curr);
				res.list[res.n++] = curr;
			}
		}
		return res;
	}
	
	double area() const {
		if (n <= 2) return 0.0;
		double ans = 0;
		Foru(i, 0, n)
			ans += det(list[i], list[(i + 1) % n]);
		return fabs(ans * 0.5);
	}
};

double xLast = 0.0, yLast = 0.0;
double xNow, yNow;
double lastArea = 100.0;
char line[1333];
polygon p;

void output(double x) {
	if (x < 0.001)
		puts("0.00");
	else {
		printf("%.2f\n", x);
	}
}

void solve() {
	if ((xNow == xLast && yNow == yLast) || lastArea < 0.001) {
		output(lastArea);
		return;
	}
	if (strcmp(line, "Same") == 0) {
		output(lastArea = 0);
		xLast = xNow;
		yLast = yNow;
		return;
	}
	double x0 = (xNow + xLast) * 0.5;
	double y0 = (yNow + yLast) * 0.5;
	double x1 = (yNow - yLast) * 0.5;
	double y1 = (xLast - xNow) * 0.5;
	if (strcmp(line, "Hotter") == 0) {
		p = p.cut(point(x0, y0), point(x0 + x1, y0 + y1));
	}
	else {
		p = p.cut(point(x0, y0), point(x0 - x1, y0 - y1));
	}
	output(lastArea = p.area());
//	Foru(i, 0, p.n) printf("(%.2f, %.2f)\n", p.list[i].x, p.list[i].y);

	xLast = xNow;
	yLast = yNow;
}

void init() {
	p.n = 4;
	p.list[0] = point(0, 0);
	p.list[1] = point(10, 0);
	p.list[2] = point(10, 10);
	p.list[3] = point(0, 10);
}

int main() {
	init();
	while (scanf("%lf %lf %s", &xNow, &yNow, line) == 3) solve();
	return 0;
}
