#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
int n, q;
long long ans;
multiset<int> yr;
int main()
{
	int test;
	scanf("%d", &test);
	for (int tt = 1; tt <= test; tt++)
	{
		scanf("%d%d", &n, &q);
		int pos = 0, dir;
		yr.clear();
		ans = 0;
		while (q--)
		{
			int opr;
			scanf("%d", &opr);
			if (opr == 0)
			{
				int tmp;
				scanf("%d", &tmp);
				yr.insert(tmp);
			}
			else
			{
				if (yr.begin() == yr.end())
					continue;
				multiset<int>::iterator itr = yr.lower_bound(pos);
				int l = -99999999, r = 99999999;
				if (itr != yr.end())
					r = *itr;
				if (itr != yr.begin())
				{
					itr--;
					l = *itr;
				}
				if (r == pos)
				{
					yr.erase(yr.find(r));
				}
				else if (r - pos < pos - l || r - pos == pos - l && dir == 1)
				{
					ans += r - pos;
					pos = r;
					dir = 1;
					yr.erase(yr.find(r));
				}
				else
				{
					ans += pos - l;
					pos = l;
					dir = -1;
					yr.erase(yr.find(l));
				}
			}
		}
		printf("Case %d: ", tt);
		cout << ans << endl;
	}
	return 0;
}
