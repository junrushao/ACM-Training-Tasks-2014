#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long int64;

int n, m;
int64 k;
int64 f[70][70];
int a[70], b[70];
int ans[70], len;

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		b[i] = a[i];
	}
	sort(b + 1, b + n + 1);
	m = unique(b + 1, b + n + 1) - (b + 1);
	for (int i = 1; i <= n; ++i) {
		a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
	}
	for (int i = n; i; --i) {
		for (int j = 1; j <= m; ++j) {
			if (a[i] != j) f[i][j] = f[i+1][j];
			else {
				f[i][j] = 1LL;
				for (int kk = j + 1; kk <= m; ++kk) {
					f[i][j] += f[i+1][kk];
				}
			}
		}
	}
	len = 0;
	int p = 1;
	int px = 0;
	while (k) {
		for (int i = px + 1; i <= m; ++i) {
			if (f[p][i] < k) k -= f[p][i];
			else {
				ans[++len] = i;
				--k;
				while (a[p] != i) ++p;
				++p;
				px = i;
				break;
			}
		}
	}
	printf("%d\n", len);
	for (int i = 1; i <= len; ++i) printf("%d%c", b[ans[i]], i == len ? '\n' : ' ');
	return 0;
}

