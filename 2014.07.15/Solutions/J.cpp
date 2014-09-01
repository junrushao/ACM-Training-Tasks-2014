#include <cstdio>
#include <algorithm>
using namespace std;
const int pls = 10000000, maxn = 10005;

struct node
{
	int s, t;
	__inline bool operator <(const node &a) const
	{
		return s < a.s || s == a.s && t > a.t;
	}
} a[maxn];

int n, f[maxn], ans;

int main()
{
	int test;
	scanf("%d", &test);
	while (test--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			char c1, c2;
			scanf("%d%c%d%c", &a[i].s, &c1, &a[i].t, &c2);
			if (c1 == 'W')
				a[i].s = -a[i].s - pls;
			if (c2 == 'W')
				a[i].t = -a[i].t + pls;
		}
		sort(a + 1, a + n + 1);
		ans = 0;
		for (int i = 1; i <= n; i++)
		{
			int tmp = lower_bound(f, f + ans + 1, a[i].t) - f;
			if (ans < tmp)
				ans = tmp;
			f[tmp] = a[i].t;
		}
		printf("%d\n", ans);
	}
	return 0;
}

