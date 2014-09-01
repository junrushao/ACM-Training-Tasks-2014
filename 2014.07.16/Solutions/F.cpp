#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

struct Point {
	int x, y;

	Point (int x = 0, int y = 0) : x(x), y(y) {};

	void in() {
		scanf("%d%d", &x, &y);
	}
};

Point operator - (Point a, Point b) {
	return Point(a.x - b.x, a.y - b.y);
}

int det(Point a, Point b) {
	return a.x * b.y - a.y * b.x;
}

int sign(int x) {
	return x < 0 ? -1 : x > 0;
}

bool cross(Point a, Point b, Point c, Point d) {
	if (sign(det(b - a, c - a)) != sign(det(b - a, d - a)) &&
		sign(det(d - c, b - c)) != sign(det(d - c, a - c))) {
		return true;
	}
	return false;
}

double dist(Point a, Point b) {
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

Point p[4];

int main() {
	int x1, y1, x2, y2;
	while (scanf("%d%d%d%d", &x1, &y1, &x2, &y2) == 4 && x1) {
		p[0] = Point(x1, y1), p[1] = Point(x2, y2);
		p[2].in(), p[3].in();
		double dis = 0;
		if (cross(p[0], p[1], p[2], p[3])) {
			dis = min(dist(p[0], p[2]) + dist(p[1], p[2]), dist(p[0], p[3]) + dist(p[1], p[3]));
		} else {
			dis = dist(p[0], p[1]);
		}
		dis /= 2;
		static int id = 0;
		printf("Case %d: %.3f\n", ++id, dis);
	}
	return 0;
}
