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

#define MAXN 100033
#pragma comment(linker, "/STACK:16777216")

struct enode {
	int to;
	enode *next;
} ebase[MAXN * 2 + 1], *etop, *fir[MAXN];
typedef enode *edge;

inline void addEdge(int a, int b) {
	etop->to = b;
	etop->next = fir[a];
	fir[a] = etop++;
}

int N;
LL ans;
LL f[MAXN];
LL size[MAXN];
int fa[MAXN];
edge E[MAXN];

void solveSubtree(int x) {
	int y;
	size[x] = 1;
	for (edge e(fir[x]); e; e = e->next)
		if ((y = e->to) != fa[x])
			size[x] += size[y];
	
	f[x] = size[x] - 1;
	for (edge e(fir[x]); e; e = e->next)
		if ((y = e->to) != fa[x])
			f[x] += f[y];

	ans += f[x] - (size[x] - 1);
	for (edge e(fir[x]); e; e = e->next)
		if ((y = e->to) != fa[x]) {
			ans += f[y] * (size[x] - 1 - size[y]);
		}

	LL tmp = 0;
	for (edge e(fir[x]); e; e = e->next)
		if ((y = e->to) != fa[x]) {
			tmp += LL(size[y]) * (size[x] - 1 - size[y]);
		}
	assert(tmp % 2 == 0);
	ans += tmp / 2;
//	printf("x = %d, size = %d, f = %lld\n", x, size[x], f[x]);
}

void DFS(int x) {
	for (E[x] = fir[x]; E[x]; E[x] = E[x]->next)
		if (E[x]->to != fa[x]) {
			fa[E[x]->to] = x;
			DFS(E[x]->to);
		}
	solveSubtree(x);
}

LL C3(LL N) {
	return N * (N - 1) * (N - 2) / 6;
}

void solve() {
	etop = ebase;
	Rep(i, 0, N) fir[i] = NULL;
	Rep(i, 2, N) {
		int a, b;
		scanf("%d %d", &a, &b);
		addEdge(a, b);
		addEdge(b, a);
	}
	
	ans = 0;
	fa[1] = -1;
	DFS(1);
	cout << C3(N) - ans << endl;
}

int main() {
	while (scanf("%d", &N) == 1) solve();
	return 0;
}

