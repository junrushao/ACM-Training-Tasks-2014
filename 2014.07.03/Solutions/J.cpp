#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int f[410][410];
vector<int> son[410], node[2][410];
int TT;
int n1, n2;
int dep[410];
int maxDep;
int size[410];

const int oo = 1 << 30;
int value[501][501], n, L[501], R[501], v[501];
bool bx[501], by[501];

void get_dep(int root) {
	int que[210], l, r;
	int tg = root / 201;
	dep[root] = 0, node[tg][0].push_back(root);
	l = r = 0;
	que[r++] = root;
	while (l != r) {
		int u = que[l++];
		for (int i = 0; i < son[u].size(); ++i) {
			int v = son[u][i];
			dep[v] = dep[u] + 1;
			node[tg][dep[v]].push_back(v);
			que[r++] = v;
		}
	}
	for (int i = r - 1; i >= 0; --i) {
		int t = que[i];
		size[t] = 1;
		for (int j = 0; j < son[t].size(); ++j) size[t] += size[son[t][j]];
	}
}

void set_tree() {
	int fa;
	scanf("%d", &n1);
	for (int i = 1; i <= n1; ++i) {
		scanf("%d", &fa);
		son[fa].push_back(i);
	}
	scanf("%d", &n2);
	for (int i = 1; i <= n2; ++i) {
		scanf("%d", &fa);
		son[fa+201].push_back(i+201);
	}
}

bool find(int now) {
	bx[now] = true;
	for (int i = 1; i <= n; ++i) {
		if (!by[i] && L[now] + R[i] == value[now][i]) {
			by[i] = true;
			if (!v[i] || find(v[i])) {
				v[i] = now;
				return true;
			}
		}
	}
	return false;
}

int KM(int p, int q) {
	n = max(son[p].size(), son[q].size());
	for (int i = 0; i < son[p].size(); ++i) {
		for (int j = 0; j < son[q].size(); ++j) {
			value[i+1][j+1] = -f[son[p][i]][son[q][j]];
		}
	}
	for (int i = son[p].size() + 1; i <= n; ++i) {
		for (int j = 0; j < son[q].size(); ++j) {
			value[i][j + 1] = -size[son[q][j]];
		}
	}
	for (int i = son[q].size() + 1; i <= n; ++i) {
		for (int j = 0; j < son[p].size(); ++j) {
			value[j + 1][i] = -size[son[p][j]];
		}
	}
	for (int i = 1; i <= n; ++i) L[i] = R[i] = v[i] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			L[i] = max(L[i], value[i][j]);
		}
	}
	/*cout << p << ' ' << q << endl;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << i << ' ' << j << ' ' << value[i][j] << endl;
		}
	}*/
	int ret = 0;
	for (int i = 1; i <= n; ++i) {
		for (;;) {
			for (int j = 1; j <= n; ++j) bx[j] = by[j] = 0;
			if (find(i)) break;
			int Min = oo;
			for (int j = 1; j <= n; ++j) {
				if (bx[j]) {
					for (int k = 1; k <= n; ++k) {
						if (!by[k]) Min = min(Min, L[j] + R[k] - value[j][k]);
					}
				}
			}
			for (int j = 1; j <= n; ++j) {
				if (bx[j]) L[j] -= Min;
				if (by[j]) R[j] += Min;
			}
		}
	}
	for (int i = 1; i <= n; ++i) ret += value[v[i]][i];
	//cout << ret << endl;
	return -ret;
}

int main() {
	//freopen("j.in", "r", stdin);
	cin >> TT;
	memset(f, 0, sizeof(0));
	for (int T = 1; T <= TT; ++T) {
		set_tree();
		get_dep(0), get_dep(201);
		//for (int i = 0; i <= n1; ++i) printf("%d %d\n", i, size[i]);
		maxDep = 0;	//cout << 1 << endl;
		for (int i = 0; i <= n1; ++i) maxDep = max(maxDep, dep[i]);	//cout << 1 << endl;
		for (int i = 201; i <= 201 + n2; ++i) maxDep = max(maxDep, dep[i]);//	cout << 1 << endl;
		for (int i = maxDep; i >= 0; --i) {
			for (int j = 0; j < node[0][i].size(); ++j) {
				int u = node[0][i][j];
				for (int k = 0; k < node[1][i].size(); ++k) {
					int v = node[1][i][k];
					//cout << u << ' ' << v << ' ' << f[u][v] << endl;
					f[u][v] = KM(u, v);
					//cout << u << ' ' << v << ' ' << f[u][v] << endl;
				}
			}
		}	//cout << 1 << endl;
//		for (int i = 0; i <= n1; ++i) {
//			for (int j = 201; j <= 201 + n2; ++j) printf("%d %d %d\n", i, j, f[i][j]);
//		}	cout << 1 << endl;
		printf("Case %d: %d\n", T, f[0][201]);
		for (int i = 0; i <= n1; ++i) son[i].clear();
		for (int i = 201; i <= 201 + n2; ++i) son[i].clear();
		for (int i = 0; i <= maxDep; ++i) node[0][i].clear(), node[1][i].clear();
//		for (int i = 0; i <= n1; ++i) {
//			for (int j = 201; j <= 201 + n2; ++j) f[i][j] = 0;
//		}
	}
}
