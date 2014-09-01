#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

const int N = 1111;
const long long INF = (1LL << 60);
const double eps = 1e-8, PI = acos(-1.0);

int n;
double r, x[N], y[N], d[N], s[N], vx[N], vy[N];

double dist(double x, double y, double xx, double yy) {
	return sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %lf", &n, &r);
		for(int i = 1; i <= n; i++) {
			scanf("%lf %lf %lf %lf", &x[i], &y[i], &d[i], &s[i]);
		}
		static int testCount = 0;
		bool collided = false;
		for(int i = 1; i <= n; i++) {
			for(int j = i + 1; j <= n; j++) {
				if (dist(x[i], y[i], x[j], y[j]) < r + eps) {
					collided = true;
				}
			}
			d[i] = (-d[i] + 90) / 180 * PI;
			vx[i] = cos(d[i]) * s[i];
			vy[i] = sin(d[i]) * s[i];
		}
		if (collided) {
			puts("0");
			continue;
		}
		double ans = 1e100;
		for(int i = 1; i <= n; i++) {
			for(int j = i + 1; j <= n; j++) {
				double X = x[i] - x[j], VX = vx[i] - vx[j], Y = y[i] - y[j], VY = vy[i] - vy[j];
				double a = VX * VX + VY * VY, b = 2 * X * VX + 2 * Y * VY, c = X * X + Y * Y - r * r;
				double delta = b * b - 4 * a * c;
				if (delta < -eps) {
					continue;
				}
				double l = (-b - sqrt(max(0.0, delta))) / 2 / a;
				double r = (-b + sqrt(max(0.0, delta))) / 2 / a;
				if (l > eps) {
					ans = min(ans, l);
				}
				if (r > eps) {
					ans = min(ans, r);
				}
			}
		}
		if (ans > 1e50) {
			puts("No collision.");
		} else {
			long long tmp = (long long)(ans + 0.5 + eps);
			cout << tmp << endl;
		}
	}
	return 0;
}