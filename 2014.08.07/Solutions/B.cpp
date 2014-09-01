#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const double oo = 1e100;
const double eps = 1e-10;
const int maxn = 10005, maxm = 10;

int n, m;
int B[maxm], N[maxn];
double res;
double a[maxm][maxn];
double x[maxn];

void pivot(int r,int c) {
	swap(N[c], B[r]);
	a[r][c]=1/a[r][c];
	for (int j=0; j<=n; j++) if(j!=c) a[r][j]*=a[r][c];
	for (int i=0; i<=m; i++) if(i!=r){
		for (int j=0; j<=n; j++) if(j!=c)
			a[i][j] -= a[i][c]*a[r][j];
		a[i][c] = -a[i][c]*a[r][c];
	}
}

bool feasible(){
	int r, c, i;
	double p, v;
	while(true){
		for (p=oo, i=0; i<m; i++) if(a[i][n] < p) p = a[r=i][n];
		if (p > -eps) return true;
		for (p=0, i=0; i<n; i++) if(a[r][i] < p) p = a[r][c=i];
		if (p > -eps) return false;
		p = a[r][n]/a[r][c];
		for (i=r+1; i<m; i++) if(a[i][c] > eps) {
			v = a[i][n]/a[i][c];
			if (v<p) r=i, p=v;
		}
		pivot(r, c);
	}
}

int solve(){
	int r, c, i;
	double p, v;
	for (i=0; i<n; i++) N[i]=i;
	for (i=0; i<m; i++) B[i]=n+i;
	if (!feasible()) return -1;
	while(true){
		for (p=0, i=0; i<n; i++) if(a[m][i] > p) p = a[m][c=i];
		if (p < eps){
			for (i=0; i<n; i++) if(N[i]<n) x[N[i]]=0;
			for (i=0; i<m; i++) if(B[i]<n) x[B[i]]=a[i][n];
			res = -a[m][n];
			return 0;
		}
		for (p=oo, i=0; i<m; i++) if(a[i][c] > eps){
			v = a[i][n]/a[i][c];
			if(v<p) p=v, r=i;
		}
		if (p == oo) return 1;
		pivot(r, c);
	}
}

void input(){
	n = 4, m = 6;
	a[0][0] = 1, a[0][1] = 1, a[0][2] = 0, a[0][3] = 0;
	a[1][0] = 1, a[1][1] = 0, a[1][2] = 1, a[1][3] = 0;
	a[2][0] = 1, a[2][1] = 0, a[2][2] = 0, a[2][3] = 1;
	a[3][0] = 0, a[3][1] = 1, a[3][2] = 1, a[3][3] = 0;
	a[4][0] = 0, a[4][1] = 1, a[4][2] = 0, a[4][3] = 1;
	a[5][0] = 0, a[5][1] = 0, a[5][2] = 1, a[5][3] = 1;
	a[6][0] = 1, a[6][1] = 1, a[6][2] = 1, a[6][3] = 1;
	double l[6];
	for (int i = 0; i < 6; i++) {
		scanf("%lf", &l[i]);
	}
	a[0][4] = l[5];
	a[1][4] = l[1];
	a[2][4] = l[0];
	a[3][4] = l[3];
	a[4][4] = l[4];
	a[5][4] = l[2];
}

void output(){
	for (int i = 0; i < 4; i++) {
		printf("%.12f%c", x[i], i == 3 ? '\n' : ' ');
	}
}

int main() {
	input();
	solve();
	output();
	return 0;
}
