#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long double LD;

int n;

struct Point {
	LD x, y;

	Point (LD x = 0, LD y = 0) : x(x), y(y) {}

	void in() {
		cin >> x >> y;
	}

	LD len() {
		return sqrt(x * x + y * y);
	}

	Point rotate(LD ang) {
		return Point(x * cos(ang) - y * sin(ang),
		 			 x * sin(ang) + y * cos(ang));
	}
};

Point operator - (const Point &a, const Point &b) {
	return Point(a.x - b.x, a.y - b.y);
}

Point operator + (const Point &a, const Point &b) {
	return Point(a.x + b.x, a.y + b.y);
}

inline int sign(LD x, LD eps = 1e-9) {
	return x < -eps ? -1 : x > eps;
}

const LD PI = acos((LD)-1);

const int N = 105;
Point p[N];

bool check(Point delta, LD ang) {
	Point q = p[0];
	for (int i = 0; i < n; ++i) {
		if (sign((p[i] - q).len()) != 0) {
			return false;
		}
		q = q + delta;
		delta = delta.rotate(ang);
	}
	return true;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		p[i].in();
	}
	Point delta = (p[1] - p[0]);
	if (check(delta, 2 * PI / n) || check(delta, -2 * PI / n)) {
		puts("YES");
	} else {
		puts("NO");
	}
	return 0;
}

