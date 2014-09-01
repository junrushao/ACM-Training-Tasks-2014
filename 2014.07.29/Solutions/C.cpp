#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
using namespace std;

double dp[1 << 15];
double w;
int c[20], n;

double go(double x) {
	dp[0] = 0;
	for (int mask = 1; mask < (1 << n); ++mask) {
		int cnt = 0;
		for (int i = 0; i < n; ++i)
			if (mask & (1 << i))
				++cnt;
		cnt = n - cnt + 1;
		
		dp[mask] = -1e8;
		for (int i = 0; i < n; ++i)
			if (mask & (1 << i))
				dp[mask] = max(dp[mask], sin(x + cnt + c[i]) - dp[mask - (1 << i)]); 
	}
	return dp[(1 << n) - 1] + ((2.0 / (1 + exp(x / w))) - 1) * n;
}

int main() {
	cin >> n >> w;
	for (int i = 0; i < n; ++i)
		scanf("%d", &c[i]);
	double lo = -1e7, hi = 1e7, ans = 20111111;
	for (int i = 0; i < 50; i++) {
		double mi = (lo + hi) / 2;
		if (go(mi) * go(lo) < 0)
			hi = mi;
		else
			lo = mi;
	}
	ans = lo;
	if (ans==20111111) puts("impossible"); 
	else printf("%.10f\n",ans);
	return 0;
}
