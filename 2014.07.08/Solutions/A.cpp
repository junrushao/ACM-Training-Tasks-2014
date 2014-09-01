#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

const int N = 111111;

int low[N], DFN[N], top, totColor, color[N], inStk[N], stk[N], tot;
int m, n;
vector<int> e[N];

void tarjan(int x) {
	DFN[x] = low[x] = ++tot;
	stk[++top] = x;
	inStk[x] = 1;
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (!DFN[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if (inStk[y]) {
			low[x] = min(low[x], DFN[y]);
		}
	}
	if (low[x] == DFN[x]) {
		++totColor;
		while(stk[top] != x) {
			color[stk[top]] = totColor;
			inStk[stk[top]] = 0;
			top--;
		}
		color[x] = totColor;
		inStk[x] = 0;
		top--;
	}
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; i++) {
			e[i].clear();
			DFN[i] = low[i] = color[i] = inStk[i] = 0;
		}		
		totColor = top = tot = 0;
		for(int i = 1; i <= m; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			e[a].push_back(b);
		}
		for(int i = 1; i <= n; i++)
			if (!DFN[i]) {
				tarjan(i);
			}
		int ans = 0;
		static int degree[N];
		for(int i = 1; i <= n; i++) {
			degree[i] = 0;
		}
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j < (int)e[i].size(); j++) {
				int y = e[i][j];
				if (color[i] != color[y])
					degree[color[y]]++;
			}
		}
		for(int i = 1; i <= totColor; i++)
			if (degree[i] == 0)
				ans++;
		printf("%d\n", ans);
	}
	return 0;
}