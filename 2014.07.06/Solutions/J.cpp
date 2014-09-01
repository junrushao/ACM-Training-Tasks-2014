#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;

const int OO = 1111111111;

const int N = 100005;

int e[N], succ[N], last[N], val[N], sum;
int dis[N], pre[N], gap[N];
int u[N], v[N], w[N], p[N], vv[N];
int n, m, ans1, ans2;
int ancient[N], tunnel[N];

int ok();
void dfs(int i, int s);
void init(int n);
void add(int a, int b, int c);
int sap(int s, int t);

int main() {
	while (scanf("%d %d", &n, &m) == 2 && (n + m))
	{
		for (int i = 1; i <= n; i++)
			scanf("%d", &vv[i]);
		ancient[0] = 0, tunnel[0] = 0;
		for (int i = 1; i <= m; i++)
		{
			scanf("%d %d %d %d", &u[i], &v[i], &w[i], &p[i]);
			if (p[i] > 0)
				ancient[++ancient[0]] = i;
			if (p[i] < 0)
				tunnel[++tunnel[0]] = i;
		}

		ans1 = 0;
		dfs(1, 0);
		if (ans1 == 0)
			printf("Poor Heaven Empire\n");
		else
			printf("%d %d\n", ans1, ans2);
	}

	return 0;
}

int ok()
{
	int tot = tunnel[0], s = n + tot + 1, t = n + tot + 2;
	init(t);
	for (int i = 1; i <= tot; i++)
		add(n + i, t, w[tunnel[i]]);
	for (int i = 1; i <= n; i++)
		add(s, i, vv[i]);
	for (int i = 1; i <= m; i++)
	{
		//printf("u = %d v = %d\n", u[i], v[i]);
		if (p[i] <= 0)
			add(u[i], v[i], OO);
		else
			add(u[i], v[i], 1);
	}

	for (int i = 1; i <= tot; i++)
	{
		int now = tunnel[i];
		add(u[now], n + i, OO);
	}

	return sap(s, t);
}

void dfs(int i, int s)
{
	if (i > ancient[0])
	{
		int now = ok();
		if (now > ans1 || (now == ans1 && s < ans2))
			ans1 = now, ans2 = s;
		return;
	}

	int now = ancient[i];
	p[now] = 0;
	dfs(i + 1, s + w[now]);
	p[now] = 1;
	dfs(i + 1, s);
}

void init(int n)
{
	for (int i = 1; i <= n; i++)
		last[i] = dis[i] = gap[i] = pre[i] = 0;
	sum = 1;
	gap[0] = n;
}

void add(int a, int b, int c)
{
	//printf("add %d %d %d\n", a, b, c);
	e[++sum] = b, succ[sum] = last[a], last[a] = sum;
	e[++sum] = a, succ[sum] = last[b], last[b] = sum;
	val[sum - 1] = c;
	val[sum] = 0;
}

int sap(int s, int t)
{
	int ans = 0, now, i, _min;
	for (now = s; dis[s] < t; )
	{
		for (i = last[now]; i != 0; i = succ[i])
			if (val[i] > 0 && dis[now] == dis[e[i]] + 1)
			{
				pre[e[i]] = i;
				now = e[i];
				break;
			}
		if (now == t)
		{
			for (_min = OO; now != s; now = e[pre[now] ^ 1])
				_min = min(_min, val[pre[now]]);
			ans += _min;
			for (now = t; now != s; now = e[pre[now] ^ 1])
				val[pre[now]] -= _min, val[pre[now] ^ 1] += _min;
		}

		else if (i == 0)
		{
			if (gap[dis[now]] == 1)
				return ans;
			for (_min = t, i = last[now]; i != 0; i = succ[i])
				if (val[i] > 0)
					_min = min(_min, dis[e[i]] + 1);
			gap[dis[now]]--, gap[_min]++, dis[now] = _min;
			if (now != s)
				now = e[pre[now] ^ 1];
		}
	}

	return ans;
}