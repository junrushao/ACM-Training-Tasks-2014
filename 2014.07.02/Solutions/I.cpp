#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 10005;

int n;

double det(double a00, double a01, double a10, double a11) {
	return a00 * a11 - a01 * a10;
}

int main() {
	scanf("%d", &n);
	double sum = 0, isum = 0;
	for (int i = 0; i < n; ++i) {
		double a;
		scanf("%lf", &a);
		sum += a, isum += i * a;
	}
	double a00 = n, a01 = (double)n * (n - 1) / 2, a02 = sum,
		   a10 = (double)n * (n - 1) / 2, a11 = (double)(n - 1) * n * (2 * n - 1) / 6, a12 = isum;
	double b0 = det(a02, a01, a12, a11) / det(a00, a01, a10, a11),
		   d = det(a00, a02, a10, a12) / det(a00, a01, a10, a11);
	printf("%.12f %.12f\n", b0, d);
	return 0;
}

