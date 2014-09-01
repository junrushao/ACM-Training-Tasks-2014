#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1005;
const int M = 2000005;

int e[M], succ[M], last[N], sum;
int n, tot, top, color;
int dfn[N], low[N], s[N], size[N], belong[N], deg[N], in[N];
char str[N];

void add(int a, int b) {
	e[++sum] = b, succ[sum] = last[a], last[a] = sum;
}

void dfs(int i) {
	dfn[i] = low[i] = ++tot;
	s[++top] = i;
	in[i] = 1;
	for (int x = last[i]; x; x = succ[x]) {
		int y = e[x];
		if (!dfn[y]) {
			dfs(y);
			low[i] = min(low[i], low[y]);
		} else if (in[y]) {
			low[i] = min(low[i], dfn[y]);
		}
	}

	if (dfn[i] == low[i]) {
		size[++color] = 0;
		deg[color] = 0;
		while (s[top] != i) {
			belong[s[top]] = color;
			size[color]++;
			in[s[top]] = 0;
			top--;
		}

		belong[s[top]] = color;
		size[color]++;
		in[s[top]] = 0;
		top--;
	}
}

void work() {
	for (int i = 1; i <= n; i++) {
		last[i] = 0;
		dfn[i] = low[i] = 0;
	}

	sum = 0;
	for (int i = 1; i < n; i++) {
		scanf("%s", str + i + 1);
		for (int j = i + 1; j <= n; j++) {
			if (str[j] == '1') {
				add(i, j);
			} else {
				add(j, i);
			}
		}
	}

	color = tot = top = 0;
	for (int i = 1; i <= n; i++) {
		if (dfn[i] == 0) {
			dfs(i);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int x = last[i]; x; x = succ[x]) {
			if (belong[i] != belong[e[x]]) {
				deg[belong[e[x]]] = 1;
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= color; i++) {
		if (deg[i] == 0) {
			ans += size[i];
		}
	}

	printf("%d\n", ans);
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		work();
	}

	return 0;
}

