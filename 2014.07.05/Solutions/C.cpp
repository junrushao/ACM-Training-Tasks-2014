#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n; 
long long a, b;

const int N = 1000005;
long long sum[N], f[N];

const long long INF = 1ll << 60;

int main() {
	int ta, tb;
	while (scanf("%d%d%d", &n, &ta, &tb) == 3) {
		a = ta, b = tb;
		sum[0] = 0;
		for (int i = 0; i < n; ++i) {
			int a;
			scanf("%d", &a);
			sum[i + 1] = sum[i] + a;
		}
		f[n] = INF;
		long long mins = max(a + b - f[n] + 1, sum[n]);
		for (int i = n - 1; i >= 0; --i) {
			f[i] = mins - sum[i];
			mins = min(mins, max(a + b - f[i] + 1, sum[i]));
		}
		puts(a >= f[0] ? "ALICE" : "BOB");
	}
	return 0;
}
