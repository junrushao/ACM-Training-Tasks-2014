#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int calc(int j, int i, int k) {
	if(i % 2 == 0 and k % 2 == 1)
		return j ^ 1;
	else
		return j;
}
int len, a[55];
long long n, dp[55][2][2];
int main() {
	for(;;) {
		cin >> n;
		if(n == -1)
			break;
		len = 0;
		while(n) {
			a[len] = n % 5;
			n /= 5;
			len++;
		}
		memset(dp, 0, sizeof(dp));
		dp[len][0][1] = 1;
		for(int i = len; i >= 1; i--) for(int j = 0; j < 2; j++) {
			for(int k = 0; k < a[i - 1]; k++) {
				dp[i - 1][calc(j, i, k)][0] += dp[i][j][1];
			}
			dp[i - 1][calc(j, i, a[i - 1])][1] += dp[i][j][1];
			for(int k = 0; k < 5; k++) {
				dp[i - 1][calc(j, i, k)][0] += dp[i][j][0];
			}
		}
		cout << dp[0][0][0] + dp[0][0][1] << endl;
	}
	return 0;
}
