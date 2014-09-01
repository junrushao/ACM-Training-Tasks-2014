#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1000005;

int x[N], y[N], st[N], at[N][8], maxs[8];

const int MOD = 1000000007;
int dp[1 << 8 | 1];

const int INF = 2000000000;

int n;

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < 8; ++i) {
			maxs[i] = -INF;
		}
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", x + i, y + i);
			at[i][0] = x[i], at[i][1] = -x[i],
			at[i][2] = y[i], at[i][3] = -y[i];
			at[i][4] = x[i] + y[i], at[i][5] = -x[i] - y[i];
			at[i][6] = x[i] - y[i], at[i][7] = -x[i] + y[i];
			for (int j = 0; j < 8; ++j) {
				maxs[j] = max(maxs[j], at[i][j]);
			}
		}
		for (int i = 0; i < n; ++i) {
			st[i] = 0;
			for (int j = 0; j < 8; ++j) {
				st[i] = st[i] << 1 | (maxs[j] == at[i][j]);
			}
		}
		for (int i = 0; i < 1 << 8; ++i) {
			dp[i] = 1;
		}
		for (int i = 0; i < n; ++i) {
			dp[st[i]] = dp[st[i]] * 2 % MOD;
		}
		for (int i = 0; i < 8; ++i) {
			int bit = 1 << i;
			for (int st = 0; st < 1 << 8; ++st) {
				if (~st & bit) {
					dp[st | bit] = (long long)dp[st | bit] * dp[st] % MOD;
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < 1 << 8; ++i) {
			int sign = (__builtin_parity(i) & 1) ? -1 : 1;
			ans = (ans + sign * dp[i]) % MOD;
		}
		if (ans < 0) {
			ans += MOD;
		}
		printf("%d\n", ans);
	}
	return 0;
}
