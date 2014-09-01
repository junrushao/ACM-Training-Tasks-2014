#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#define sqr(x) ((x) * (x))
using namespace std;
typedef long long int64;

struct Task {
	int x, a, b, c, d;
} task[1010];

int TT;
int lcm[110][110];
int n, tm;
int f[1010][10010];

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int64 test(int64 t) {
	int64 ret = 0;
	for (int i = 1; i <= n; ++i) {
		int64 a, b, c, d;
		a = task[i].a, b = task[i].b, c = task[i].c, d = task[i].d;
		int64 use = t * int64(task[i].x);
		ret += int64(f[i][lcm[b][d]]) * int64(use / int64(lcm[b][d])) + int64(f[i][use % lcm[b][d]]);
	}
	return ret;
}

int main(){
	cin >> TT;
	for (int i = 1; i <= 100; ++i) {
		for (int j = 1; j <= 100; ++j) {
			lcm[i][j] = i * j / gcd(i, j);
		}
	}
	for (int T = 1; T <= TT; ++T) {
		scanf("%d %d", &n, &tm);
		for (int i = 1; i <= n; ++i) {
			scanf("%d %d %d %d %d", &task[i].x, &task[i].a, &task[i].b, &task[i].c, &task[i].d);
			if (task[i].b > task[i].d) swap(task[i].a, task[i].c), swap(task[i].b, task[i].d);
		}
		memset(f, 0, sizeof(f));
		for (int i = 1; i <= n; ++i) {
			int b = task[i].b, d = task[i].d;
			int a = task[i].a, c = task[i].c;
			for (int j = 1; j <= b; ++j) f[i][j] = min(a, c);
			for (int j = b + 1; j <= d; ++j) f[i][j] = min(a + f[i][j-b], c);
			for (int j = d + 1; j <= lcm[b][d]; ++j) f[i][j] = min(a + f[i][j-b], c + f[i][j-d]);
		}
		int ll = 0, rr = 10001000;
		while (ll < rr - 1) {
			int mm = (ll + rr) >> 1;
			//cout << mm << ' ' << test(mm) << endl;
			if (test(mm) <= int64(tm)) ll = mm;
			else rr = mm;
		}
		printf("Case %d: %d\n", T, ll);
	}
	return	0;
}
