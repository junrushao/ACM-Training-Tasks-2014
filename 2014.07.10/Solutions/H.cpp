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

const int MAXN = 17;

int dp[1 << MAXN];
bool pal[1 << MAXN];

bool is_pal(string s) {
	for (int index = 0; index < (int)s.length() / 2; ++index) {
		if (s[index] != s[s.length() - index - 1]) {
			return false;
		}
	}
	return true;
}

int main() {
	int task;
	scanf("%d", &task);
	while (task-- > 0) {
		char s[MAXN];
		scanf("%s", s);
		int n = strlen(s);
		for (int mask = 0; mask < 1 << n; ++mask) {
			dp[mask] = n;
			pal[mask] = false;
		}
		for (int mask = 0; mask < 1 << n; ++mask) {
			string t = "";
			for (int index = 0; index < n; ++index) {
				if ((mask >> index & 1) == 1) {
					t += s[index];
				}
			}
			pal[mask] = is_pal(t);
		}
		dp[0] = 0;
		for (int mask = 1; mask < 1 << n; ++mask) {
			for (int v = mask; v; v = v - 1 & mask) {
				if (pal[v]) {
					dp[mask] = min(dp[mask], dp[mask ^ v] + 1);
				}
			}
		}
		printf("%d\n", dp[(1 << n) - 1]);
	}
	return 0;
}