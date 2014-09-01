#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
const double EPS = 1E-8;
struct point{
	double x,y;
	point(double x = 0, double y = 0) : x(x), y(y) {}
	inline double length() const {
		return hypot(x,y);
	}
};
inline bool operator < (const point &a, const point &b){
	if (fabs(a.x - b.x) > EPS)
		return a.x < b.x;
	return a.y + EPS < b.y;
}
inline point operator- (const point &a, const point &b){
	return point(a.x - b.x, a.y - b.y);
}
inline double det(const point &a, const point &b){
	return a.x *b.y - b.x * a.y;
}

inline double dis(const point &a, const point &b){
	return hypot(a.x - b.x , a.y - b.y);
}

inline bool turn_left(const point &a, const point &b, const point &c){
	return det(b - a, c - a) > EPS;
}
inline bool turn_right (const point &a, const point &b, const point &c){
	return det(b -a , c - a) < -EPS;
}
inline vector<point> convex_hull(vector<point> a) {
	int n = (int)a.size(), cnt = 0;
	sort(a.begin(),a.end());
	vector<point> ret;
	for (int i = 0; i < n ; ++ i){
		while (cnt > 1 && turn_left(ret[cnt - 2], a[i] , ret[cnt - 1])){
			--cnt;
			ret.pop_back();
		}
		ret.push_back(a[i]);
		++cnt;
	}
	int fixed = cnt;
	for (int i = n-1; i >= 0; --i){
		while (cnt > fixed && turn_left(ret[cnt - 2], a[i], ret[cnt - 1])) {
			--cnt;
			ret.pop_back();
		}
		ret.push_back(a[i]);
		++cnt;
	}
	return ret;
}
double min3(double a, double b, double c){
	double t = a;
	t = min(t, b);
	t = min(t, c);
	return t;
}
int n;
double ans;
double x, y;
vector<point> p, q;

double hehe[505][505];
int main(){
	while (scanf("%d", &n) == 1){
		p.clear();
		q.clear();
		ans = 0;
		for (int i = 1; i <= n ; i++)
		{
			scanf("%lf%lf", &x, &y);
			point new_point(x, y);
			p.push_back(new_point);
		}
		q = convex_hull(p);
		/*		for (unsigned i = 0; i < q.size() - 1; i++){
				printf("%f %f\n",q[i].x, q[i].y);
				}*/

		for (unsigned i = 0; i < q.size() - 1; i++){
			for (unsigned j = 0;j < q.size() - 1; j++)
				if (j != i && j != i+1)
				{
					double s = fabs(det(q[j] - q[i], q[i + 1] - q[i]));
					double minl = min3(dis(q[i], q[i + 1]), dis(q[i + 1], q[j]), dis(q[i], q[j]));
					double height = s / minl;	
					if (height > ans) ans = height;
				}
		}
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				hehe[i][j] = dis(p[i], p[j]);

		for (unsigned i = 0; i < q.size() - 1; ++i)
			for (int j = 0; j < n; ++j)
			{
				if (dis(q[i], p[j]) < ans) continue;
				for (int k = j + 1; k < n; ++k) {
					double s = fabs(det(p[j] - q[i], p[k] - q[i]));
					double minl = hehe[j][k];//dis(p[j], p[k]);//min3(dis(q[i], p[k]), dis(p[k], p[j]), dis(q[i], p[j]));
					double height = s / minl;
					if (height > ans) ans = height;
				}
			}
		printf("%.8f\n", ans);
	}
}
