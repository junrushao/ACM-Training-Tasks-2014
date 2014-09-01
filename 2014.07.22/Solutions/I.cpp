#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int N = 1005;

int n, m, hx, hy, tot, end;
int next[N * N], succ[N * N], rx[N * N], ry[N * N], type[N * N];
int nextX[N * N], nextY[N * N];
int hashCnt, hashNow[N][N], s[N][N];
char str[N][N];

void del(int i) {
	//printf("%d\n", i);
	succ[next[i]] = succ[i];
	next[succ[i]] = next[i];
}

void getNext(const int &x, const int &y, int &nx, int &ny) {
	if (x == hx) {
		if (y < hy) {
			nx = x;
			ny = y + 1;
		} else {
			nx = x;
			ny = y - 1;
		}

		return;
	}

	if (y == hy) {
		if (x < hx) {
			nx = x + 1;
			ny = y;
		} else {
			nx = x - 1;
			ny = y;
		}

		return;
	}

	if (x < hx) {
		nx = x + 1;
		if (y < hy) {
			ny = y + 1;
		} else {
			ny = y - 1;
		}
	} else {
		nx = x - 1;
		if (y < hy) {
			ny = y + 1;
		} else {
			ny = y - 1;
		}
	}
}


int work() {
	if (scanf("%s", str[1] + 1) != 1) {
		return 0;
	}

	n = 1;
	while (1) {
		n++;
		scanf("%s", str[n] + 1);
		if (str[n][1] == '$') {
			break;
		}
	}

	n--;
	m = strlen(str[1] + 1);
	tot = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char ch = str[i][j];
			if (ch == '@') {
				hx = i, hy = j;
			} else if (ch == '+') {
				str[i][j] = '.';
				rx[++tot] = i;
				ry[tot] = j;
				type[tot] = 1;
			} else if (ch == '#') {
				str[i][j] = '.';
				rx[++tot] = i;
				ry[tot] = j;
				type[tot] = 2;
			}
		}
	}

	end = tot + 1;
	for (int i = 0; i < end; i++) {
		next[i] = i + 1;
		succ[i + 1] = i;
	}

	int ans = 0;
	while (next[0] != end) {
		hashCnt++;
		for (int i = next[0]; i != end; i = next[i]) {
			if (type[i] == 1 || type[i] == 2) {
				getNext(rx[i], ry[i], nextX[i], nextY[i]);
				int xx = nextX[i], yy = nextY[i];
				if ((xx == hx && yy == hy) || str[xx][yy] == '*') {
					del(i);
					if (xx == hx && yy == hy) {
						ans++;
					}
				} else {
					if (hashNow[xx][yy] == hashCnt) {
						s[xx][yy]++;
					} else {
						hashNow[xx][yy] = hashCnt;
						s[xx][yy] = 1;
					}
				}
			}
		}

		for (int i = next[0]; i != end; i = next[i]) {
			if (s[nextX[i]][nextY[i]] > 1) {
				del(i);
				str[nextX[i]][nextY[i]] = '*';
			} else {
				rx[i] = nextX[i];
				ry[i] = nextY[i];
			}
		}

		hashCnt++;
		for (int i = next[0]; i != end; i = next[i]) {
			if (type[i] == 1 || type[i] == 2) {
				if (type[i] == 1) {
					nextX[i] = rx[i], nextY[i] = ry[i];
				} else {
					getNext(rx[i], ry[i], nextX[i], nextY[i]);
				}

				int xx = nextX[i], yy = nextY[i];
				if ((xx == hx && yy == hy) || str[xx][yy] == '*') {
					del(i);
					if (xx == hx && yy == hy) {
						ans++;
					}
				} else {
					if (hashNow[xx][yy] == hashCnt) {
						s[xx][yy]++;
					} else {
						hashNow[xx][yy] = hashCnt;
						s[xx][yy] = 1;
					}
				}
			}
		}

		for (int i = next[0]; i != end; i = next[i]) {
			if (s[nextX[i]][nextY[i]] > 1) {
				del(i);
				str[nextX[i]][nextY[i]] = '*';
			} else {
				rx[i] = nextX[i];
				ry[i] = nextY[i];
			}
		}
	}

	printf("%d\n", ans);
	return 1;
}

int main() {
	while (work()) {}
	return 0;
}
