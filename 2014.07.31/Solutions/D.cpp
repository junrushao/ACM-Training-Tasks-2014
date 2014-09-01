
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m, p;
int a[200];
int C[200][200];

void prepare() {
	for(int i = 0; i < 200; ++i)	
		C[i][i] = C[i][0] = 1;
	for(int i = 1; i < 200; ++i)
		for(int j = 1; j < i; ++j)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % p;
}

int main() {
	scanf("%d%d%d", &n, &m, &p);
	prepare();
	for(int i = 0; i < m; ++i)
		scanf("%d", &a[i]);
	sort(a, a + m);
	int ans = 1, tot = 0, k = n / m;
	for (int i = m - 1; i >= 0; --i) {
		tot += k;
		if(n - a[i] + 1 < tot) {
			printf("-1\n");
			return 0;
		}
		ans = (long long)ans * C[n - a[i] + 1 - (tot - k) - 1][k - 1] % p;
	}
	printf("%d\n", ans);
	return 0;
}
