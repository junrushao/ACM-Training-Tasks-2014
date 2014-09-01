#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

const int N = 300005;

int n, val[N], father[N], sjj[N], color[N];
int Hash[N], h_tag;
long long f[N], w[N], sf[N], sw[N];
vector <pair <int, int> > v[N];

int main() {
	while (scanf("%d", &n) == 1 && n)
	{
		for (int i = 1; i <= n; i++)
			scanf("%d", &val[i]), v[i].clear();
		for (int i = 1; i < n; i++)
		{
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			v[a].push_back(make_pair(b, c));
			v[b].push_back(make_pair(a, c));
		}

		sjj[1] = 1;
		for (int h = 1, t = 1; h <= t; h++)
		{
			int now = sjj[h];
			for (vector <pair <int, int> > :: iterator it = v[now].begin(); it != v[now].end(); ++it)
				if (it->first != father[now])
					sjj[++t] = it->first, color[it->first] = it->second, father[it->first] = now;
		}

		for (int i = 1; i <= n; i++)
			w[i] = 1, f[i] = val[i] + val[father[i]];
		for (int i = n; i > 1; i--)
		{
			int now = sjj[i], fnow = father[now];
			if (color[now] != color[fnow])
			{
				w[fnow] += w[now];
				f[fnow] += f[now] + val[father[fnow]] * w[now];
			}
		}

		long long ans = 0;
		for (int i = 2; i <= n; i++)
			ans += f[i];
		for (int i = 1; i <= n; i++)
		{
			h_tag++;
			long long sfNow = 0, swNow = 0;
			for (vector <pair <int, int> > :: iterator it = v[i].begin(); it != v[i].end(); ++it)
			{
				if (it->first == father[i])
					continue;
				int cnow = it->second, now = it->first;
				if (Hash[cnow] != h_tag)
					Hash[cnow] = h_tag, sf[cnow] = 0, sw[cnow] = 0;
				sf[cnow] += f[it->first];
				sw[cnow] += w[it->first];
				sfNow += f[it->first];
				swNow += w[it->first];
				long long F = sfNow - sf[cnow], W = swNow - sw[cnow];
				ans += F * w[now] + f[now] * W - W * w[now] * val[i];
			}
		}

		cout << ans << endl;
	}

	return 0;
}
