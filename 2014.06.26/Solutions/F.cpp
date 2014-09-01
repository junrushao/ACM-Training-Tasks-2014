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

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int P, Q;
int G[2033][2033], T = 0, xT = 0, yT = 0;
int dist[2033][2033];
int xLowerBound, yLowerBound;
int xUpperBound, yUpperBound;
pii Queue[2033 * 2033];

inline bool inRange(int x, int y) {
	return xLowerBound <= x && x <= xUpperBound && yLowerBound <= y && y <= yUpperBound;
}

#define x first
#define y second

void solve() {
	xLowerBound = yLowerBound = 2000;
	xUpperBound = yUpperBound = 0;
	
	xT = ++T;
	yT = ++T;
	{
		int x, y;
		Rep(i, 1, P) {
			scanf("%d %d", &x, &y);
			G[x][y] = xT;
			Down(xLowerBound, x);
			Down(yLowerBound, y);
			Up(xUpperBound, x);
			Up(yUpperBound, y);
		}
		scanf("%d", &Q);
		Rep(i, 1, Q) {
			scanf("%d %d", &x, &y);
			G[x][y] = yT;
			Down(xLowerBound, x);
			Down(yLowerBound, y);
			Up(xUpperBound, x);
			Up(yUpperBound, y);
		}
	}

	int head = 0, tail = 0;
	Rep(x, xLowerBound, xUpperBound)
		Rep(y, yLowerBound, yUpperBound)
			if (G[x][y] == xT) {
				Queue[++tail] = pii(x, y);
				dist[x][y] = 0;
			}
			else dist[x][y] = INF;

	while (head < tail) {
		++head;
		int x = Queue[head].x, y = Queue[head].y;
		int d = dist[x][y];

		Rep(dir, 0, 3) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (!inRange(nx, ny)) continue;
			if (dist[nx][ny] < INF) continue;
			if (G[nx][ny] == yT) {
				printf("%d\n", d + 1);
				return;
			}
			dist[nx][ny] = d + 1;
			Queue[++tail] = pii(nx, ny);
		}
	}
}

void init() {
	memset(G, 0, sizeof(G));
}

int main() {
	init();
	while (scanf("%d", &P), P != 0) solve();
	return 0;
}

