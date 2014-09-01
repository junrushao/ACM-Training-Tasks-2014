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

const char table[17][17] = {
	{},
	{".TUVWXYZ."},
	{".MNOPQRS."},
	{".FGHIJKL."},
	{"..ABCDE.."}
};

const int dx[] = {0, 1,  0, -1,  1, 1, -1, -1};
const int dy[] = {1, 0, -1,  0, -1, 1, -1,  1};

inline int sign(int v) {
	if (v > 0) return 1;
	if (v < 0) return -1;
	return 0;
}

struct point {

	int x, y;

	point(): x(0), y(0) {
	}

	point(int x, int y): x(x), y(y) {
	}

	point operator - (const point &rhs) const {
		return point(x - rhs.x, y - rhs.y);
	}
};

inline int det(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}

inline int dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}

inline bool between(const point &a, const point &b, const point &p) {
	return det(p - a, b - a) == 0 && dot(p - a, p - b) <= 0;
}

inline int checkSegCross(const point &a, const point &b, const point &c, const point &d) {
	int s1, s2, s3, s4;
	int d1 = sign(s1 = det(b - a, c - a)), d2 = sign(s2 = det(b - a, d - a));
	int d3 = sign(s3 = det(d - c, a - c)), d4 = sign(s4 = det(d - c, b - c));
	if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) {
//		o = (c * s2 - d * s1) / (s2 - s1);
		return 1;
	}
	return 0;
}

#define x first
#define y second

pii chrPos[555];
string pathBetween[555][555];
int N, Len;
char P[1333];
int Next[1333][33];
string text;

void initText() {
	int N = strlen(P);
	text = string(".") + P[0];
	for (int i = 1; i < N; ++i) {
		int s = P[i - 1], t = P[i];
		text += pathBetween[s][t];
	}
//	cout << "text = " << text << endl;
	Len = (int)text.size() - 1;
//	Debug(Len);
	Rep(j, 0, 25) Next[Len][j] = -1;
	Til(i, Len - 1, 0) {
		Rep(j, 0, 25)
			Next[i][j] = Next[i + 1][j];
		Next[i][ text[i + 1] - 'A' ] = i + 1;
	}
//	Rep(i, 0, Len) Rep(j, 0, 2) printf("Next[%d][%c] = %d\n", i, (char)j + 'A', Next[i][j]);
}

void solve() {
	scanf("%d %s", &N, P);
	initText();

	bool done = false;
	Rep(str, 1, N) {
		scanf("%s", P + 1);
		if (done) continue;

		int lp = strlen(P + 1);
		int pos = 0;
		Rep(i, 1, lp) {
			pos = Next[pos][ P[i] - 'A' ];
//			Debug(pos);
			if (pos == -1) break;
		}
		if (pos != -1) {
			puts(P + 1);
			done = true;
		}
	}
	if (!done)
		puts("NO SOLUTION");
}

string calcPath(int from, int to) {
	static int G[55][55];

	point a = point(chrPos[from].x * 2, chrPos[from].y * 2);
	point b = point(chrPos[ to ].x * 2, chrPos[ to ].y * 2);

	memset(G, 0, sizeof(G));
	Rep(itr, 'A', 'Z') {
		int i = chrPos[itr].x, j = chrPos[itr].y;
		if (between(a, b, point(2 * i, 2 * j))
		 || checkSegCross(a, b, point(2 * i - 1, 2 * j - 1), point(2 * i - 1, 2 * j + 1))
		 || checkSegCross(a, b, point(2 * i - 1, 2 * j + 1), point(2 * i + 1, 2 * j + 1))
		 || checkSegCross(a, b, point(2 * i + 1, 2 * j + 1), point(2 * i + 1, 2 * j - 1))
		 || checkSegCross(a, b, point(2 * i + 1, 2 * j - 1), point(2 * i - 1, 2 * j - 1))) {
			G[i][j] = 1;
		}
	}

	static pii Q[5555];
	int head = 0, tail = 0;
	string res = "";
	G[chrPos[from].x][chrPos[from].y] = 2;
	for (Q[++tail] = pii(chrPos[from].x, chrPos[from].y); head < tail; ) {
		++head;
		int x = Q[head].x, y = Q[head].y;
		Rep(dir, 0, 7) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (G[nx][ny] != 1) continue;
			G[nx][ny] = 2;
			res += table[nx][ny];
			Q[++tail] = pii(nx, ny);
		}
	}
	return res;
}

void init() {
	Rep(i, 1, 4) Rep(j, 1, 8) if (table[i][j] != '.') {
		int v = table[i][j];
		chrPos[v] = pii(i, j);
	}
	
	Rep(S, 'A', 'Z') Rep(T, 'A', 'Z')
		pathBetween[S][T] = calcPath(S, T);
//	Rep(S, 'A', 'Z') Rep(T, 'A', 'Z') printf("%c -> %c: %s\n", (char)S, (char)T, pathBetween[S][T].c_str());
}

int main() {
	init();
	int T;
	scanf("%d", &T);
	while (T--) solve();
	return 0;
}

