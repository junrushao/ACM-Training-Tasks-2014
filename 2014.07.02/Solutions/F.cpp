#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int d, r1, R1, r2, R2;

const double pi = acos(-1);

double s(double r) {
	return pi * r * r;
}

double inct(int r1, int r2) {
	if (d > r1 + r2) {
		return 0;
	} else if (d <= max(r1, r2) - min(r1, r2)) {
		return s(min(r1, r2));
	} else {
		double area = 0,
			   ang1 = acos((double)(r1 * r1 - r2 * r2 - d * d) / (-2 * r2 * d)),
			   ang2 = acos((double)(r2 * r2 - r1 * r1 - d * d) / (-2 * r1 * d));
		double h = r1 * sin(ang2);
		area = r1 * r1 * ang2 + r2 * r2 * ang1 - h * d;
		return area;
	}
}

int main() {
	scanf("%d%d%d%d%d", &d, &r1, &R1, &r2, &R2);
	double ans = s(R1) + s(R2) - s(r1) - s(r2) - inct(R1, R2) - inct(r1, r2) + inct(R1, r2) + inct(r1, R2);
	printf("%.12f\n", ans);
	return 0;
}

