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

const int N = 600005;

int f[N], g[N], number[N], s[N];

int find(int i)
{
	if (f[i] != i)
	{
		int j = f[i];
		f[i] = find(f[i]);
		g[i] = (g[i] + g[j]) % 2;
	}
	return f[i];
}

int main() {
	int n, m;
	while (scanf("%d%d", &n, &m) == 2)
	{
		for (int i = 0; i < n; ++i)
		{
			number[i] = i;
			f[i] = i;
			g[i] = 0;
			s[i] = 1;
		}
		int ed = n;
		while (m--)
		{
			char c;
			int u, v;
			scanf(" %c", &c);
			if (c == 'L')
			{
				scanf("%d%d", &u, &v);
				u = number[u];
				v = number[v];
				find(u);
				find(v);
				if (find(u) == find(v)) continue;
				int val = (1 - g[u] - g[v] + 100) % 2;
				u = find(u);
				v = find(v);
				f[u] = v;
				g[u] = val;
				s[v] += s[u];
			}
			else if (c == 'D')
			{
				scanf("%d", &u);
				int v = find(number[u]);
				--s[v];
				number[u] = ed;
				f[ed] = ed;
				g[ed] = 0;
				s[ed] = 1;
				++ed;
			}
			else if (c == 'Q')
			{
				scanf("%d%d", &u, &v);
				u = number[u];
				v = number[v];
				find(u);
				find(v);
				if (find(u) != find(v))
					puts("Unknown");
				else if ((g[u] + g[v]) % 2 == 0)	
					puts("Same");
				else
					puts("Different");
			}
			else
			{
				scanf("%d", &u);
				u = number[u];
				u = find(u);
				printf("%d\n", s[u]);
			}
		}
	}
	return 0;
}
