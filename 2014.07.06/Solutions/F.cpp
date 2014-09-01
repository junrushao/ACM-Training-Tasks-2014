#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;

const int mo = 10007;

int n, r, test, x[505], y[505], niyuan[mo + 5];
int fac[505][505], du[505], a[505][505], f[505];

int cross(int x1, int y1, int x2, int y2)
{
	return x1 * y2 - x2 * y1;
}

int in(int a, int b, int c)
{
	if (a >= b && a <= c)
		return 1;
	if (a >= c && a <= b)
		return 1;
	return 0;
}

int sumi(int a, int b)
{
	int ret = 1, c = a;
	while (b)
	{
		if (b & 1)
			(ret *= c) %= mo;
		(c *= c) %= mo;
		b >>= 1;
	}

	return ret;
}

int find(int i)
{
	if (f[i] == i)
		return i;
	return f[i] = find(f[i]);
}

int main() {
	scanf("%d", &test);
	for (int i = 1; i < mo; i++)
		niyuan[i] = sumi(i, mo - 2);
	while (test--)
	{
		scanf("%d %d", &n, &r);
		for (int i = 1; i <= n; i++)
			scanf("%d %d", &x[i], &y[i]);
		if (n == 1)
		{
			printf("1\n");
			continue;
		}

		for (int i = 1; i <= n; i++)
		{
			du[i] = 0;
			f[i] = i;
			for (int j = 1; j <= n; j++)
				a[i][j] = 0;
		}

		for (int i = 1; i < n; i++)
			for (int j = i + 1; j <= n; j++)
				if ((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) <= r * r)
				{
					int flag = 1;
					for (int k = 1; k <= n; k++)
						if (k != i && k != j && cross(x[i] - x[k], y[i] - y[k], x[j] - x[k], y[j] - y[k]) == 0
								&& in(x[k], x[i], x[j]) && in(y[k], y[i], y[j]))
						{
							flag = 0;
							break;
						}

					if (flag == 1)
					{
						a[i][j] = a[j][i] = flag;
						du[i] += flag, du[j] += flag;
						f[find(i)] = find(j);
					}
				}
		int tag = 1;
		for (int i = 2; i <= n; i++)
			if (find(i) != find(1))
			{
				tag = 0;
				break;
			}
		if (!tag)
		{
			printf("-1\n");
			continue;
		}

		for (int i = 1; i < n; i++)
			for (int j = 1; j < n; j++)
				if (i == j)
					fac[i][j] = du[i];
				else
				{
					if (a[i][j])
						fac[i][j] = mo - 1;
					else
						fac[i][j] = 0;
				}

		/*for (int i = 1; i < n; i++)
			for (int j = 1; j < n; j++)
				if (j == n - 1)
					printf("%d\n", fac[i][j]);
				else
					printf("%d ", fac[i][j]);*/

		for (int i = 1; i < n; i++)
		{
			if (fac[i][i] == 0)
			{
				int j;
				for (j = i + 1; j < n; j++)
					if (fac[j][i] > 0)
						break;
				for (int k = 1; k < n; k++)
					swap(fac[j][k], fac[i][k]);
			}

			for (int j = i + 1; j < n; j++)
			{
				if (!fac[j][i])
					continue;
				int temp = fac[j][i] * niyuan[fac[i][i]] % mo;
				for (int k = i; k < n; k++)
				{
					fac[j][k] = (fac[j][k] - fac[i][k] * temp) % mo;
					while (fac[j][k] < 0)
						fac[j][k] += mo;
				}
			}
		}
		
		/*for (int i = 1; i < n; i++)
			for (int j = 1; j < n; j++)
				if (j == n - 1)
					printf("%d\n", fac[i][j]);
				else
					printf("%d ", fac[i][j]);*/

		int ans = 1;
		for (int i = 1; i < n; i++)
			(ans *= fac[i][i]) %= mo;
		while (ans < 0)
			ans += mo;
		printf("%d\n", ans);
	}

	return 0;
}
