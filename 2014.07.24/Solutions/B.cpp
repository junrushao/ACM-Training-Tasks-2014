#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	double v, l, V, L, D, k, c, a, cost1, cost2, ans = 1000000000.0 * 1000000000.0, li, ri, t1, t2, t;
	scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &v, &l, &V, &L, &D, &a, &k, &c);
	int n, i;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%lf %lf", &li, &ri);
		t1 = (li + l) / v;
		t2 = D / (V - v);
		if (t1 < t2) {
			t = t2 - t1;
			cost1 = 0;
		} else {
			t = 0;
			cost1 = (t1 - t2) * k;
		}

		t += (ri - li + L) / V;

		if ((ri - li - l) / v >= t) {
			cost2 = 0;
		} else if ( (ri - li - l) / (v * 0.5) < t) {
			cost2 = v / ( (ri - li -l) / (v * 0.5) );
		} else {
			cost2 = ( v * t - (ri - li - l) ) / ( t * t * 0.5 );
		}

		if (cost2 < a) {
			cost2 = 0;
		} else {
			cost2 = (cost2 - a) * c;
		}

		if (ans > cost1 + cost2) {
			ans = cost1 + cost2;
		}

	}
	
	printf("%0.7f\n", ans);
	return 0;
}
