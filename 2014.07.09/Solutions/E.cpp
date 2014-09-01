#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <utility>
#include <bitset>
#include <complex>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <cctype>
using namespace std;

typedef pair <int, int> TP;
#define X first
#define Y second
inline int sqr(int x)
{
	return x * x;
}
inline int dis2(const TP &a, const TP &b)
{
	return sqr(a.X - b.X) + sqr(a.Y - b.Y);
}
inline double dis(const TP &a, const TP &b)
{
	return sqrt(sqr(a.X - b.X) + sqr(a.Y - b.Y));
}
int n;
TP E[1010];
inline int det(const TP &a, const TP &b, const TP &c)
{
	return (c.X - a.X) * (b.Y - a.Y) - (c.Y - a.Y) * (b.X - a.X);
}
int main()
{
	int T, ca = 0;
	for (scanf("%d", &T); T; T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d%d", &E[i].X, &E[i].Y);
		printf("Case %d: ", ++ca);
		sort(E, E + n);
		n = unique(E, E + n) - E;
		int rx = -1, ry, mi = 1000000000;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				if (dis2(E[i], E[j]) < mi)
					rx = i, ry = j, mi = dis2(E[i], E[j]);
		double ans = 1e10;
		if (rx != -1) {
			for (int i = 0; i < n; i++)
				if (det(E[i], E[rx], E[ry]) && i != rx && i != ry && ans > dis(E[i], E[rx]) + dis(E[rx], E[ry]) + dis(E[i], E[ry]))
					ans = dis(E[i], E[rx]) + dis(E[rx], E[ry]) + dis(E[i], E[ry]);
		}
		if (rx == -1 || ans > 1e9)
			puts("No Solution");
		else {
			for (int i = 0; i < n; i++)
				for (int j = i + 1; j < n; j++)
					if (dis(E[i], E[j]) * 2 < ans)
						for (int k = j + 1; k < n; k++)
							if (det(E[i], E[j], E[k]))
								ans = min(ans, dis(E[i], E[j]) + dis(E[i], E[k]) + dis(E[j], E[k]));
			printf("%.3f\n", ans);
		}
	}
}
