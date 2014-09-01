#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define mod 100000007
using namespace std;
const int maxn = 1005;
int n, m, f[maxn][maxn << 1][2];
__inline void update(int &a, int b)
{
	a += b;
	a %= mod;
}
int main()
{
	int test;
	scanf("%d", &test);
	while (test--)
	{
		scanf("%d%d", &n, &m);
		memset(f, 0, sizeof(f));
		f[1][1][0] = 1;
		f[1][2][1] = 1;
		for (int i = 1; i < n; i++)
			for (int j = 1; j <= m; j++)
			{
				if (f[i][j][0])
				{
					update(f[i + 1][j][0], f[i][j][0]);
					update(f[i + 1][j + 1][0], f[i][j][0]);
					update(f[i + 1][j + 2][1], f[i][j][0]);
					update(f[i + 1][j + 1][1], f[i][j][0] * 2);
				}
				if (f[i][j][1])
				{
					update(f[i + 1][j + 1][0], f[i][j][1]);
					update(f[i + 1][j + 2][1], f[i][j][1]);
					update(f[i + 1][j][0], f[i][j][1] * 2);
					update(f[i + 1][j + 1][1], f[i][j][1] * 2);
					update(f[i + 1][j][1], f[i][j][1]);
				}
			}
		cout << (f[n][m][0] + f[n][m][1]) % mod << endl;
	}
	return 0;
}
