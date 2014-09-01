#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const double Eps = 1E-6;

#define x0 yaodaye
#define y0 yaodaye2

int x0,y0,c,t;
int x,y,vx,vy;
int n;

double Sqrt(double x) {
	return x < 0 ? 0 : sqrt(x);
}

double calc(double a, double b, double c, double t){
	return (a * t * t + b * t + c);
}

double delta(double a,double b, double c){
	return (b * b - 4 * a * c);
}
bool check( double a, double b, double c, double t){
	if (fabs(a) < Eps){
		if (fabs(b) < Eps ) {
			return fabs(c) < Eps;
		}
		else
		{
			double p = calc(a,b,c,0);
			double q = calc(a,b,c,t);
			if (fabs(p) < Eps) return true;
			if (fabs(q) < Eps) return true;
			return ((p > Eps) ^ (q > Eps));
		}
	} else
	{
		if (a < 0)
		{
			a = -a;
			b = -b;
			c = -c;
		}
		double del = delta((double)a, (double)b, (double)c);
		if (del < -Eps) return false;
//		double p = 2 * (double)a * (double)t + (double)b;
		double sdel = Sqrt(del);
		double sdel1 = (-b + sdel) / (2.0 * a);
		double sdel2 = (-b - sdel) / (2.0 * a);
		return ((sdel1 > -Eps && sdel1 < (double)t + Eps ) || (sdel2 > -Eps && sdel2 < (double)t + Eps));
	}
}
bool judge(double x,double y,double vx,double vy,double p,double t){
	double a = vx * vx + vy * vy - p * p;
	double b = 2 * vx * x + 2 * vy * y;
	double c = x * x + y * y;
	return check(a,b,c,t);
}
int main(){
  while (scanf("%d%d%d%d", &x0, &y0, &c, &t) == 4){
  	scanf("%d", &n);
  	int ans = 0;
  	for (int i = 1 ; i <= n ;i++){
  		scanf("%d%d%d%d", &x, &y, &vx, &vy);
  		x -= x0;
  		y -= y0;
  		if (judge((double)x,(double)y,(double)vx,(double)vy,(double)c,(double)t)
  		|| judge((double)x + 2.0* vx * t,(double)y + 2.0 * vy * t,(double)-vx,(double)-vy,(double)c,(double)t)) ans++;
  	}
  	printf("%d\n", ans);
  }
  
}
