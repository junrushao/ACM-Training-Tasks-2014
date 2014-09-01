#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 30;

int n, r;

int x[N], y[N];

vector<int> edge[N];

int ord[N];

vector<int> ans, stack;

bool mem[N][N];
bool taken[N];

void go(int d) {
	if (stack.size() >= ans.size()) {
		return;
	}
	if (d == n) {
		ans = stack;
		return;
	}
	int u = ord[d];
	if (taken[u]) {
		go(d + 1);
	} else {
		for (int i = 0; i < (int)edge[u].size(); ++i) {
			int v = edge[u][i];
			for (int j = 0; j < (int)edge[v].size(); ++j) {
				int w = edge[v][j];
				mem[d][w] = taken[w];
				taken[w] = true;
			}
			stack.push_back(v);
			go(d + 1);
			stack.pop_back();
			for (int j = 0; j < (int)edge[v].size(); ++j) {
				int w = edge[v][j];
				taken[w] = mem[d][w];
			}
		}
	}
}

bool by_dgr(int i, int j) {
	return edge[i].size() < edge[j].size();
}

int main() {
	scanf("%d%d", &n, &r);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", x + i, y + i);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int delta = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
			if (delta <= r * r) {
				edge[i].push_back(j);
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		ord[i] = i;
		ans.push_back(i);
	}
	sort(ord, ord + n, by_dgr);
	go(0);
	printf("%d\n", (int)ans.size());
	sort(ans.begin(), ans.end());
	for (int i = 0; i < (int)ans.size(); ++i) {
		printf("%d%c", ans[i] + 1, i == (int)ans.size() - 1 ? '\n' : ' ');
	}
	return 0;
}

