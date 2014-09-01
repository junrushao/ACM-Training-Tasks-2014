#include<cassert>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 105, INF = 1000000000;

int n, m, k;

int g[N][N];

int match[N];

int dis[N];
bool vis[N];

vector<int> stack;

bool find(int u) {
	stack.push_back(u);
	if (vis[u]) {
		return true;
	}
	vis[u] = true;
	for (int i = 0; i < k; ++i) {
		int v = i;
		if (vis[v] || v == u || v == match[u]) {
			continue;
		}
		int t = match[v];
		if (dis[t] > dis[u] + g[u][v] - g[v][t]) {
			dis[t] = dis[u] + g[u][v] - g[v][t];
			if (find(t)) {
				return true;
			}
		}
	}
	stack.pop_back();
	vis[u] = false;
	return false;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				g[i][j] = INF;
			}
			g[i][i] = 0;
		}
		for (int i = 0; i < m; ++i) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			--u, --v;
			g[u][v] = g[v][u] = min(g[u][v], w);
		}
		static int id = 0;
		printf("Case %d: ", ++id);
		if (k & 1) {
			printf("Impossible\n");
		} else {
			for (int k = 0; k < n; ++k) {
				for (int i = 0; i < n; ++i) {
					for (int j = 0; j < n; ++j) {
						g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
					}
				}
			}
			for (int i = 0; i < k; ++i) {
				g[i][i] = INF;
			}
			for (int i = 0; i < k; i += 2) {
				match[i] = i + 1;
				match[i + 1] = i;
			}
			while (true) {
				memset(dis, 0, sizeof(int) * k);
				memset(vis, 0, sizeof(bool) * k);
				bool update = false;
				for (int i = 0; i < k; ++i) {
					if (find(i)) {
						int j = stack.size() - 2;
						while (stack[j] != stack.back()) {
							--j;
						}
						stack.pop_back();
						vector<int> tmp;
						for (int i = j; i < (int)stack.size(); ++i) {
							int u = stack[i];
							tmp.push_back(match[u]);
							tmp.push_back(u);
						}
						tmp.push_back(tmp.front());
						for (int i = 1; i + 1 < (int)tmp.size(); i += 2) {
							int u = tmp[i], v = tmp[i + 1];
							match[u] = v, match[v] = u;
						}
						stack.clear();
						update = true;
						break;
					}
				}
				if (!update) {
					break;
				}
			}
			int ans = 0;
			for (int i = 0; i < k; ++i) {
				ans += g[i][match[i]];
			}
			printf("%d\n", ans >> 1);
		}
	}
	return 0;
}

