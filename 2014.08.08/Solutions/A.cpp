#include <cassert>
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, a, b;

const int N = 33;

struct Matrix {
	int a[N][N];

	Matrix() {
		memset(a, 0, sizeof(a));
	}

	int* operator[] (const int &i) {
		return a[i];
	}

	const int* operator[] (const int &i) const {
		return a[i];
	}

	Matrix inverse() {
		Matrix ret, bak = *this;
		for (int i = 0; i < m; ++i) {
			ret[i][i] = 1;
		}
		for (int i = 0; i < m; ++i) {
			if (!bak[i][i]) {
				for (int j = i + 1; j < m; ++j) {
					if (bak[j][i]) {
						for (int k = 0; k < m; ++k) {
							swap(bak[j][k], bak[i][k]);
							swap(ret[j][k], ret[i][k]);
						}
						break;
					}
				}
			}
			assert(bak[i][i]);
			for (int j = 0; j < m; ++j) {
				if (j != i && bak[j][i]) {
					for (int k = 0; k < m; ++k) {
						bak[j][k] ^= bak[i][k];
						ret[j][k] ^= ret[i][k];
					}
				}
			}
		}
		return ret;
	}
};

Matrix operator * (const Matrix &a, const Matrix &b) {
	Matrix ret;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			for (int k = 0; k < m; ++k) {
				ret[i][j] ^= a[i][k] & b[k][j];
			}
		}
	}
	return ret;
}

struct Vector {
	int a[N];

	Vector() {
		memset(a, 0, sizeof(a));
	}

	int& operator[] (const int &i) {
		return a[i];
	}

	const int operator[] (const int &i) const {
		return a[i];
	}

	int hash() {
		int ret = 0;
		for (int i = 0; i < n; ++i) {
			ret = ret << 1 | a[i];
		}
		return ret;
	}
};

Vector source, target;

Vector operator * (const Vector &a, const Matrix &b) {
	Vector ret;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			ret[j] ^= a[i] & b[i][j];
		}
	}
	return ret;
}

void debug(Vector v) {
	for (int i = 0; i < m; ++i) {
		printf("%d%c", v[i], i == m - 1 ? '\n' : ' ');
	}
}

int main() {
	while (scanf("%d%d%d", &n, &a, &b) == 3) {
		m = n + 1;
		Matrix tr;
		for (int i = 1; i < n; ++i) {
			tr[i][i - 1] = 1;
		}
		for (int i = 0; i < a; ++i) {
			int u;
			scanf("%d", &u);
			--u;
			tr[u][n - 1] = 1;
		}
		for (int i = 0; i < b; ++i) {
			int u;
			scanf("%d", &u);
			--u;
			tr[n][u] = 1;
		}
		tr[n][n] = 1;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &source[i]);
		}
		source[n] = 1;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &target[i]);
		}
		target[n] = 1;
		Matrix inv = tr.inverse();	
		map<int, int> rem;
		int block = 1 << n / 2, step = 1 << (n + 1) / 2;
		for (int i = 0; i < block; ++i) {
			int h = target.hash();
			if (!rem.count(h)) {
				rem[h] = i;
			}
			target = target * inv;
		}
		Matrix trs;
		{
			for (int i = 0; i < m; ++i) {
				trs[i][i] = 1;
			}
			Matrix tmp = tr;
			int b = block;
			while (b) {
				if (b & 1) {
					trs = trs * tmp;
				}
				tmp = tmp * tmp;
				b >>= 1;
			}
		}
		int ans = -1, cur = 0;
		for (int i = 0; i < step; ++i) {
			int h = source.hash();
			if (rem.count(h)) {
				ans = cur + rem[h];
				break;
			}
			source = source * trs;
			cur += block;
		}
		if (ans == -1) {
			puts("poor sisyphus");
		} else {
			printf("%d\n", ans);
		}
	}
	return 0;
}
