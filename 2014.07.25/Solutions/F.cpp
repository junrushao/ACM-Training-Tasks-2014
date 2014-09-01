#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

typedef long double DOUBLE;

const DOUBLE PI = acos((DOUBLE)-1.0);
const double EPS = 1e-16;

int n;
struct Point {
	DOUBLE x, y;
	Point(DOUBLE x = 0, DOUBLE y = 0) : x(x), y(y) {}
	inline friend Point operator +(const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	} 
	inline friend Point operator -(const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	inline friend Point operator *(const Point &a, DOUBLE k) {
		return Point(a.x * k, a.y * k);
	}
	inline friend Point operator /(const Point &a, DOUBLE k) {
		return Point(a.x / k, a.y / k);
	} 
	DOUBLE angle() {
		return atan2(y, x);
	}
	
	DOUBLE length() {
		return sqrt(x * x + y * y);
	}
};

vector<Point> points;
DOUBLE ansMax, ansMin, ansMaxAng, ansMinAng;

void update(DOUBLE theta, DOUBLE value) {
	if (value > ansMax) {
		ansMax = value;
		ansMaxAng = theta;
	}
	if (value < ansMin) {
		ansMin = value;
		ansMinAng = theta;
	}
}

DOUBLE fix(DOUBLE t) {
	while (t >= PI) {
		t -= PI;
	}
	while(t <= 0) {
		t += PI;
	}
	
	return t;
}

void solve(DOUBLE x) {
	vector<DOUBLE > pairs;
	for(int i = 0; i < n; i++) {
		DOUBLE pos = points[i].x * cos(x) + points[i].y * sin(x);
		pairs.push_back(pos);
	}
	sort(pairs.begin(), pairs.end());
	DOUBLE result = 2;
	for(int i = 0; i < (int)pairs.size() - 1; i++) {
		result += min((DOUBLE)2.0, pairs[i + 1] - pairs[i]);
	}
	update(x, result);
}

void solve(DOUBLE l, DOUBLE r) {
	DOUBLE x = (l + r) / 2.0;
	vector<pair<DOUBLE, int> > pairs;
	for(int i = 0; i < n; i++) {
		DOUBLE pos = points[i].x * cos(x) + points[i].y * sin(x);
		pairs.push_back(make_pair(pos, i));
	}
	sort(pairs.begin(), pairs.end());
	DOUBLE rightMost = -1e100, leftMost = 1e100;
	DOUBLE a = 0, b = 0, c = 0;
	for(int i = 0; i < n; i++) {
		if (rightMost + 2 < pairs[i].first) {
			a -= points[pairs[i].second].x;
			b -= points[pairs[i].second].y;
		}
		rightMost = pairs[i].first;
	}
	for(int i = n - 1; i >= 0; i--) {
		if (leftMost - 2 > pairs[i].first) {
			a += points[pairs[i].second].x;
			b += points[pairs[i].second].y;
		}
		leftMost = pairs[i].first;
	}
	DOUBLE theta = fix(Point(a, b).angle());
	solve(theta);
}

int main() {
	while(scanf("%d", &n) == 1 && n) {
		points.clear();
		for(int i = 0; i < n; i++) {
			DOUBLE x, y;
			cin >> x >> y;
			points.push_back(Point(x, y));
		}
		
		vector<DOUBLE> angles;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < i; j++) {
				Point delta = points[i] - points[j];
				angles.push_back(fix(delta.angle() + PI / 2.0));
				DOUBLE length = delta.length();
				DOUBLE theta = acos(2. / length);
				angles.push_back(fix(delta.angle() + theta));
				angles.push_back(fix(delta.angle() - theta));
			}
		angles.push_back(0);
		angles.push_back(PI / 2);
		angles.push_back(PI);
		sort(angles.begin(), angles.end());
		ansMinAng = ansMin = 1e100;
		ansMaxAng = ansMax = -1e100;
		for(int i = 0; i < (int)angles.size(); i++) {
			solve(angles[i]);
		}
		for(int i = 0; i < (int)angles.size() - 1; i++) {
			solve(angles[i], angles[i + 1]);
		}
		//cout << ansMaxAng << " " << ansMinAng << endl;
 		printf("%.15f\n%.15f\n", (double)fix(PI - ansMinAng + PI / 2) + EPS, (double)fix(PI - ansMaxAng + PI / 2) + EPS);
	}
	return 0;
}
