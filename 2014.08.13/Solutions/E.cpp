#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <ctime>
#include <cmath>
#include <set>
#include <map>
#include <queue>

#define foreach(it,e) for (__typeof(e.begin ()) it = e.begin(); it != e.end(); it++)

#define sqr(x) ((x) * (x))
#define abs(x) (((x) > 0) ? (x) : (-(x))) 
#define lowbit(x) ((x) & (-(x)))

using namespace std;

typedef long long i64;
typedef unsigned long long u64;
typedef double dbl;

#define point ____point

struct point {
	dbl x, y;
	inline point(const dbl& _x = 0.0, const dbl& _y = 0.0) {
		x = _x;
		y = _y;
	}
};

inline point operator + (const point& a, const point& b) {
	return point(a.x + b.x, a.y + b.y);
}

inline point operator - (const point& a, const point& b) {
	return point(a.x - b.x, a.y - b.y);
}

inline dbl dot(const point& a, const point& b) {
	return a.x * b.x + a.y * b.y;
}

inline dbl det(const point& a, const point& b) {
	return a.x * b.y - b.x * a.y;
}

inline dbl norm(const point& a, const point& b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

struct circle {
	point center;
	dbl radius;
};

inline pair<point, point> circle_intersect(const circle& a, const circle& b) {
	dbl vx = b.center.x - a.center.x;
	dbl vy = b.center.y - a.center.y;
	dbl dist = sqrt(sqr(vx) + sqr(vy));
	vx /= dist; vx *= a.radius;
	vy /= dist; vy *= a.radius;
	double angle = acos((sqr(a.radius) + sqr(dist) - sqr(b.radius)) / (2 * a.radius * dist));
	double xx1 = cos(+angle) * vx - sin(+angle) * vy, yy1 = sin(+angle) * vx + cos(+angle) * vy;
	double xx2 = cos(-angle) * vx - sin(-angle) * vy, yy2 = sin(-angle) * vx + cos(-angle) * vy;
	return make_pair(point(a.center.x + xx1, a.center.y + yy1), point(a.center.x + xx2, a.center.y + yy2));
}

inline dbl calc(const point& a, const point& b, const point& c) {
	return det(b - a, c - a);
}

inline bool check(const point& a, const point& b, const pair<point, point>& c) {
	return calc(a, b, c.first) * calc(a, b, c.second) <= 0;
}

int const N = 1000;
dbl const INF = 1e50;

int n;
circle circles[N];
vector< pair<int, dbl> > adj[N * 5];
pair<point, point> intersects[N * 5];
dbl dist[N * 5];
bool handled[N * 5];

inline void solve() {
	for (int i = 1; i <= n; ++i) {
		scanf("%lf%lf%lf", &circles[i].center.x, &circles[i].center.y, &circles[i].radius);
	}
	vector< pair<point, int> > points;
	points.push_back(make_pair(circles[1].center, 0));
	for (int i = 1; i <= n - 1; ++i) {
		intersects[i] = circle_intersect(circles[i], circles[i + 1]);
		points.push_back(make_pair(intersects[i].first, i));
		points.push_back(make_pair(intersects[i].second, i));
	}
	points.push_back(make_pair(circles[n].center, n));
	intersects[0] = make_pair(circles[1].center, circles[1].center);
	intersects[n] = make_pair(circles[n].center, circles[n].center);
	for (int i = 0; i < (int)points.size(); ++i) {
		adj[i].clear();
	}
//	foreach (it, points) {
//		cout << it->first.x << " " << it->first.y << endl;
//	}
//	cout << endl;
	for (int i = 0; i < (int)points.size(); ++i) {
		for (int j = i + 1; j < (int)points.size(); ++j) {
			bool available = true;
			for (int k = points[i].second + 1; k <= points[j].second - 1; ++k) {
				if (!check(points[i].first, points[j].first, intersects[k])) {
					available = false;
					break;
				}
			}
			if (available) {
				adj[i].push_back(make_pair(j, norm(points[i].first, points[j].first)));
			}
		}
	}
	priority_queue< pair<dbl, int> > heap;
	for (int i = 0; i < (int)points.size(); ++i) {
		handled[i] = false;
		dist[i] = INF;
	}
	dist[0] = 0.0;
	heap.push(make_pair(0.0, 0));
	while (!heap.empty()) {
		int x = heap.top().second;
//cout << x << endl;
		heap.pop();
		if (handled[x]) {
			continue;
		}
		handled[x] = true;
		foreach (it, adj[x]) {
			int y = it->first;
			dbl w = it->second;
			if (dist[y] > dist[x] + w) {
				dist[y] = dist[x] + w;
				heap.push(make_pair(-dist[y], y));
			}
		}
	}
//cout << points.size() << endl;
	printf("%.10f\n", dist[(int)points.size() - 1]);
}

int main () {
	while (scanf("%d", &n) != EOF && n > 0) {
		solve();
	}
	return 0;
}
