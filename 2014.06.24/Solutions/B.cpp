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

int R, C;
LL pow26[1033];

void solve(int k, int bit) {
	if (bit == 0) {
		assert(k == 1);
		return;
	}
	Rep(i, 0, 25) {
		LL l = i * pow26[bit - 1];
		LL r = (i + 1) * pow26[bit - 1];
		if (l < k && k <= r) {
			putchar('A' + i);
			solve(k - l, bit - 1);
			break;
		}
	}
}

bool solve() {
	R = getint();
	C = getint();
//	cout << R << ' ' << C << endl;
	if (R == 0 && C == 0) return false;
	
	LL total = 0, last = 1;
	int bit = 0;
	while (total < C) {
		last *= 26;
		total += last;
		++bit;
	}
//	printf("bit = %d\n", bit);
	C -= total - last;
	solve(C, bit);
	printf("%d\n", R);
	return true;
}

void init() {
	pow26[0] = 1;
	Rep(i, 1, 1022) pow26[i] = pow26[i - 1] * 26;
}

int main() {
	init();
	while (solve());
	return 0;
}


