#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cassert>
#include <set>
using namespace std;

const int N = 111;

int del[N], visit[N], times = 0, color[N], n;
vector<int> e[N];
vector<pair<int, int> > pairs;
set<pair<int, int> > edges;

int dfs(int dep) {
	if (dep < 0) {
		return 1;
	}
	int x = pairs[dep].second, mp[4] = {0};
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (color[y] != -1) {
			mp[color[y]] = 1;
		}
	}
	for(int i = 0; i < 4; i++) {
		if (mp[i]) {
			continue;
		}
		color[x] = i;
		if (dfs(dep - 1)) {
			return 1;
		}
	}
	return 0;
}

int main() {
	bool second = false;
	for(; scanf("%d", &n) == 1;) {
		if (second) {
			puts("");
		} else {
			second = true;
		}
		edges.clear();
		for(int i = 1; i <= n; i++) {
			e[i].clear();
		}
		static char buffer[N + 10];
		gets(buffer);
		while(gets(buffer)) {
			if (buffer[0] == 0) {
				break;
			} else {
				int a, b;
				sscanf(buffer, "%d-%d", &a, &b);
				if (a > b) {
					swap(a, b);
				}
				if (edges.count(make_pair(a, b))) {
					continue;
				}
				e[a].push_back(b);
				e[b].push_back(a);
				edges.insert(make_pair(a, b));
			}
		}
		pairs.clear();
		for(int i = 1; i <= n; i++) {
			pairs.push_back(make_pair((int)e[i].size(), i));
			color[i] = -1;
		}
		sort(pairs.begin(), pairs.end());
		dfs(n - 1);
		for(int x = 1; x <= n; x++) {
			for(int i = 0; i < (int)e[x].size(); i++) {
				if (color[x] == color[e[x][i]]) {
					assert(false);
				}
			}
		}
		for(int i = 1; i <= n; i++) {
			printf("%d %d\n", i, color[i] + 1);
		}
	}
	return 0;
}
