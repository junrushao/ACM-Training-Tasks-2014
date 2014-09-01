#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n;

long long l;

vector<int> prime;

struct Trie {
	char ch;
	int son, next, father, suffix;
	vector<int> danger;
};

const int LEN = 45;

Trie a[LEN];

int now, m;

void clear(int x) {
	a[x].son = a[x].next = 0;
	a[x].danger.clear();
}

void insert(char *s, int l, int t, int x) {
	if (!a[x].son) {
		a[x].son = ++m;
		clear(m);
		a[m].father = x;
		a[m].ch = s[t];
		if (t + 1 == l) {
			a[m].danger.push_back(now);
		} else {
			insert(s, l, t + 1, m);
		}
		return;
	}
	int i = a[x].son;
	while (1) {
		if (!a[i].next || a[i].ch == s[t]) {
			break;
		}
		i = a[i].next;
	}
	if (a[i].ch == s[t] && t + 1 == l) {
		a[i].danger.push_back(now);
	} else if (a[i].ch == s[t]) {
		insert(s, l, t + 1, i);
	} else {
		a[i].next = ++m;
		clear(m);
		a[m].father = x;
		a[m].ch = s[t];
		if (t + 1 == l) {
			a[m].danger.push_back(now);
		} else {
			insert(s, l, t + 1, m);
		}
	}
}

int q[100000];

int child(int x, char ch) {
	for (int i = a[x].son; i; i = a[i].next) {
		if (a[i].ch == ch) {
			return i;
		}
	}
	if (x == 1) {
		return 1;
	}
	return child(a[x].suffix, ch);
}

void build_trie() {
	int l, r;
	l = r = 1;
	q[1] = 1;
	while (l <= r) {
		int x = q[l++];
		for (int i = a[x].son; i; i = a[i].next) {
			q[++r] = i;
		}
	}
	a[1].suffix = 1;
	for (int i = 2; i <= r; ++i) {
		int x = q[i];
		if (a[x].father == 1) {
			a[x].suffix = 1;
			continue;
		}
		a[x].suffix = child(a[a[x].father].suffix, a[x].ch);
		for (int j = 0; j < a[a[x].suffix].danger.size(); ++j) {
			a[x].danger.push_back(a[a[x].suffix].danger[j]);
		}
	}
}

int MOD;

struct Matrix {
	int a[LEN][LEN];

	Matrix(int type = 0) {
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < m; ++j) {
				a[i][j] = 0;
			}
		}
		if (type == 1) {
			for (int i = 0; i < m; ++i) {
				a[i][i] = 1;
			}
		}
	}

	void clear() {
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < m; ++j) {
				a[i][j] = 0;
			}
		}
	}

	const int* operator[] (int i) const {
		return a[i];
	}
	
	int* operator[] (int i) {
		return a[i];
	}
};

int ll[LEN];
Matrix ma[200];

Matrix operator * (Matrix &a, Matrix &b) {
	Matrix ret;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			int &tmp = ret[i][j], *aa = a[i];
			for (int k = 0; k < m; ++k) {
				(tmp += aa[k] * b[k][j]);
			}
			tmp %= MOD;
		}
	}
	return ret;
}

int solve(int mod, long long l) {
	MOD = mod;
	for (int i = 0; i < mod; ++i) {
		ma[i].clear();
		for (int k = 1; k <= m; ++k) {
			for (char ch = 'A'; ch <= 'Z'; ++ch) {
				int u = k, v = child(u, ch);
				vector<int> w = a[v].danger;
				--u, --v;
				int add = 1;
				for (int j = 0; j < (int)w.size(); ++j) {
					(add *= prime[w[j]] * (ll[w[j]] + i) % MOD) %= MOD;
				}
				ma[i][u][v] += add;
			}
		}
	}
	Matrix g(1), f(1);
	for (int i = 1; i <= mod; ++i) {
		g = g * ma[i % mod];
	}
	long long lp = l / mod, lq = l % mod;
	while (lp) {
		if (lp & 1) {
			f = f * g;
		}
		g = g * g;
		lp >>= 1;
	}
	for (int i = 1; i <= lq; ++i) {
		f = f * ma[i];
	}
	int ret = 0;	
	for (int i = 0; i < m; ++i) {
		(ret += f[0][i]) %= MOD;
	}
	return ret;
}

void init() {
	for (int i = 2; prime.size() < 40; ++i) {
		bool isprime = true;
		for (int j = 0; j < (int)prime.size(); ++j) {
			if (i % prime[j] == 0) {
				isprime = false;
			}
		}
		if (isprime) {
			prime.push_back(i);
		}
	}
}

const int P[3] = {179, 173, 163}; 
int Q[3];

void prepare() {
	for (int i = 0; i < 3; ++i) {
		int k = P[0] * P[1] * P[2] / P[i];
		for (int j = 0; j < P[i]; ++j) {
			if (k * j % P[i] == 1) {
				Q[i] = j;
				break;
			}
		}
	}
}

int crt(int a, int b, int c) {
	MOD = P[0] * P[1] * P[2];
	return ((long long)a * Q[0] % MOD * (MOD / P[0]) % MOD + (long long)b * Q[1] % MOD * (MOD / P[1]) % MOD + (long long)c * Q[2] % MOD * (MOD / P[2]) % MOD) % MOD;
}

char buf[LEN];

int main() {
	init();
	prepare();
	while (scanf("%d%I64d", &n, &l) == 2) {
		clear(m = 1);
		for (int i = 0; i < n; ++i) {
			scanf("%s", buf);
			now = i;
			ll[i] = strlen(buf);
			insert(buf, strlen(buf), 0, 1);
		}
		build_trie();
		static int id = 0;
		printf("Case #%d: %d\n", ++id, crt(solve(P[0], l), solve(P[1], l), solve(P[2], l)));
	}
	return 0;
}
