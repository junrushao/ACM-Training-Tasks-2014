#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

const int N = 15 * 15;

int match[N], n, m, k, like[N][N], lower[N], need[N], visit[N]; 
vector<int> e[N * N];
int nn = 0;

int find(int x) {
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (visit[y])
			continue;
		visit[y] = 1;
		if (match[y] == 0 || find(match[y])) {
			match[y] = x;
			return true;
		}
	}
	return false;
}

bool dfs(int x, int totNeed) {
	if (totNeed > n)
		return false;
	if (x > m) {
		nn = 0;
		for(int i = 1; i <= m; i++) {
			for(int j = 1; j <= need[i]; j++) {
				e[++nn].clear();
				for(int k = 1; k <= n; k++) {
					if (like[i][k]) {
						e[nn].push_back(k);
					}
				}
			}
		}
		for(int i = 1; i <= n; i++)
			match[i] = 0;
		for(int i = 1; i <= nn; i++) {
			for(int j = 1; j <= n; j++) {
				visit[j] = 0;
			}
			if (!find(i))
				return false;
		}
		return true;
	}
	for(int i = 0; ; i++) {
		need[x] = i;
		if (dfs(x + 1, totNeed + i + max(0, lower[x] - i * k)))
			return true;
		if (i * k >= lower[x])
			break;
	}
	return false;
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		static int testCount = 0;
		scanf("%d %d %d", &n, &m, &k);
		for(int i = 1; i <= m; i++) {
			scanf("%d", &lower[i]);
		}	
		for(int i = 1; i <= m; i++)
			for(int j = 1; j <= n; j++)
				scanf("%d", &like[i][j]);
		
		printf("Case #%d: ", ++testCount);
		if (dfs(1, 0))
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}