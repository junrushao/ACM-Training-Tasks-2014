#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const double R = 8.314, eps = 1e-9;

double p, V, T, n;

int main() {
	p = V = T = n = -1e100;
	for (int i = 0; i < 3; ++i) {
		char ch[2];
		double tmp;
		scanf("%s%*s%lf", ch, &tmp);
		if (ch[0] == 'p') {
			p = tmp;
		} else if (ch[0] == 'V') {
			V = tmp;
		} else if (ch[0] == 'T') {
			T = tmp;
		} else if (ch[0] == 'n') {
			n = tmp;
		}
	}
	//V, T > 0 but p / n...
	//error -> INF or ZERO undefined -> ZERO / ZERO
	if (p < -1) {
		printf("p = %.12f\n", n * R * T / V);
	}
	if (V < -1) {
		if (n > eps && p > eps) {
			printf("V = %.12f\n", n * R * T / p);
		} else if (n < eps && p > eps) {
			printf("error\n");
		} else if (n > eps && p < eps) {
			printf("error\n");
		} else if (n < eps && p < eps) {
			printf("undefined");
		}
	}
	if (T < -1) {
		if (p > eps && n > eps) {
			printf("T = %.12f\n", p * V / R / n);
		} else if (p > eps && n < eps) {
			printf("error\n");
		} else if (p < eps && n > eps) {
			printf("error\n");
		} else if (p < eps && n < eps) {
			printf("undefined\n");
		}
	}
	if (n < -1) {
		printf("n = %.12f\n", p * V / R / T);
	}
	return 0;
}

