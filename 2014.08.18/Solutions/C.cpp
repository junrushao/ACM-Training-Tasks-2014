#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

char buf[20];

int read() {
	scanf("%s", buf);
	int l = strlen(buf);
	int ret = 0;
	for (int i = 0; i + 1 < l; ++i) {
		ret = ret * 10 + buf[i] - '0';
	}
	return ret << 1 | (buf[l - 1] == 'h');
}

int n, m;
const int N = 35 << 1;
vector<int> edge[N], revEdge[N];

void addedge(int u, int v) {
	edge[u].push_back(v);
	revEdge[v].push_back(u);
}

bool vis[N];
vector<int> ord;

void dfs(int u) {
	vis[u] = true;
	for (int i = 0; i < (int)edge[u].size(); ++i) {
		int v = edge[u][i];
		if (vis[v]) {
			continue;	
		}
		dfs(v);
	}
	ord.push_back(u);
}

int cnt, col[N];

void dfsRev(int u) {
	col[u] = cnt;
	for (int i = 0; i < (int)revEdge[u].size(); ++i) {
		int v = revEdge[u][i];
		if (col[v]) {
			continue;
		}
		dfsRev(v);
	}
}

vector<int> ans;

bool SAT() {
	memset(vis, 0, sizeof(vis));
	ord.clear();
	for (int i = 0; i < n * 2; ++i) {
		if (!vis[i]) {
			dfs(i);
		}
	}
	cnt = 0;
	memset(col, 0, sizeof(col));
	for (int i = 0; i < n * 2; ++i) {
		int u = ord[n * 2 - 1 - i];
		if (col[u] == 0) {
			++cnt;
			dfsRev(u);
		}
	}
	for (int i = 0; i < n * 2; ++i) {
		if (col[i] == col[i ^ 1]) {
			return false;
		}
		if (col[i] > col[i ^ 1]) {
			ans.push_back(i);
		}
	}
	return true;
}

int main() {
	while (scanf("%d%d", &n, &m) == 2 && (n || m)) {
		for (int i = 0; i < n * 2; ++i) {
			edge[i].clear();
			revEdge[i].clear();
		}
		for (int i = 0; i < m; ++i) {
			int u = read(), v = read();
			if ((u ^ v) != 1) {
				addedge(u, v ^ 1);
				addedge(v, u ^ 1);
			}
		}
		addedge(0, 1);
		ans.clear();
		if (SAT()) {
			bool first = true;
			for (int i = 0; i < (int)ans.size(); ++i) {
				if (ans[i] == 1) {
					continue;
				}
				if (first) {
					first = false;
				} else {
					printf(" ");
				}
				printf("%d%c", ans[i] >> 1, (ans[i] & 1) ? 'w' : 'h');
			}
			printf("\n");
		} else {
			printf("bad luck\n");
		}
	}
	return 0;
}

