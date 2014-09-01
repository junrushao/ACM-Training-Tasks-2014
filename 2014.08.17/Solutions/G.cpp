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

const int N = 1000 + 10;
int n, m;
int a[N];
int b[N][N];
int to[N];
vector<int> adj[N];
vector<int> vec[N];
int top, id, totc;
int low[N], dfn[N], instack[N], stack[N], color[N];

int tarjan(int u)
{
	++ id;
	low[u] = dfn[u] = id;
	instack[u] = true;
	stack[++ top] = u;

	int v;
	for(int i = 0; i < (int)adj[u].size(); ++ i) {
		v = adj[u][i];
		if (! dfn[v]) {
			low[u] = min(low[u], tarjan(v));
		} else if (instack[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}

	if (low[u] == dfn[u]) {
		do {
			v = stack[top --];
			color[v] = totc;
			instack[v] = false;
		} while (v != u);
		totc ++;
	}

	return low[u];
}


void solve() {
	cin >> n;
	for(int i = 0; i < n; ++ i) {
		cin >> a[i];
	}
	cin >> m;
	for(int i = 0; i < m; ++ i) {
		for(int j = 0; j < n; ++ j) {
			scanf("%d", &b[i][j]);
		}
	}
	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j < m; ++ j) {
			if (b[j][i] == a[i]) {
				vec[i].push_back(j);
			}
		}
	}
	int tot = m;
	for(int i = 0; i < n; ++ i) {
		if (vec[i].size() == 0) {
			cout << "NO" << endl;
			return;
		}
		to[i * 2 + 1] = i * 2;
		to[i * 2] = i * 2 + 1;

		if (vec[i].size() == 1) {
			vec[i].push_back(tot ++);
			adj[i * 2 + 1].push_back(i * 2);
		}
	}

	for(int i = 0; i < n; ++ i) {
		for(int di = 0; di < 2; ++ di) {
			int u = vec[i][di];
			if (u >= m) continue;
			for(int j = i + 1; j < n; ++ j) {
				for(int dj = 0; dj < 2; ++ dj) {
					int v = vec[j][dj];
					if (v >= m) continue;
					int flag = false;
					for(int k = 0; k < n; ++ k) {
						if (b[u][k] == b[v][k]) {
							flag = true;
							break;
						}
					}
					if (flag) {
						adj[i * 2 + di].push_back(j * 2 + 1 - dj);
						adj[j * 2 + dj].push_back(i * 2 + 1 - di);
					}
				}
			}
		}
	}

	id = 0, top = 0; totc = 0;
	for(int i = 0; i < 2 * n; ++ i) {
		if (dfn[i] == 0) {
			tarjan(i);
		}
	}

	for(int i = 0; i < n; ++ i) {
		int u = i * 2;
		int v = i * 2 + 1;
		if (color[u] == color[v]) {
			cout << "NO" << endl;
			return;
		}
	}
	puts("YES");
	for(int i = 0; i < n; ++ i) {
		int u = i * 2;
		int v = i * 2 + 1;
		if (color[u] < color[v]) {
			cout << vec[i][0] + 1;
		} else {
			cout << vec[i][1] + 1;
		}
		if (i == n - 1) cout << endl;
		else cout << ' ';
	}
}

int main() {
	solve();
	return 0;
}
