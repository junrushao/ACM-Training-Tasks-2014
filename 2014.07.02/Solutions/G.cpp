#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 105;

int n;

int t[N];

int dp[N];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", t + i);
	}
	sort(t, t + n);
	dp[2] = t[1], dp[3] = t[1] + t[0] + t[2];
	for (int i = 4; i <= n; ++i) {
		dp[i] = min(dp[i - 1] + t[0] + t[i - 1],
					dp[i - 2] + t[0] + t[i - 1] + 2 * t[1]);
	}
	printf("%d\n", dp[n]);
	return 0;
}
