#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <bitset>
#include <string>
#define PQ priority_queue
#define OO 2147483647
#define Max(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((b) & FASTBUFFER | (a) & ~FASTBUFFER))
#define Min(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((a) & FASTBUFFER | (b) & ~FASTBUFFER))
#define Swap(a, b) (a ^= b, b ^= a, a ^= b)

int FASTBUFFER;

using namespace std;

const int N = 105;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int n, m, ans, a[N][N];

void dfs(int x, int y, int s, int now) {
	if (s >= ans) {
		return;
	}
	
	if (a[x][y] == 3) {
		ans = s;
		return;
	}
	
	if (now == -1) {
		for (int d = 0; d < 4; d++) {
			int xx = x + dx[d], yy = y + dy[d];
			if (xx < 1 || xx > n || yy < 1 || yy > m || a[xx][yy] == 1) {
				continue;
			}
			
			dfs(xx, yy, s + 1, d);
		}
	} else {
		int xx = x + dx[now], yy = y + dy[now];
		if (xx < 1 || xx > n || yy < 1 || yy > m) {
			return;
		}
		
		if (a[xx][yy] == 1) {
			a[xx][yy] = 0;
			dfs(x, y, s, -1);
			a[xx][yy] = 1;
		} else {
			dfs(xx, yy, s, now);
		}
	}
}

void work() {
	int x, y;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j]);
			if (a[i][j] == 2) {
				x = i, y = j;
			}
		}
	}
	
	ans = 11;
	dfs(x, y, 0, -1);
	if (ans == 11) {
		printf("-1\n");
	} else {
		printf("%d\n", ans);
	}
}

int main() {
	while (scanf("%d %d", &m, &n) == 2 && (n + m)) {
		work();
	}
	
	return 0;
}
