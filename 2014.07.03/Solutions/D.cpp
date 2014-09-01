#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

int tt, test, ans[5], pos[5];
string name[5] = {"Ja", "Sam", "Sha", "Sid", "Tan"};
map <string, int> id;
vector <string> v[5];

void solve() {
	int m, n, t, tot;
	string now, temp;
	for (int i = 0; i < 5;i++)
		ans[i] = 0, pos[i] = 0;
	scanf("%d %d", &m, &n);
	cin >> now;
	for (int i = 0; i < 5; i++)
	{
		v[i].clear();
		scanf("%d", &tot);
		for (int j = 1; j <= tot; j++)
		{
			cin >> temp;
			v[i].push_back(temp);
		}
	}

	t = 0;
	while (t < n)
	{
		ans[id[now]] += min(m, n - t);
		t += (m + 2);
		int last = id[now];
		now = v[last][pos[last]];
		pos[last] = (pos[last] + 1) % v[last].size();
	}

	for (int i = 0; i < 5; i++)
		printf("%s %d\n", name[i].c_str(), ans[i]);
}

int main() {
	for (int i = 0; i < 5;i++)
		id[name[i]] = i;
	scanf("%d", &test);
	while (test--)
	{
		printf("Case %d:\n", ++tt);
		solve();
	}

	return 0;
}

