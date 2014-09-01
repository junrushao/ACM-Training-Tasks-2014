#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 105;

int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct Matrix {
	int n;
	long double v[N][N];

	Matrix (const int &n = 64) : n(n) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				v[i][j] = 0.0;
			}
		}
	}

	friend Matrix operator * (Matrix a, Matrix b) {
		Matrix c(a.n);
		for (int i = 1; i <= c.n; i++) {
			for (int j = 1; j <= c.n; j++) {
				for (int k = 1; k <= c.n; k++) {
					c.v[i][j] += a.v[i][k] * b.v[k][j];
				}
			}
		}

		return c;
	}

	void unify() {
		long double sum = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				sum += v[i][j];
			}
		}
		sum /= 64;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				v[i][j] /= sum;
			}
		}
	}
} trans;

int a[N][N], id[N][N], tot;

int main() {
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			scanf("%d", &a[i][j]);
			id[i][j] = ++tot;
		}
	}
	
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			int s = 0;
			for (int d = 0; d < 8; d++) {
				int x = i + dx[d], y = j + dy[d];
				if (x < 1 || x > 8 || y < 1 || y > 8) {
					continue;
				}

				s += a[x][y];
			}

			for (int d = 0; d < 8; d++) {
				int x = i + dx[d], y = j + dy[d];
				if (x < 1 || x > 8 || y < 1 || y > 8) {
					continue;
				}

				trans.v[id[i][j]][id[x][y]] = (long double)a[x][y] / (long double)s;
			}
		}
	}

	for (int i = 1; i <= 100; i++) {
		trans = trans * trans;
		trans.unify();
	}

	for (int i = 1; i <= tot; i++) {
		long double ans = 0.0;
		for (int j = 1; j <= tot; j++) {
			ans += trans.v[j][i];
		}

		if (i % 8 == 0) {
			printf("%.15f\n", (double)ans / 64.0);
		} else {
			printf("%.15f ", (double)ans / 64.0);
		}
	}

	return 0;
}

