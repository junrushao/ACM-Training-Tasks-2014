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

const int N = 1005;

int x[N], y[N], z[N];

int sgn(int x)
{
	if (x == 0) return 0;
	return 1;
}

int main() {
	int n, m, k;
	while (scanf("%d%d%d", &n, &m, &k) == 3)
	{
		long long ans = -1;
		for (int i = 0; i < m; ++i)
		{
			scanf("%d%d%d", &x[i], &y[i], &z[i]);
			--x[i];
			--y[i];
		}
		for (int s = 0; s < (1 << n); ++s)
		{
			if (sgn(s & (1 << 0)) == sgn(s & (1 << (n - 1)))) continue;
			vector<int> a;
			for (int i = 0; i < m; ++i)
				if (sgn(s & (1 << x[i])) != sgn(s & (1 << y[i])))
					a.push_back(z[i]);
			sort(a.begin(), a.end());
			reverse(a.begin(), a.end());
			long long tmp = 0;
			for (int i = k; i < (int)a.size(); ++i)
				tmp += a[i];
			if (ans == -1 || tmp < ans)
				ans = tmp;
		}
		if (n == 1)
			ans = 0;
		cout << ans << endl;
	}
	return 0;
}

