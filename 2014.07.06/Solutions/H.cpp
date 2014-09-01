/*
 * 1.cpp
 *
 *  Created on:
 *      Author:
 */

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

#define INF 1000000000
#define LL_INF 4000000000000000000ll
#define EPS (1e-9)

#define Lowbit(x) ((x) & (-(x)))
#define Lc(x) ((x) << 1)
#define Rc(x) (Lc(x) + 1)
#define Pow2(x) (1 << (x))
#define Contain(a, x) (((a) >> (x)) & 1)

#define Rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define Til(i, a, b) for(int i = (a); i >= (b); --i)
#define Foru(i, a, b) for(int i = (a); i < (b); ++i)
#define Ford(i, a, b) for(int i = (a); i > (b); --i)

#define It iterator
#define For(i, x) for(__typeof(x.begin()) i = x.begin(); i != x.end(); ++i)

#define Debug(x) (cerr << #x << " = " << (x) << endl)
#define Debug2(x, y) (cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl)

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int, int> pii;
typedef vector<int> VI;
typedef vector<string> VS;

//inline int rand(int a, int b) { return rand() % (b - a + 1) + a; }

template <class T> inline bool Up(T &a, const T &b) { if(a < b) {a = b; return true;} return false; }
template <class T> inline bool Down(T &a, const T &b) { if(a > b) {a = b; return true;} return false; }

inline int getus() { int tmp, c; while(tmp = fgetc(stdin), tmp < '0' || tmp > '9'); tmp -= '0'; while(c = fgetc(stdin), '0' <= c && c <= '9') tmp = tmp * 10 + c - '0'; return tmp; }
inline int getint() { int tmp, c, flag; while(flag = fgetc(stdin), flag != '-' && (flag < '0' || flag > '9')); if(flag == '-') tmp = 0; else tmp = flag - '0'; while(c = fgetc(stdin), '0' <= c && c <= '9') tmp = tmp * 10 + c - '0'; return flag == '-' ? -tmp : tmp; }

#define MAXN 2033
#define MAXM 2000033

struct enode {
	int to;
	LL c;
	enode *next, *op;
} ebase[MAXN * MAXN * 2], *etop, *fir[MAXN], *cur[MAXN], *pe[MAXN];
typedef enode *edge;

inline void addEdge(int a, int b, LL c) {
	edge e1 = etop++, e2 = etop++;
	e1->to = b; e1->c = c; e1->next = fir[a]; fir[a] = e1;
	e2->to = a; e2->c = c; e2->next = fir[b]; fir[b] = e2;
	e1->op = e2; e2->op = e1;
}

int S, T, Ncnt, h[MAXN], vh[MAXN];

LL maxFlow() {
	LL flow(0);
	int x, y;
	edge e;
	
	Rep(i, 0, Ncnt) h[i] = INF;
	Rep(i, 0, Ncnt) vh[i] = 0;
	Rep(i, 0, Ncnt) cur[i] = fir[i];

	{
		static int Q[MAXN];
		int head = 0, tail = 0;
		for (h[T] = 0, Q[++tail] = T; head < tail; ) {
			x = Q[++head]; ++vh[ h[x] ];
			for (e = fir[x]; e; e = e->next) if (e->op->c)
				if (h[y = e->to] >= INF) {
					h[y] = h[x] + 1;
					Q[++tail] = y;
				}
		}
	}
	for (x = S; h[S] < Ncnt; ) {
		for (e = cur[x]; e; e = e->next) if (e->c)
			if (h[y = e->to] + 1 == h[x]) {
				pe[y] = cur[x] = e;
				x = y;
				break;
			}
		if (!e) {
			if (!--vh[ h[x] ]) break;
			h[x] = Ncnt; cur[x] = NULL;
			for (e = fir[x]; e; e = e->next) if (e->c)
				if (Down(h[x], h[e->to] + 1))
					cur[x] = e;
			++vh[ h[x] ];
			if (x != S) x = pe[x]->op->to;
		}
		else if (x == T) {
			LL augc = LL_INF;
			for (x = T; x != S; x = pe[x]->op->to) Down(augc, pe[x]->c);
			for (x = T; x != S; x = pe[x]->op->to) {
				pe[x]->c -= augc;
				pe[x]->op->c += augc;
			}
			flow += augc;
		}
	}
	return flow;
}

int N;

void solve() {
	N = getus();
	static int B[MAXN][MAXN], C[MAXN], W[MAXN][MAXN], P[MAXN], D[MAXN];
	Rep(i, 1, N) Rep(j, 1, N) B[i][j] = getus();
	Rep(i, 1, N) C[i] = getus();

	Rep(i, 1, N) Rep(j, 1, N)
		if (i == j)
			W[i][j] = 0;
		else
			W[i][j] = B[i][j] + B[j][i];

	Rep(i, 1, N) {
		D[i] = 0;
		Rep(j, 1, N) if (i != j)
			D[i] += W[i][j];
	}

	Rep(i, 1, N) P[i] = B[i][i] - C[i];

	LL U = 0;
	Rep(i, 1, N) Up(U, 2LL * P[i] + D[i]);

	etop = ebase;
	S = 0; T = N + 1; Ncnt = N + 2;
	Rep(i, S, T) fir[i] = NULL;
	
	Rep(i, 1, N) addEdge(S, i, U);
	Rep(i, 1, N) addEdge(i, T, U - 2LL * P[i] - D[i]);
	Rep(i, 1, N) Rep(j, i + 1, N)
		addEdge(i, j, W[i][j]);
	cout << (U * N - maxFlow()) / 2 << endl;
}

int main() {
	int T;
	T = getus();
	while (T--) solve();
	return 0;
}