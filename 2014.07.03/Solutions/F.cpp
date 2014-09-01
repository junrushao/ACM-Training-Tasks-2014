#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

void solve() {
}

int n, ans, test;

int main() {
	scanf("%d", &test);
	for (int tt = 1; tt <= test; tt++)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			int x;
			scanf("%d", &x);
			if (i == 1)
				ans = x;
			else
				ans = max(ans, x);
		}

		printf("Case %d: %d\n", tt, ans);
	}

	return 0;
}
