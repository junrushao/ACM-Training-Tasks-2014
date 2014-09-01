#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cassert>
#include <bitset>
#include <numeric>

using namespace std;

const int MAXL = 111111;
const int MAXN = 20;

char s[MAXL];
int dp[2][1 << MAXN];

int bit_count(int x) {
	int ret = 0;
	while (x > 0) {
		if ((x & 1) == 1) {
			++ret;
		}
		x >>= 1;
	}
	return ret;
}

int main() {
	int task;
	scanf("%d", &task);
	while (task-- > 0) {
		scanf("%s", s);

		memset(dp[0], 0, sizeof dp[0]);
		int state = 0;
		++dp[0][state];
		int n = strlen(s);
		for (int index = 0; index < n; ++index) {
			state ^= 1 << (s[index] - 'a');
			++dp[0][state];
		}
		for (int index = 0; index < MAXN; ++index) {
			int _ = index & 1;
			memset(dp[_ ^ 1], 0, sizeof dp[_ ^ 1]);
			for (int mask = 0; mask < 1 << MAXN; ++mask) {
				dp[_ ^ 1][mask] = dp[_][mask];
				if ((mask >> index & 1) == 1) {
					dp[_ ^ 1][mask] += dp[_][mask ^ 1 << index];
				}
			}
		}

		int q;
		scanf("%d", &q);
		while (q-- > 0) {
			int m;
			scanf("%d", &m);
			int mask = 0;
			for (int index = 0; index < m; ++index) {
				char c[5];
				scanf("%s", c);
				mask |= 1 << (c[0] - 'a');
			}
			long long ret = 0;
			int pat = mask;
			while (true) {
				int all = (1 << MAXN) - 1 ^ mask ^ pat;
				int sub = pat;
				int num = 0;
				while (true) {
					if ((bit_count(sub) & 1) == 1) {
						num -= dp[0][all ^ sub];
					}
					else {
						num += dp[0][all ^ sub];
					}
					if (sub == 0) {
						break;
					}
					sub = sub - 1 & pat;
				}
				ret += (long long)num * (num - 1) / 2;
				if (pat == 0) {
					break;
				}
				pat = pat - 1 & mask;
			}
			printf("%I64d\n", ret);
		}
	}
	return 0;
}