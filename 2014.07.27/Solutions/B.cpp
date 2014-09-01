#include <deque>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long double DOUBLE;

const DOUBLE INF = 2e15;

const DOUBLE eps = 1e-9;

struct Point {
	DOUBLE x, y;

	Point(DOUBLE x = 0, DOUBLE y = 0) : x(x), y(y) {}

	DOUBLE ang() {
		return atan2(y, x);
	}

	DOUBLE len() {
		return sqrt(x * x + y * y);
	}

	DOUBLE len2() {
		return x * x + y * y;
	}
};

Point operator - (const Point &a, const Point &b) {
	return Point(a.x - b.x, a.y - b.y);
}

Point operator * (const Point &a, const DOUBLE &k) {
	return Point(a.x * k, a.y * k);
}

Point operator / (const Point &a, const DOUBLE &k) {
	return Point(a.x / k, a.y / k);
}

DOUBLE det(const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}

DOUBLE dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}

inline int sign(const DOUBLE &x, const DOUBLE EPS = eps) {
	return x < -EPS? -1 : x > EPS;
}

inline int getint() {
	char ch;
	while (!isdigit(ch = getchar())) {
		if (ch == '-') {
			break;
		}
		continue;
	}
	bool flag = ch == '-';
	int ret = 0;
	if (ch != '-') {
		ret = ch - '0';
	}
	while (isdigit(ch = getchar())) {
		ret = ret * 10 + ch - '0';
	}
	return flag ? -ret : ret;
}

struct Line {
	Point a, b;

	DOUBLE ang, dis;

	Line(Point a = Point(0, 0), Point b = Point(0, 0)) : a(a), b(b) {}

	void in() {
		double a0 = getint(), b0 = getint(), c0 = getint();
		a = Point(0, -c0 / b0);	
		b = Point(5e4, (-c0 - a0 * 5e4) / b0);
	}

	void setangdis(const Point &p) {
		if (!include(p)) {
			swap(a, b);
		}
		ang = (b - a).ang();
		dis = det(b - a, p - a) / (b - a).len();
	}

	bool include(const Point &p) const {
		return sign(det(b - a, p - a)) > 0;		
	}
};

Point intersect(const Line &a, const Line &b) {
	DOUBLE s1 = det(a.b - a.a, b.a - a.a),
		   s2 = det(a.b - a.a, b.b - a.a);
	return (b.a * s2 - b.b * s1) / (s2 - s1);
}

const int N = 2 * 100005;

int n;

Line l[N];

int ord[N];

inline bool cmp(const Line &a, const Line &b) {
	if (sign(a.ang - b.ang) != 0) {
		return a.ang < b.ang;
	} else {
		return a.dis < b.dis;
	}
}

bool cmpz(const int &a, const int &b) {
	return cmp(l[a], l[b]);
}

bool check(const int &u, const int &v, const int &w) {
	return l[w].include(intersect(l[u], l[v]));
}

bool operator < (const Point &a, const Point &b) {
	if (sign(a.x - b.x) != 0) {
		return a.x < b.x;
	}
	return a.y < b.y;
}

vector<Point> build(const Point &O) {
	for (int i = 0; i < n; ++i) {
		l[i].setangdis(O);
	}
	sort(ord, ord + n, cmpz);
	deque<int> q;
	for (int _ = 0; _ <	n; ++_) {
		int i = ord[_];
		if (_ && sign(l[i].ang - l[ord[_ - 1]].ang) == 0) {
			continue;
		}
		while (q.size() > 1 && !check(q[q.size() - 2], q[q.size() - 1], i)) {
			q.pop_back();
		}
		while (q.size() > 1 && !check(q[1], q[0], i)) {
			q.pop_front();
		}
		q.push_back(i);
	}
	while (q.size() > 2 && !check(q[q.size() - 2], q[q.size() - 1], q.front())) {
		q.pop_back();
	}
	while (q.size() > 2 && !check(q[1], q[0], q.back())) {
		q.pop_front();
	}
	vector<Point> ret;
	for (int i = 0; i < (int)q.size(); ++i) {
		ret.push_back(intersect(l[q[i]], l[q[(i + 1) % (int)q.size()]]));
	}
	sort(ret.begin(), ret.end());
	return ret;
}

DOUBLE sqr(const DOUBLE &x) {
	return x * x;
}

DOUBLE dis(const Line &l, const Point &p) {
	if (sign(dot(p - l.a, l.b - l.a)) >= 0 && sign(dot(p - l.b, l.a - l.b)) >= 0) {
		return sqr(det(p - l.a, l.b - l.a)) / (l.b - l.a).len2();
	}
	return min((p - l.a).len2(), (p - l.b).len2());
}

DOUBLE dist(const vector<Point> &a, const vector<Point> &b) {
	int n = a.size(), m = b.size();
	DOUBLE ret = 1e100;
	int j = 0;
	{
		DOUBLE cur = 1e100;
		for (int i = 0; i < m; ++i) {
			DOUBLE now = dis(Line(b[j], b[(j + 1) % m]), a[0]);
			if (now < cur) {
				cur = now;
				j = i;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		DOUBLE cur = dis(Line(b[j], b[(j + 1) % m]), a[i]);
		do {
			DOUBLE next = dis(Line(b[(j + 1) % m], b[(j + 2) % m]), a[i]);
			if (sign(next - cur, 1e-6) <= 0) {
				cur = next;
				j = (j + 1) % m;
			} else {
				break;
			}
		} while (true);
		ret = min(ret, cur);
	}
	return ret;
}

Point I = Point(0, 1e10), F = Point(0, -1e10);

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			l[i].in();
		}
		l[n] = Line(Point(0, INF), Point(1, INF));
		l[n + 1] = Line(Point(0, -INF), Point(1, -INF));
		l[n + 2] = Line(Point(-INF, 0), Point(-INF, 1));
		l[n + 3] = Line(Point(INF, 0), Point(INF, 1));
		n += 4;
		for (int i = 0; i < n; ++i) {
			ord[i] = i;
		}
		vector<Point> a = build(I), b = build(F);
		printf("%.12f\n", (double)min(dist(a, b), dist(b, a)));
	}
	return 0;
}
