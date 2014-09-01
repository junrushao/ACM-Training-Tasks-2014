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

int n, test, full, tt, des[105];
long long f[100005];
char str[105];

void solve() {
	printf("Case %d: ", ++tt);
	scanf("%d", &n);
	for (int i = 0; i <= n; i++)
	{
		scanf("%s", str + 1);
		des[i] = 0;
		for (int j = 1; j <= n; j++)
			if (str[j] == '1')
				des[i] |= (1 << (j - 1));
	}

	full = (1 << n) - 1;
	for (int i = 1; i <= full; i++)
		f[i] = 0;
	f[0] = 1;
	for (int i = 0; i < full; i++)
	{
		int now = des[0];
		for (int j = 1; j <= n; j++)
			if (i & (1 << (j - 1)))
				now |= des[j];
		for (int j = 1; j <= n; j++)
			if ((now & (1 << (j - 1))) && !(i & (1 << (j - 1))))
				f[i + (1 << (j - 1))] += f[i];
	}

	cout << f[full] << endl;
}

int main() {
	scanf("%d", &test);
	while (test--)
		solve();
	return 0;
}

