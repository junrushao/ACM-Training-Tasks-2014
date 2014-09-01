#include <cstdio>
#include <cmath>
#define eps 1e-6
const int maxn = 10005;
const double pi = acos(-1.0);
int n;
struct point
{
	double x, y, z;
	point(){}
	point(double x, double y, double z) : x(x), y(y), z(z){}
	__inline void read()
	{
		scanf("%lf%lf%lf", &x, &y, &z);
	}
}a[maxn];
__inline point calc(double h)
{
	double max = 0;
	for (int i = 1; i <= n; i++)
	{
		double tmp = h * sqrt(a[i].x * a[i].x + a[i].y * a[i].y) / (h - a[i].z);
		if (tmp > max)
			max = tmp;
	}
	return point(pi * max * max * h / 3, max, h);
}
int main()
{
	int test;
	scanf("%d", &test);
	while (test--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			a[i].read();
		double l = 0, r = 1e8;
		for (int i = 1; i <= n; i++)
			if (l < a[i].z)
				l = a[i].z;
		while(l + eps < r)
		{
			double m1 = (r - l) / 3 + l, m2 = (r - l) / 3 * 2 + l;
			point a1 = calc(m1), a2 = calc(m2);
			if (a1.x < a2.x)
				r = m2;
			else
				l = m1;
		}
		point ans = calc(l);
		printf("%.3f %.3f\n", ans.z, ans.y);
	}
	return 0;
}
