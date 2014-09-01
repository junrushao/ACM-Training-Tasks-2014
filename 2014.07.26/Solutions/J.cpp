#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

const int N = 111 * 2;
const double EPS = 1e-8;
const int INF = 1000000000;
const int LIMIT = N * 3;

struct Edge {
	int to, st, delta;
	bool deleted;
	Edge(int to = 0, int st = 0, int delta = 0) : to(to), st(st), delta(delta) {
		deleted = false;
	} 
};

struct Point {
	int x, y, z;
	Point(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
	friend inline Point operator +(const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	friend inline Point operator -(const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y, a.z - b.z);
	}
	int getDist() {
		int value = x * x + y * y + z * z;
		int res = (int)sqrt(value);
		while(res * res < value) {
			res++;
		}
		return res;
	}
};
Point getPoint() {
	int x, y, z;
	scanf("%d %d %d", &x, &y, &z);
	return Point(x, y, z);
}

vector<Edge> e[N];
vector<Point> points;
int source, target, dist[N], times[N], lower[N];
int n;
pair<int, int> pre[N];

vector<pair<int, int> > loop;

void solveLoop(int p) {
	loop.clear();
	static int visit[N];
	for(int i = 0; i < n; i++) {
		visit[i] = 0;
	}
	int x = p, cnt = 0;
	while(!visit[x]) {
		visit[x] = 1;
		x = pre[x].first;
	}
	p = x;
	while(1) {
		loop.push_back(pre[x]);
		x = pre[x].first;
		if (x == p) {
			break;
		}
		assert(++cnt <= LIMIT);
	}
	
	reverse(loop.begin(), loop.end());
	int m = (int)loop.size();
	for(int i = 0; i < m; i++) {
		bool flag = true;
		int ds = e[loop[i].first][loop[i].second].st;
		for(int j = 0; j < m - 1 && flag; j++) {
			ds += e[ loop[(i + j) % m].first ][ loop[(i + j) % m].second ].delta;
			if (ds < e[ loop[(i + j + 1) % m].first ][ loop[(i + j + 1) % m].second ].st) {
				flag = false;
			}
		}
		if (flag) {
		//	e[loop[i].first][loop[i].second].deleted = true;
			lower[loop[i].first] = min(lower[loop[i].first], e[loop[i].first][loop[i].second].st);
		//	lower[loop[(i + 1) % m].first] = min(lower[loop[(i + 1) % m].first],
		//							 e[loop[i].first][loop[i].second].st + e[loop[i].first][loop[i].second].delta);
			return ;
		}
	}
}

vector<int> queue;

int spfa() {
	queue.clear();
	for(int i = 0; i < n; i++) {
		times[i] = 0;
		dist[i] = lower[i];
		if (lower[i] != INF) {
			queue.push_back(i);
		}
	}
	for(int head = 0; head < (int)queue.size(); head++) {
		int x = queue[head];
		for(int i = 0; i < (int)e[x].size(); i++) {
			if (e[x][i].deleted) {
				continue;
			}
			int value = max(dist[x], e[x][i].st) + e[x][i].delta;
			int y = e[x][i].to;
			if (value < dist[y]) {
				queue.push_back(y);
				dist[y] = value;
				pre[y] = make_pair(x, i);
				if (++times[y] == n) {
					solveLoop(y);
					return 1;
				}
			}
		}
	}
	return 0;
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		points.clear();
		points.push_back(getPoint());
		points.push_back(getPoint());
		source = 0; e[source].clear();
		target = 1; e[target].clear();
		
		int holes;
		scanf("%d", &holes);
		for(; holes--; ) {
			int idx = (int)points.size();
			points.push_back(getPoint());
			points.push_back(getPoint());
			e[idx].clear();
			e[idx + 1].clear();
			int st, delta;
			scanf("%d %d", &st, &delta);
			e[idx].push_back(Edge(idx + 1, st, delta));
		}
		n = (int)points.size();
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++) {
				if (i != j) {
					e[i].push_back(Edge(j, -INF, (points[j] - points[i]).getDist()));
				}
			}
		for(int i = 0; i < n; i++) {
			lower[i] = INF;
		}
		lower[source] = 0;
		while(spfa());
		printf("%d\n", dist[target]);
	}
	return 0;
}
