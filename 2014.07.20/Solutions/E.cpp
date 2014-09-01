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

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

const int N = 1000 + 10;
const int INF = 1000000000 + 10;

int n, m;
int distS[N], distT[N];
int father[N];
int layer[N];
int onPath[N];
int ret[N];
vector<pair<int, int> > events[N];
map<int, int> cnt;
vector<int> children[N];
vector<pair<int, int> > adj[N];

void dij(int s, int *dist)
{
	static int in[N];
	for(int i = 0; i < n; ++ i) {
		in[i] = false;
		dist[i] = INF;
		father[i] = -1;
	}
	dist[s] = 0;
	priority_queue<pair<int, int> > que;
	que.push(make_pair(0, s));
	for( ; que.size(); ) {
		int u = que.top().second;
		que.pop();
		if (in[u]) continue;
		in[u] = true;
		for(int i = 0; i < (int)adj[u].size(); ++ i) {
			int v = adj[u][i].first;
			if (dist[v] > dist[u] + adj[u][i].second) {
				dist[v] = dist[u] + adj[u][i].second;
				father[v] = u;
				que.push(make_pair(-dist[v], v));
			}
		}
	}
}

void dfs(int u, int on, int depth)
{
	layer[u] = depth;
	if (on) {
		for(int i = 0; i < (int)children[u].size(); ++ i) {
			int v = children[u][i];
			if (onPath[v]) {
				dfs(v, true, depth + 1);
			} else {
				dfs(v, false, depth);
			}
		}
	} else {
		for(int i = 0; i < (int)children[u].size(); ++ i) {
			int v = children[u][i];
			dfs(v, false, depth);
		}
	}
}

void update(pair<int, int> c)
{
	if (c.first == 1) {
		cnt[c.second] ++;
	} else {
		-- cnt[c.second];
		if (! cnt[c.second]) {
			cnt.erase(c.second);
		}
	}
}

void solve() {
	cin >> n >> m;
	for(int i = 0; i < n; ++ i) {
		adj[i].clear();
		children[i].clear();
		onPath[i] = false;
	}
	int u, v, w;
	for(int i = 0; i < m; ++ i) {
		scanf("%d%d%d", &u, &v, &w);
		-- u, -- v;
		adj[u].push_back(make_pair(v, w));
		adj[v].push_back(make_pair(u, w));
	}
	dij(n - 1, distT);
	if (distT[0] == INF) {
		cout << -1 << endl;
		return;
	}
	dij(0, distS);

	vector<int> path;
	for(u = n - 1; u != 0; ) {
		path.push_back(u);
		u = father[u];
	}
	path.push_back(0);
	reverse(path.begin(), path.end());

	for(int i = 0; i < (int)path.size(); ++ i) {
		onPath[path[i]] = true;
	}

	for(int i = 0; i < n; ++ i) {
		if (father[i] < 0) continue;
		children[father[i]].push_back(i);
	}

	dfs(0, 1, 0);

	for(int i = 0; i < (int)path.size(); ++ i)
		events[i].clear();

	for(int i = 0; i < n; ++ i) {
		int u = i;
		if (distS[u] == INF) continue;
		int flag = onPath[u];
		for(int j = 0; j < (int)adj[u].size(); ++ j) {
			int v = adj[u][j].first;
			if (layer[v] >= layer[u]) continue;
			if (flag && onPath[v] && distS[v] + adj[u][j].second == distS[u]) {
				flag = false;
				continue;
			}
			int w = adj[u][j].second + distS[v] + distT[u];
			int l = layer[v];
			int r = layer[u];
			events[r].push_back(make_pair(-1, w));
			events[l].push_back(make_pair(1, w));
		}
	}

	for(int i = 0; i < (int)path.size(); ++ i)
		sort(events[i].begin(), events[i].end());
	cnt.clear();

	int answer = -2;
	for(int i = 0; i + 1 < (int)path.size(); ++ i) {
		for(int j = 0; j < (int)events[i].size(); ++ j) {
			update(events[i][j]);
		}
		ret[i] = -1;
		if (cnt.size()) {
			ret[i] = cnt.begin()->first;
		}
		if (answer == -2) {
			answer = ret[i];
			continue;
		}
		if (answer == -1) continue;
		if (answer < ret[i] || ret[i] == -1) {
			answer = ret[i];
		}
	}
	cout << answer << endl;
}

int main() {
	int test;
	cin >> test;
	for(int i = 1; i <= test; ++ i) {
		solve();
	}
	return 0;
}
