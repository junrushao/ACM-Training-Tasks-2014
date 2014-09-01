#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int f[10][7] = {
{1, 1, 1, 0, 1, 1, 1},
{0, 0, 1, 0, 0, 1, 0},
{1, 0, 1, 1, 1, 0, 1},
{1, 0, 1, 1, 0, 1, 1},
{0, 1, 1, 1, 0, 1, 0},
{1, 1, 0, 1, 0, 1, 1},
{1, 1, 0, 1, 1, 1, 1},
{1, 0, 1, 0, 0, 1, 0},
{1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 0, 1, 1} };
bool check(int a[7], int b[7]) {
	int i;
	for (i = 0; i < 7; i++) {
		if ( (a[i] == 0 && b[i] == 1) || (a[i] == 1 && b[i] == 0) ) {
			break;
		}
	}
	return i >= 7;
}
bool check_empty(int b[7]) {
	int i;
	for (i = 0; i < 7; i++) {
		if ( b[i] == 1) {
			break;
		}
	}
	return i >= 7;
}
int v(char c) {
	if (c == '.') return 0;
	if (c == '-' || c == '|') return 1;
	return 2;
}
char s[5][100], c[100];
int a[25], g[25][3][7], now[3][7];
void read(int a[7], int x, int y) {
	a[0] = v(s[x + 0][y + 1]);
	a[1] = v(s[x + 1][y + 0]);
	a[2] = v(s[x + 1][y + 2]);
	a[3] = v(s[x + 2][y + 1]);
	a[4] = v(s[x + 3][y + 0]);
	a[5] = v(s[x + 3][y + 2]);
	a[6] = v(s[x + 4][y + 1]);
	return;
}
void fread(int a[7], int x) {
	int i;
	for (i = 0; i < 7; i++) {
		a[i] = f[x][i];
	}
	return;
}
int main() {
	while (1) {
		int n = 0, end = 0, t, xt, i, j, k, flag;
		while (scanf("%d", &t) == 1) {
			a[++n] = t;
			gets(c);
			for (i = 0; i < 5; i++) {
				gets(s[i]);
			}
			for (i = j = 0; i < 3; i++, j += 3) {
				read(g[n][i], 0, j);
			}
		}
		gets(c);
		if (c[0] == '$') {
			end = 1;
		}
		vector<int> ans;
		ans.clear();
		for (xt = 0; xt <= 999; xt++) {
			for (i = 1; i <= n; i++) {
				t = (a[i] + xt) % 1000;
				flag = 1;
				for (j = 2; j >= 0; j--) {
					fread(now[j], t % 10);
					t /= 10;
					if (!check(now[j], g[i][j])) {
						flag = 0;
						break;
					}
					if (t == 0) {
						for (int k = j - 1; k >= 0; --k) {
							if (!check_empty(g[i][k])) {
								flag = 0;
								break;
							}
						}
						break;
					}
				}
				if (flag == 0) {
					break;
				}
			}
			if (i > n) {
				ans.push_back(xt);
				//printf("%d\n", xt);
			}
		}
		if ((int)ans.size() == 1) {
			printf("%d\n", ans[0]);
		} else {
			printf("? %d\n", (int)ans.size());
		}
		if (end == 1) {
			return 0;
		}
	}
	return 0;
}

