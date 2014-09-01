#include<cstring>
#include<cstdio>
#include<cmath>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
struct Point {
	double x, y;
	Point(const double & x = 0, const double & y = 0) : x(x), y(y) {
	}
	void scan() {
		scanf("%lf%lf", &x, &y);
	}
	double len() {
		return sqrt(x * x + y * y);
	}
	void print() const {
		printf("(%f, %f)\n", x, y);
	}
} points[10001], lines[10001][2], o;
double atan2(const Point & a) {
	return atan2(a.y, a.x);
}
double eps = 1e-8, pi = acos(-1);
int sign(const double & x) {
	return x < -eps?-1:x > eps;
}
bool equal(const double & x, const double & y) {
	return x + eps > y and y + eps > x;
}
Point operator + (const Point & a, const Point & b) {
	return Point(a.x + b.x, a.y + b.y);
}
Point operator - (const Point & a, const Point & b) {
	return Point(a.x - b.x, a.y - b.y);
}
double operator * (const Point & a, const Point & b) {
	return a.x * b.y - a.y * b.x;
}
Point operator * (const double & a, const Point & b) {
	return Point(a * b.x, a * b.y);
}
bool check(const Point & a, const Point & b, const Point & c, const Point & d) {
	//a.print(); b.print(); c.print(); d.print();
	//printf("=%d\n", sign((a - b) * (c - b)) * sign((a - b) * (d - b)) < 0 and sign((c - d) * (a - d)) * sign((c - d) * (b - d)) < 0);
	return sign((a - b) * (c - b)) * sign((a - b) * (d - b)) < 0 and sign((c - d) * (a - d)) * sign((c - d) * (b - d)) < 0;
}
struct Line {
	Point s, d;
	Line(const Point & s, const Point & d) : s(s), d(d) {
	}
	Line(const double & theta) : s(0), d(cos(theta), sin(theta)) {
	}
};
Point intersect(const Line & a, const Line & b) {
	double lambda = b.d * (b.s - a.s) / (b.d * a.d);
	return a.s + lambda * a.d;
}
struct recvec {
	int type, i;
	double theta;
	recvec(int i, const double & theta, int type) : i(i), theta(theta), type(type) {
	}
};
bool operator < (const recvec & a, const recvec & b) {
	return a.theta + eps < b.theta;
}
vector<recvec> vec;
void push(int i, const double & theta1, const double theta2) {
	vec.push_back(recvec(i, theta1, 1));
	vec.push_back(recvec(i, theta2, -1));
}
double theta;
vector<Point> query;
struct cmp {
	bool operator () (int a, int b) {
		return intersect(Line(theta), Line(lines[a][0] - o, lines[a][1] - lines[a][0])).len() < intersect(Line(theta), Line(lines[b][0] - o, lines[b][1] - lines[b][0])).len();
	}
};
bool cmpPolar(const Point & a, const Point & b) {
	return atan2(a) < atan2(b);
}
set<int, cmp> st;
int main() {
	int m, n, k;
	while(3 == scanf("%d%d%d", &m, &n, &k)) {
	for(int i = 1; i <= n; i++) {
		points[i].scan();
	}
	for(int i = 1; i <= k; i++) {
		lines[i][0].scan();
		lines[i][1].scan();
	}
	for(int i = 1; i <= m; i++) {
		//printf("%d\n", i);
		o = points[i];
		vec.clear();
		bool piBlk(false);
		for(int j = 1; j <= k; j++) {
			double theta1 = atan2(lines[j][0] - o), theta2 = atan2(lines[j][1] - o);
			if(!equal(theta1, theta2)) {
				if((lines[j][0] - o) * (lines[j][1] - o) < 0)
					swap(theta1, theta2);
				if(theta1 > theta2) {
					push(j, -pi, theta2);
					push(j, theta1, pi);
					piBlk = true;
				}else {
					push(j, theta1, theta2);
				}
			}
		}
		sort(vec.begin(), vec.end());
		query.clear();
		for(int j = 1; j <= n; j++) if(j != i) {
			query.push_back(points[j] - o);
		}
		sort(query.begin(), query.end(), cmpPolar);
		int ans(0);
		int j = 0;
		st.clear();
		//for(int j = 0; j < (int)query.size(); j++)
		//	printf("%f\n", atan2(query[j]));
		while(j < (int)query.size() and atan2(query[j]) < vec[0].theta)
			ans++, j++;
		for(int k = 0; k + 1 < (int)vec.size(); k++) {
		//printf("%f~%f\n", vec[k].theta, vec[k + 1].theta);
			if(vec[k].type == -1)
				st.erase(vec[k].i);
			theta = (vec[k].theta + vec[k + 1].theta) / 2;
			if(vec[k].type == 1)
				st.insert(vec[k].i);
			while(j < (int)query.size() and vec[k].theta < atan2(query[j]) and atan2(query[j]) < vec[k + 1].theta) {
				//printf("%f~%f[%f] %d\n", vec[k].theta, vec[k + 1].theta, atan2(query[j]), *st.begin());
				if(st.empty() or !check(Point(0, 0), query[j], lines[*st.begin()][0] - o, lines[*st.begin()][1] - o))
					ans++;
				j++;
			}
		}
		if(!piBlk) {
			while(j < (int)query.size())
				ans++, j++;
		}
		printf("%d\n", ans);
	}
	//return 0;
	}
	fclose(stdin);
	return 0;
}
