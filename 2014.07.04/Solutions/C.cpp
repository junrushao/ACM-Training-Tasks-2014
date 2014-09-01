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

const int gxx = 1000000000;

const int N = 1005;

vector<pair<int, int> > e1[N], e2[N];
int f[N], g[N], n, m, C;
bool vis[N], ok[N];

void work()
{
	for (int i = 1; i <= n; ++i)
		f[i] = -1, vis[i] = false;
	f[1] = C;
	queue<int> Q;
	Q.push(1);
	while (!Q.empty())
	{
		int a = Q.front();
		vis[a] = false;
		Q.pop();
		for (int i = 0; i < (int)e1[a].size(); ++i)
		{
			int j = e1[a][i].first;
			int k = f[a] - e1[a][i].second;
			if (k < 0) continue;
			if (ok[j]) k = C;
			if (k > f[j])
			{
				f[j] = k;
				if (!vis[j])
				{
					vis[j] = true;
					Q.push(j);
				}
			}
		}
	}
}

void workwork()
{
	for (int i = 1; i <= n; ++i)
		g[i] = gxx, vis[i] = false;
	g[n] = 0;
	queue<int> Q;
	Q.push(n);
	while (!Q.empty())
	{
		int a = Q.front();
		vis[a] = false;
		Q.pop();
		for (int i = 0; i < (int)e2[a].size(); ++i)
		{
			int j = e2[a][i].first;
			int k = g[a] + e2[a][i].second;
			if (k > C) continue;
			if (ok[j]) k = 0;
			if (k < g[j])
			{
				g[j] = k;
				if (!vis[j])
				{
					vis[j] = true;
					Q.push(j);
				}
			}
		}
	}
}

int main() {
	while (scanf("%d%d%d", &n, &m, &C) == 3)
	{
		for (int i = 1; i <= n; ++i)
		{
			e1[i].clear();
			e2[i].clear();
			ok[i] = false;
		}
		for (int i = 0; i < m; ++i)
		{
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			e1[x].push_back(make_pair(y, z));
			e2[y].push_back(make_pair(x, z));
		}
		int p;
		scanf("%d", &p);
		while (p--)
		{
			int x;
			scanf("%d", &x);
			ok[x] = true;
		}
		work();
		workwork();
		int q, ans = 0;
		scanf("%d", &q);
		while (q--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			if (f[n] == -1) continue;
			if (f[x] > g[x])
				ans = max(ans, (f[x] - g[x]) * y);
		}
		if (f[n] == -1)
			puts("-1");
		else
			printf("%d\n", ans);
	}
	return 0;
}
