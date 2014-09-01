#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

const int N = 111111 * 2;

vector<int> e[N];

int n, m;
vector<pair<int, int> > edges;
int visit[N * 2];
int father[N], fa[N], dep[N];

int find(int x) {
	int p = x;
	while(p != father[p]) {
		p = father[p];
	}
	while(x != p) {
		int t = father[x];
		father[x] = p;
		x = t;
	}
	return p;
}

int insert(int a, int b) {
	int result = 0;
	while(1) {
		a = find(a);
		b = find(b);
		if (a == b) {
			return result;
		}
		if (dep[a] < dep[b]) {
			swap(a, b);
		}
		father[a] = fa[a];
		result++;
	}
}

int main() {
	while(scanf("%d %d", &n, &m) == 2 && (n || m)) {
		edges.clear();
		for(int i = 0; i < m; i++) {
			int a, b;
			visit[i] = 0;
			scanf("%d %d", &a, &b);
			edges.push_back(make_pair(a, b));
		}
		for(int i = 1; i <= n; i++) {
			father[i] = i;
			e[i].clear();
		}
		for(int i = 0; i < m; i++) {
			int a = find(edges[i].first), b = find(edges[i].second);
			if (a != b) {
				e[edges[i].first].push_back(edges[i].second);
				e[edges[i].second].push_back(edges[i].first);
				father[a] = b;
				visit[i] = 1;
			}
		}
		vector<int> queue;
		queue.push_back(1);
		fa[1] = 0;
		dep[1] = 0;
		for(int head = 0; head < (int)queue.size(); head++) {
			int x = queue[head];
			for(int i = 0; i < (int)e[x].size(); i++) {
				int y = e[x][i];
				if (y == fa[x]) {
					continue;
				}
				queue.push_back(y);
				dep[y] = dep[x] + 1;
				fa[y] = x;
			}
		}
		int ans = n - 1;
		for(int i = 1; i <= n; i++) {
			father[i] = i;
		}
		for(int i = 0; i < m; i++) {
			if (!visit[i]) {
				ans -= insert(edges[i].first, edges[i].second);
			}
		}
		
		static int testCount = 0;
		printf("Case %d:\n", ++testCount);
		int q;
		scanf("%d", &q);
		for(int i = 0; i < q; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			ans -= insert(a, b);
			printf("%d\n", ans);
		}
		puts("");
	}
	return 0;
}
