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
#include <queue>
#include <iomanip>
#include <stack>
using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

#define foreach(e,x) for(__typeof(x.begin()) e=x.begin(); e!=x.end(); ++e)


const int N = 200000 + 10;
const int LOG = 19;

int n, m;
int tot, cnt;
vector<int> adj[N];
vector<pair<int, int> > chains[N];
int f[N], g[N], c[N];
int dfsOrd[N];
int depth[N];
int ordInDfs[N][2];
int father[N][LOG];

int jump(int u, int h)
{
	for(int i = 0; h; ++ i, h >>= 1) {
		if (h & 1)
			u = father[u][i];
	}
	return u;
}

int getLCA(int u, int v)
{
	if (depth[u] < depth[v]) 
		swap(u, v);
	u = jump(u, depth[u] - depth[v]);
	if (u == v) return u;
	for(int i = LOG - 1; i >= 0; -- i) {
		if (father[u][i] != father[v][i]) {
			u = father[u][i];
			v = father[v][i];
		}
	}
	return father[u][0];
}

int ask(int p)
{
	int ret = 0;
	for( ; p; p -= p & -p) {
		ret += c[p];
	}
	return ret;
}

void add(int p, int x)
{
	for( ; p < N; p += p & -p) {
		c[p] += x;
	}
}

int getSum(int u, int v, int lca)
{
	return ask(ordInDfs[u][0]) + ask(ordInDfs[v][0]) - 2 * ask(ordInDfs[lca][0]);
}

stack<int> S;
int it[N];

void dfs(int u)
{
	dfsOrd[cnt ++] = u;
	ordInDfs[u][0] = ++ tot;
	S.push(u);
	it[u]=0;
	while(!S.empty()){
		int x=S.top();
		if(it[x]==int(adj[x].size())){
			S.pop();
			ordInDfs[x][1]=++tot;
		}
		else{
			int y=adj[x][it[x]++];
			if(father[x][0]!=y){
				dfsOrd[cnt ++] = y;
				ordInDfs[y][0] = ++ tot;
				S.push(y);
				depth[y]=depth[x]+1;
				father[y][0]=x;
				it[y]=0;
			}
		}
	}
}

void solve() {
	cin >> n >> m;
	int u, v;
	for(int i = 1; i < n; ++ i) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	father[0][0] = -1;
	tot = 0;
	cnt = 0;
	depth[0] = 0;
	dfs(0);
	father[0][0] = 0;
	for(int j = 1; j < LOG; ++ j) {
		for(int i = 0; i < n; ++ i) {
			father[i][j] = father[father[i][j - 1]][j - 1];
		}
	}
	for(int i = 0; i < m; ++ i) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		int lca = getLCA(u, v);
		chains[lca].push_back(make_pair(u, v));
	}
	for(int i = 0; i < n; ++ i) {
		f[i] = g[i] = 0;
	}

	int x, y;
	int ret = 0;
	for(int t = n - 1; t >= 0; -- t) {
		u = dfsOrd[t];
		f[u] = g[u];
		foreach(it, chains[u]) {
			x = it->first;
			y = it->second;
			f[u] = max(f[u], getSum(x, y, u) + g[u] + 1);
		}
		ret = max(ret, f[u]);
		if (u) {
			g[father[u][0]] += f[u];
		}
		add(ordInDfs[u][0], g[u] - f[u]);
		add(ordInDfs[u][1], f[u] - g[u]);
	}
	cout << ret << endl;
}

int main() {
	solve();
	return 0;
}
