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


int calc(double x, double y) {
	double r = x * x + y * y;
	if (r <= 9.0) return 100;
	if (r <= 36.0) return 80;
	if (r <= 81.0) return 60;
	if (r <= 144.0) return 40;
	if (r <= 225.0) return 20;
	return 0;
}

bool solve() {
	double x, y;
	scanf("%lf %lf", &x, &y);
	if (x == -100.0)
		return false;
	int a = 0, b = 0;
	a += calc(x, y);
	Rep(i, 2, 3) {
		scanf("%lf %lf", &x, &y);
		a += calc(x, y);
	}
	Rep(i, 1, 3) {
		scanf("%lf %lf", &x, &y);
		b += calc(x, y);
	}
	if (a == b)
		printf("SCORE: %d to %d, TIE.\n", a, b);
	else if (a > b)
		printf("SCORE: %d to %d, PLAYER 1 WINS.\n", a, b);
	else if (a < b)
		printf("SCORE: %d to %d, PLAYER 2 WINS.\n", a, b);
	return true;
}

int main() {
	while (solve());
	return 0;
}

