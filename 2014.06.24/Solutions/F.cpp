/*
 * 1.cpp
 *
 *  Created on: 2014.6.23
 *      Author: JunruShao
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

int R, C[1033];
unsigned dp[33][33][33][33][33];

bool solve() {
	scanf("%d", &R);
	if (R == 0) return false;
	Rep(i, 1, R) scanf("%d", C + i);
	Rep(i, R + 1, 5) C[i] = 0;
	R = 5;
	
	Rep(r1, 0, C[1])
	Rep(r2, 0, C[2])
	Rep(r3, 0, C[3])
	Rep(r4, 0, C[4])
	Rep(r5, 0, C[5])
		dp[r1][r2][r3][r4][r5] = 0;
	dp[0][0][0][0][0] = 1;
	
	Rep(r1, 0, C[1])
	Rep(r2, 0, min(r1, C[2]))
	Rep(r3, 0, min(r3, C[3]))
	Rep(r4, 0, min(r4, C[4]))
	Rep(r5, 0, min(r5, C[5])) {
		unsigned v = dp[r1][r2][r3][r4][r5];
		if (v == 0) continue;
		if (r1 + 1 <= C[1])
			dp[r1 + 1][r2][r3][r4][r5] += v;
		if (r2 + 1 <= C[2] && r2 + 1 <= r1)
			dp[r1][r2 + 1][r3][r4][r5] += v;
		if (r3 + 1 <= C[3] && r3 + 1 <= r2)
			dp[r1][r2][r3 + 1][r4][r5] += v;
		if (r4 + 1 <= C[4] && r4 + 1 <= r3)
			dp[r1][r2][r3][r4 + 1][r5] += v;
		if (r5 + 1 <= C[5] && r5 + 1 <= r4)
			dp[r1][r2][r3][r4][r5 + 1] += v;
	}
	cout << dp[C[1]][C[2]][C[3]][C[4]][C[5]] << endl;
	return true;
}

int main() {
	while ( solve() );
	return 0;
}
