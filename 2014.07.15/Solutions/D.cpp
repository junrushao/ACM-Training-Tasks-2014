#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 2005;

int tot, top, color, n, test;
int x[N], y[N], d[N];
int dfn[N], low[N], s[N], belong[N], deg[N], in[N];
vector <int> v[N];

void dfs(int now) {
	dfn[now] = low[now] = ++tot;
	s[++top] = now;
	in[now] = 1;
	for (vector <int> :: iterator it = v[now].begin(); it != v[now].end(); ++it) {
		int y = *it;
		if (dfn[y] == 0)
			dfs(y), low[now] = min(low[now], low[y]);
		else if (in[y] == 1)
			low[now] = min(low[now], dfn[y]);
	}

	if (dfn[now] == low[now]) {
		deg[++color] = 0;
		while (s[top] != now) {
			belong[s[top]] = color;
			in[s[top]] = 0;
			top--;
		}

		belong[s[top]] = color;
		in[s[top]] = 0;
		top--;
	}
}

void work() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d", &x[i], &y[i], &d[i]);
		v[i].clear();
		dfn[i] = low[i] = in[i] = 0;
	}

	tot = top = color = 0;
	for (int i = 1; i <= n; i++) {
		int dnow = d[i];
		if (dnow & 1)
			dnow--;
		dnow /= 2;
		for (int j = 1; j <= n; j++) {
			if (j != i && max(abs(x[i] - x[j]), abs(y[i] - y[j])) <= dnow)
				v[i].push_back(j);
		}
	}

	for (int i = 1; i <= n; i++) {
		if (dfn[i] == 0)
			dfs(i);
	}

	for (int i = 1; i <= n; i++) {
		for (vector <int> :: iterator it = v[i].begin(); it != v[i].end(); ++it)
			if (belong[*it] != belong[i])
				deg[belong[*it]]++;
	}

	int ans = 0;
	for (int i = 1; i <= color; i++) {
		if (deg[i] == 0)
			ans++;
	}

	printf("%d\n", ans);
}

int main() {
	scanf("%d", &test);
	while (test--)
		work();
	return 0;
}

