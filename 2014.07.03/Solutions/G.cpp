#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define sqr(x) ((x) * (x))
using namespace std;

struct Point {
	int x, y;
	Point (int _x = 0, int _y = 0) : x(_x), y(_y) {}
	Point operator - (const Point &p) const {
		return Point(x - p.x, y - p.y);
	}
	int operator ^ (const Point &p) const {
		return x * p.y - y * p.x; 
	}
	int operator * (const Point &p) const {
		return x * p.x + y * p.y;
	}
} point[10];

bool cmp(Point a, Point b) {
	return atan2(a.y, a.x) < atan2(b.y, b.x);
}

bool par(int a1, int a2, int b1, int b2) {
	if (((point[a1] - point[a2]) ^ (point[b1] - point[b2])) == 0) return true;
	else return false;
} 

int dis(int a, int b) {
	return sqr(point[a].x - point[b].x) + sqr(point[a].y - point[b].y);
}

int TT;
int type;

int main(){
	cin >> TT;
	for (int T = 1; T <= TT; ++T) {
		for (int i = 0; i < 4; ++i) scanf("%d %d", &point[i].x, &point[i].y);
		for (int i = 3; i >= 0; --i) point[i].x -= point[0].x, point[i].y -= point[0].y;
		sort(point + 1, point + 4, cmp);
		type = 0;
		if (par(0, 1, 2, 3) && par(0, 3, 1, 2)) {
			bool is3, is4;
			if (dis(0, 1) == dis(1, 2)) is3 = true;
			else is3 = false;
			if ((point[1] - point[0]) * (point[3] - point[0]) == 0) is4 = true;
			else is4 = false;
			if (is3 && is4) type = 5;
			else if (is4) type = 4;
			else if (is3) type = 3;
			else type = 2;
		}
		else if (par(0, 1, 2, 3) || par(0, 3, 1, 2)) type = 1;
		else type = 0;
		printf("Case %d: ", T);
		if (type == 5) puts("Square");
		else if (type == 4) puts("Rectangle");
		else if (type == 3) puts("Rhombus");
		else if (type == 2) puts("Parallelogram");
		else if (type == 1) puts("Trapezium");
		else if (type == 0) puts("Ordinary Quadrilateral");
	}
	return	0;
}
