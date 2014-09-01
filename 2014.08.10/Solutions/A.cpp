#include <cassert>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m;

const int N = 105;
int map[N][N], a[N][N];

string ept;
vector<string> ans;

string itos(int n) {
	string ret;
	while (n) {
		ret = ret + (char)(n % 10 + '0');
		n /= 10;
	}
	reverse(ret.begin(), ret.end());
	return ret;
}

struct Quad {
	int a[4];

	vector<string> ret;

	Quad(int a0 = 0, int a1 = 0, int a2 = 0, int a3 = 0) {
		a[0] = a0, a[1] = a1, a[2] = a2, a[3] = a3;
	}

	void R0(int r0) {
		ret.push_back(ept + "R" + itos(r0 + 1));
		swap(a[0], a[1]);
	}

	void R1(int r1) {
		ret.push_back(ept + "R" + itos(r1 + 1));
		swap(a[2], a[3]);
	}

	void C0(int c0) {
		ret.push_back(ept + "C" + itos(c0 + 1));
		swap(a[0], a[2]);
	}

	void C1(int c1) {
		ret.push_back(ept + "C" + itos(c1 + 1));
		swap(a[1], a[3]);
	}

	vector<string> minimize(int r0 = 0, int c0 = 0, int r1 = 0, int c1 = 0) {
		ret.clear();
		int b[4] = {a[0], a[1], a[2], a[3]};
		sort(b, b + 4);
		//step 1
		if (b[0] == a[0]) {
		} else if (b[0] == a[1]) {
			C1(c1), R0(r0), C1(c1), R0(r0);
		} else if (b[0] == a[2]) {
			C0(c0), R0(r0), C0(c0), R0(r0);
		} else if (b[0] == a[3]) {
			R0(r0), C1(c1), R0(r0), C1(c1);
		}
		//step 2
		if (b[1] == a[1]) {
		} else if (b[1] == a[2]) {
			C1(c1), R1(r1), C1(c1), R1(r1);
		} else if (b[1] == a[3]) {
			R1(r1), C1(c1), R1(r1), C1(c1);
		}
		return ret;
	}

	void myassert() {
		for (int i = 0; i + 1 < 4; ++i) {
			assert(a[i] < a[i + 1]);
		}
	}
};

int top;

int ma[N * N][N << 1];

void newEqu(int r, int c, int res) {
	for (int i = 0; i < n + m + 1; ++i) {
		ma[top][i] = 0;
	}
	ma[top][n + m] = res;	
	ma[top][r] = 1;
	ma[top][n - 1 - r] = 1;
	ma[top][c + n] = 1;
	ma[top][m - 1 - c + n] = 1;
	++top;
}

bool x[N << 1];

bool gauss(int n, int m) {
	for (int i = 0, pivot = 0; pivot < m; ++i, ++pivot) {
		if (i >= n) {
			for (int j = 0; j < n; ++j) {
				ma[j][pivot] = 0;
			}
			continue;
		}
		do {	
			if (ma[i][pivot] == 0) {
				for (int j = i + 1; j < n; ++j) {
					if (ma[j][pivot]) {
						for (int k = pivot; k <= m; ++k) {
							swap(ma[i][k], ma[j][k]);
						}
						break;
					}
				}
			}
			if (ma[i][pivot] == 0) {
				for (int j = 0; j < n; ++j) {
					ma[j][pivot] = 0;
				}
				++pivot;
			} else {
				break;
			}
		} while (pivot < m);
		if (pivot == m) {
			break;
		}
		for (int j = 0; j < n; ++j) {
			if (i == j) {
				continue;
			}
			if (ma[j][pivot]) {
				for (int k = pivot; k <= m; ++k) {
					ma[j][k] ^= ma[i][k];
				}
			}
		}
	}
	for (int i = 0; i < m; ++i) {
		x[i] = 0;
	}
	for (int i = 0; i < n; ++i) {
		int find = -1;
		for (int j = 0; j < m; ++j) {
			if (ma[i][j]) {
				if (find == -1) {
					find = j;
				} else {
					assert(false);
				}
			}
		}
		if (find == -1) {
			if (ma[i][m] == 1) {
				return false;
			} else {
				continue;
			}
		} else {
			x[find] = ma[i][m];
		}
	}
	return true;
}

void debug(vector<string>);

bool solve() {
	if (n & 1) {
		int mid = n >> 1;
		bool rev = false;
		for (int i = 0; i < m; ++i) {
			if (map[mid][i] != a[mid][i]) {
				rev = true;
			}
		}
		if (rev) {
			ans.push_back(ept + "R" + itos(mid + 1));
			for (int i = 0; i < m - 1 - i; ++i) {
				swap(map[mid][i], map[mid][m - 1 - i]);
			}
		}
		for (int i = 0; i < m; ++i) {
			if (map[mid][i] != a[mid][i]) {
				return false;
			}
		}
	}

	if (m & 1) {
		int mid = m >> 1;
		bool rev = false;
		for (int i = 0; i < n; ++i) {
			if (map[i][mid] != a[i][mid]) {
				rev = true;
			}
		}
		if (rev) {
			ans.push_back(ept + "C" + itos(mid + 1));
			for (int i = 0; i < n - 1 - i; ++i) {
				swap(map[i][mid], map[n - 1 - i][mid]);
			}
		}
		for (int i = 0; i < n; ++i) {
			if (map[i][mid] != a[i][mid]) {
				return false;
			}
		}
	}
	
	top = 0;
	for (int i = 0; i < n - 1 - i; ++i) {
		for (int j = 0; j < m - 1 - j; ++j) {
			int tmp[4] = {map[i][j], map[i][m - 1 - j], map[n - 1 - i][j], map[n - 1 - i][m - 1 - j]},
				ori[4] = {a[i][j], a[i][m - 1 - j], a[n - 1 - i][j], a[n - 1 - i][m - 1 - j]};
			sort(tmp, tmp + 4);
			sort(ori, ori + 4);
			for (int k = 0; k < 4; ++k) {
				if (tmp[k] != ori[k]) {
					return false;
				}
			}
			Quad cur(map[i][j], map[i][m - 1 - j], map[n - 1 - i][j], map[n - 1 - i][m - 1 - j]);
			cur.minimize();	
			newEqu(i, j, cur.a[2] > cur.a[3]);
		}
	}
	if (!gauss(top, n + m)) {
		return false;
	}
	for (int i = 0; i < n; ++i) {
		if (x[i]) {
			ans.push_back(ept + "R" + itos(i + 1));
			for (int j = 0; j < m - 1 - j; ++j) {
				swap(map[i][j], map[i][m - 1 - j]);
			}
		}
	}
	for (int i = 0; i < m; ++i) {
		if (x[i + n]) {
			ans.push_back(ept + "C" + itos(i + 1));
			for (int j = 0; j < n - 1 - j; ++j) {
				swap(map[j][i], map[n - 1 - j][i]);
			}
		}
	}
	for (int i = 0; i < n - 1 - i; ++i) {
		for (int j = 0; j < m - 1 - j; ++j) {
			Quad cur(map[i][j], map[i][m - 1 - j], map[n - 1 - i][j], map[n - 1 - i][m - 1 - j]);
			vector<string> tmp = cur.minimize(i, j, n - i - 1, m - j - 1);
			ans.insert(ans.end(), tmp.begin(), tmp.end());
			cur.myassert();
		}
	}
	return true;
}

int bak[N][N], tmp[N][N];

void debug(vector<string> ans) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			tmp[i][j] = bak[i][j];
		}
	}
	for (int i = 0; i < (int)ans.size(); ++i) {
		string cur = ans[i];
		if (cur[0] == 'R') {
			int i;
			sscanf(cur.c_str(), "%*c%d", &i);
			--i;
			for (int j = 0; j < m - 1 - j; ++j) {
				swap(tmp[i][j], tmp[i][m - 1 - j]);
			}
		} else {
			int j;
			sscanf(cur.c_str(), "%*c%d", &j);
			--j;
			for (int i = 0; i < n - 1 - i; ++i) {
				swap(tmp[i][j], tmp[n - 1 - i][j]);
			}
		}
	}
}

bool check(vector<string> ans) {
	if (ans.size() > 10 * n * m) {
		return false;
	}
	debug(ans);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (tmp[i][j] != a[i][j]) {
				while (true) {
					int x = 1;
					x = x * x + 1;
					continue;
				}
			}
		}
	}
	return true;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &m, &n);
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				scanf("%d", &map[i][j]);
				a[i][j] = ++cnt;
				bak[i][j] = map[i][j];
			}
		}
		ans.clear();
		if (solve()) {
			printf("POSSIBLE %d", (int)ans.size());
			for (int i = 0; i < (int)ans.size(); ++i) {
				printf(" %s", ans[i].c_str());
			}
			printf("\n");
			assert(check(ans));
		} else {
			puts("IMPOSSIBLE");
		}
	}
	return 0;
}
