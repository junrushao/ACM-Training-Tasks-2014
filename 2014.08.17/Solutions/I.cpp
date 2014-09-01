#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

const int N = 20000 + 10;
int n, m;
int top, tot;
int low[N], dfn[N], instack[N], stack[N];
int size[N];
long long ret[N];

vector<int> adj[N];

int tarjan(int u)
{
	++ tot;
	low[u] = dfn[u] = tot;
	instack[u] = true;
	stack[++ top] = u;
	size[u] = 1;
	
	int v;
	vector<int> vec;
	for(int i = 0; i < (int)adj[u].size(); ++ i) {
		v = adj[u][i];
		if (! dfn[v]) {
			int tmp = tarjan(v);
			low[u] = min(low[u], tmp);
			int sum = 0;
			if (tmp >= dfn[u]) {
				do {
					tmp = stack[top --];
					sum += size[tmp];	
				} while (tmp != v);
				vec.push_back(sum);
				size[u] += sum;
			}
		} else if (instack[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}

	ret[u] = (long long)(n - 1) * (n - 1);
	for(int i = 0; i < (int)vec.size(); ++ i) {
		ret[u] -= (long long)vec[i] * vec[i];
	}
	ret[u] -= (long long)(n - size[u]) * (n - size[u]);

	return low[u];
}

void solve() {
	int u, v;
	cin >> n >> m;
	for(int i = 0; i < m; ++ i) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	tot = 0, top = 0;
	tarjan(0);
	for(int i = 0; i < n; ++ i) {
		printf("%lld\n", ret[i] / 2 + n - 1);
	}
}

int main() {
	solve();
	return 0;
}
