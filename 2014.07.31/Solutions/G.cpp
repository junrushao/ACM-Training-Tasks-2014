
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <climits>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <utility>
#include <numeric>
#include <functional>
#include <algorithm>

#define Rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define Foru(i, a, b) for(int i = (a); i < (b); ++i)

using namespace std;

const int MAXN = 513;

int W[MAXN], Q[MAXN];
char G[MAXN][MAXN];

inline int* QToIntArray(int n, int *label) {
	int *res = new int[n];
	for (int i = 0; i < n; ++i)
		res[i] = label[ Q[i + 1] ];
	return res;
}

inline int BFS(int n, int *label, int S, bool *vis, char go) {
	int head = 0, tail = 0;
	assert(!vis[S]);

	for (Q[++tail] = S, vis[S] = true; head < tail; ) {
		int x = Q[++head];
		Foru(y, 0, n) if (!vis[y] && G[ label[x] ][ label[y] ] == go) {
			vis[y] = true;
			Q[++tail] = y;
		}
	}
	return tail;
}

inline int Calc(int n, int *label) {
	if (n == 1) {
		return W[ label[0] ];
	}
	bool *vis = new bool[n];
	Foru(i, 0, n) vis[i] = false;
	int res = 0;
	int n1 = BFS(n, label, 0, vis, '1');
	if (n1 != n) {
		res = Calc(n1, QToIntArray(n1, label));
		Foru(S, 1, n) if (!vis[S]) {
			n1 = BFS(n, label, S, vis, '1');
			res = max(res, Calc(n1, QToIntArray(n1, label)));
		}
	}
	else if (n1 == n) {
		Foru(i, 0, n) vis[i] = false;
		Foru(S, 0, n) if (!vis[S]) {
			n1 = BFS(n, label, S, vis, '0');
			res += Calc(n1, QToIntArray(n1, label));
		}
	}
	return res;
}

void solve() {
	int N;
	scanf("%d", &N);
	Foru(i, 0, N) scanf("%s", G[i]);
	Foru(i, 0, N) scanf("%d", W + i);

	int *label = new int[N];
	Foru(i, 0, N) label[i] = i;
	int ans = Calc(N, label);
	printf("%d\n", ans);
}

int main() {
	solve();
	return 0;
}

