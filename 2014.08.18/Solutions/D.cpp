#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


int n, m;

const int N = 205;
double x[N], y[N], z[N];

int sign(double x, double eps = 1e-9) {
	return x < -eps ? -1 : x > eps;
}

int main() {
	while (scanf("%d", &n) == 1 && (n != -1)) {
		for (int i = 0; i < n; ++i) {
			scanf("%lf%lf%lf", &x[i], &y[i], &z[i]);
		}
		scanf("%d", &m);
		for (int i = n; i < n + m; ++i) {
			scanf("%lf%lf%lf", &x[i], &y[i], &z[i]);
		}
		double a = 0, b = 0, c = 0, d = 0;
		while (true) {
			bool flag = false;
			for (int i = 0; i < n; ++i) {
				if (sign(a * x[i] + b * y[i] + c * z[i] + d) >= 0) {
					a -= x[i], b -= y[i], c -= z[i], d -= 1;
					flag = true;
				}
			}
			for (int i = n; i < n + m; ++i) {
				if (sign(a * x[i] + b * y[i] + c * z[i] + d) <= 0) {
					double offset = a * x[i] + b * y[i] + c * z[i];
					a += x[i], b += y[i], c += z[i], d += 1;
					flag = true;
				}
			}
			if (!flag) {
				break;
			}
		}
		printf("%.6f %.6f %.6f %.6f\n", a, b, c, d);
	}
	return 0;
}
