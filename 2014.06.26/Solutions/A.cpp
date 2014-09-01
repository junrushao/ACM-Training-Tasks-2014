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

#define MAXN 129

struct Point {
	double x, y;
} P[MAXN], Q[MAXN];

inline double dist(const Point &a, const Point &b) {
	return hypot(a.x - b.x, a.y - b.y);
}

int N, M, S, V;
int G[MAXN][MAXN];
int LinkY[MAXN], LinkX[MAXN];
int used[MAXN];

int DFS(int x) {
	if (used[x]) return 0;
	used[x] = 1;
	Rep(y, 1, M) if (G[x][y])
		if (LinkY[y] == 0 || DFS(LinkY[y])) {
			LinkY[y] = x;
			LinkX[x] = y;
			return 1;
		}
	return 0;
}

void solve() {
	Rep(i, 1, N) scanf("%lf %lf", &P[i].x, &P[i].y);
	Rep(i, 1, M) scanf("%lf %lf", &Q[i].x, &Q[i].y);

	Rep(i, 1, N) Rep(j, 1, M)
		if (dist(P[i], Q[j]) <= (LL)V * S)
			G[i][j] = 1;
		else
			G[i][j] = 0;

	int ans = 0;
	Rep(i, 1, N) LinkX[i] = 0;
	Rep(i, 1, M) LinkY[i] = 0;
	Rep(x, 1, N) if (!LinkX[x]) {
		Rep(i, 1, N) used[i] = 0;
		if (DFS(x)) ++ans;
	}
	printf("%d\n", N - ans);
}

int main() {
	while (scanf("%d %d %d %d", &N, &M, &S, &V) == 4) solve();
	return 0;
}

