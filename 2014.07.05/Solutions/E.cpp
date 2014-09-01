#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 505;
int n, a[N];
char s[N];

const int L = 26;
int dp[L + 1][N], ord[N];

const int INF = 1000000000;

int main() {
	while (scanf("%d", &n) == 1) {
		scanf("%s", s);
		for (int i = 0; i < n; ++i) {
			scanf("%d", a + i);
			ord[a[i]] = i;
		}
		ord[n] = -1;
		for (int i = 0; i <= L; ++i) {
			for (int j = 0; j <= n; ++j) {
				dp[i][j] = INF;
			}
		}
		dp[0][0] = 0;
		for (int i = 0; i < L; ++i) {
			for (int j = 0; j <= n; ++j) {
				dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
				int cost = 0, last = -2;
				for (int k = j; k < n; ++k) {
					int pos = a[k];
					if (ord[pos + 1] < last) {
						break;
					}
					last = ord[pos + 1];
					if (s[pos] != 'a' + i) {
						++cost;
					}
					dp[i + 1][k + 1] = min(dp[i + 1][k + 1], dp[i][j] + cost);
				}
			}
		}
		int ans = dp[L][n];
		if (ans == INF) {
			ans = -1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
