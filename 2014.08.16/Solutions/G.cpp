#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int e[10][10][10];
int d[10][10][10];
int ans[5 * 5 * 5 + 5][3];
int f[24][3], tot = 0;
int re[4][3] = {{-2, -1, 0}, 
				{-2, 0, 1},
				{-1, 0, 2},
				{0, 1, 2}};
int a, b, c, all;
int la, ra, lb, rb, lc, rc;
int flag = 0;

void dfs(int x, int y, int z, int v) {
	e[x][y][z] = 0;
	ans[v][0] = x, ans[v][1] = y, ans[v][2] = z;
	if (v == all) {
		flag = 1;
		return;
	}
	v++;
	int x1, y1, z1, see = -1;
	for (int i = 0; i < tot; i++) {
		x1 = x + f[i][0], y1 = y + f[i][1], z1 = z + f[i][2];
		d[x1][y1][z1]--;
		if (e[x1][y1][z1] == 1 && d[x1][y1][z1] == 0) {
			if (see == -1) {
				see = i;
			} else {
				see = tot;
			}
		}
	}
	if (see == -1) {
		for (int i = 0; i < tot; i++) {
			x1 = x + f[i][0], y1 = y + f[i][1], z1 = z + f[i][2];
			if (e[x1][y1][z1] == 1) {
				dfs(x1, y1, z1, v);
				if (flag == 1) {
					return;
				}
			}
		}
	} else if (see < tot) {
		x1 = x + f[see][0], y1 = y + f[see][1], z1 = z + f[see][2];
		if (e[x1][y1][z1] == 1) {
			dfs(x1, y1, z1, v);
			if (flag == 1) {
				return;
			}
		}
	}
	for (int i = 0; i < tot; i++) {
		x1 = x + f[i][0], y1 = y + f[i][1], z1 = z + f[i][2];
		d[x1][y1][z1]++;
	}
	e[x][y][z] = 1;
	return;
}


int main() {
	for (int i = 0; i < 4; i++) {
		do {
			for (int j = 0; j < 3; j++) {
				f[tot][j] = re[i][j];
			}
			tot++;
		} while(next_permutation(re[i], re[i] + 3));
	}
	scanf("%d%d%d", &a, &b, &c);
	flag = 0;
	all = a * b * c;
	la = lb = lc = 3;
	ra = a + 2, rb = b + 2, rc = c + 2;
	memset(e, 0, sizeof(e));
	memset(d, 0, sizeof(d));
	for (int i = la; i <= ra; i++) {
		for (int j = lb; j <= rb; j++) {
			for (int k = lc; k <= rc; k++) {
				e[i][j][k] = 1;
			}
		}
	}
	bool useless = false;
	for (int i = la; i <= ra; i++) {
		for (int j = lb; j <= rb; j++) {
			for (int k = lc; k <= rc; k++) {
				for (int l = 0; l < tot; l++) {
					d[i][j][k] += e[i + f[l][0]][j + f[l][1]][k + f[l][2]];
				}
				if (d[i][j][k] == 0 && (i != 3 || j != 3 || k != 3)) {
					useless = true;
				}
			}
		}
	}
	if (!useless) {
		dfs(3, 3, 3, 1);
	}
	if (flag == 0) {
		printf("NO\n");
	} else {
		printf("YES\n");
		for (int i = 1; i <= all; i++) {
			printf("%d %d %d\n", ans[i][0] - 2, ans[i][1] - 2, ans[i][2] - 2);
		}
	}
	return 0;
}

