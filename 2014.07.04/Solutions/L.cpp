#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cassert>
#include <bitset>
#include <numeric>

using namespace std;

const int MAXN = 10;
const int MAXM = 10;
const int MAXP = MAXN * MAXM;
const double EPS = 1e-9;
const pair<int, int> DIRECT[4] = {make_pair(0, -1), make_pair(-1, 0), make_pair(1, 0), make_pair(0, 1)};

int height[MAXN][MAXM], d[MAXN][MAXM];
int code[MAXN][MAXM], solve[MAXP];
double eq_A[MAXP][MAXP];
double eq_b[MAXP], expect[MAXP];

pair<int, int> operator+ (const pair<int, int> &a, const pair<int, int> &b) {
	return make_pair(a.first + b.first, a.second + b.second);
}

bool valid(int n, int m, pair<int, int> p) {
	if (p.first < 0 || p.first >= n) {
		return false;
	}
	if (p.second < 0 || p.second >= m) {
		return false;
	}
	return true;
}

bool h_condition(int h, int x, int y, int nx, int ny) {
	if (height[x][y] > h || height[nx][ny] > h) {
		return false;
	}
	if (height[x][y] == h && height[nx][ny] == h) {
		return false;
	}
	return true;
}

bool stamp[MAXN][MAXM];

void dfs(int h, int x, int y, int n, int m) {
	stamp[x][y] = true;
	for (int k = 0; k < 4; ++k) {
		int nx = x + DIRECT[k].first;
		int ny = y + DIRECT[k].second;
		if (0 <= nx && nx < n && 0 <= ny && ny < m && h_condition(h, x, y, nx, ny)) {
			if (!stamp[nx][ny]) {
				dfs(h, nx, ny, n, m);
			}
		}
	}
}

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				scanf("%d", height[i] + j);
				code[i][j] = i * m + j;
				stamp[i][j] = false;
				d[i][j] = 0;
			}
		}
		int init_h = height[0][0];
		dfs(init_h, 0, 0, n, m);
		if (!stamp[n - 1][m - 1]) {
			puts("Never reach!");
			continue;
		}
		for (int i = 0; i < n * m; ++i) {
			for (int j = 0; j < n * m; ++j) {
				eq_A[i][j] = 0.0;
			}
			eq_b[i] = 0.0;
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				for (int k = 0; k < 4; ++k) {
					pair<int, int> pos = make_pair(i, j);
					pair<int, int> n_p = pos + DIRECT[k];
					if (valid(n, m, n_p)) {
						if ((i != n - 1 || j != m - 1) && h_condition(init_h, i, j, n_p.first, n_p.second)) {
							++d[i][j];
						}
					}
				}
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				for (int k = 0; k < 4; ++k) {
					pair<int, int> pos = make_pair(i, j);
					pair<int, int> n_p = pos + DIRECT[k];
					if (valid(n, m, n_p)) {
						int h = height[i][j];
						int n_h = height[n_p.first][n_p.second];
						if ((i != n - 1 || j != m - 1) && h_condition(init_h, i, j, n_p.first, n_p.second)) {
							double t;
							if (h == n_h) {
								double v = sqrt(20.0 * (init_h - h));
								t = 1.0 / v;
							}
							else {
								double v1 = sqrt(20.0 * (init_h - h));
								double v2 = sqrt(20.0 * (init_h - n_h));
								double alpha = atan(fabs((double)h - n_h));
								double a = 10.0 * sin(alpha);
								t = fabs(v1 - v2) / a;
							}
							eq_A[code[i][j]][code[n_p.first][n_p.second]] += 1.0 / d[i][j];
							eq_b[code[i][j]] -= t / d[i][j];
						}
					}
				}
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (d[i][j] > 0) {
					eq_A[code[i][j]][code[i][j]] -= 1.0;
				}
			}
		}
		eq_A[n * m - 1][n * m - 1] = 1.0;

		/*for (int i = 0; i < n * m; ++i) {
			for (int j = 0; j < n * m; ++j) {
				printf("%.6f, ", eq_A[i][j]);
			}
			printf("%.6f\n", eq_b[i]);
		}*/

		int e = 0;
		for (int pivot = 0; pivot < n * m; ++pivot) {
			int r = e;
			for (int i = e + 1; i < n * m; ++i) {
				if (fabs(eq_A[i][pivot]) > fabs(eq_A[r][pivot])) {
					r = i;
				}
			}
			if (fabs(eq_A[r][pivot]) < EPS) {
				continue;
			}
			for (int i = 0; i < n * m; ++i) {
				swap(eq_A[e][i], eq_A[r][i]);
			}
			swap(eq_b[e], eq_b[r]);
			for (int i = e + 1; i < n * m; ++i) {
				double coef = eq_A[i][pivot] / eq_A[e][pivot];
				for (int j = pivot; j < n * m; ++j) {
					eq_A[i][j] -= eq_A[e][j] * coef;
				}
				eq_b[i] -= eq_b[e] * coef;
			}
			solve[e++] = pivot;
		}

		for (int i = e - 1; i >= 0; --i) {
			int pivot = solve[i];
			expect[pivot] = eq_b[i] / eq_A[i][pivot];
			for (int j = 0; j < i; ++j) {
				eq_b[j] -= eq_A[j][pivot] * expect[pivot];
			}
		}

		printf("%.9f\n", expect[0]);
	}
	return 0;
}
