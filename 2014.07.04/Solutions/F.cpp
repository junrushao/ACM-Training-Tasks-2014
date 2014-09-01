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

const int N = 100005;

int now[N], next[N], ne[N], point[N], pos[N];
long long key[N];
bool flag;
int d[N], vd[N], ed, s, t, n, m, T;

void linklink(int a, int b, long long c)
{
	++ed; next[now[a]] = ed; now[a] = ed; point[ed] = b; key[ed] = c; pos[ed] = ed + 1; next[ed] = 0;
	++ed; next[now[b]] = ed; now[b] = ed; point[ed] = a; key[ed] = c; pos[ed] = ed - 1; next[ed] = 0;
}

long long dfs(int a, long long flow)
{
	if (a == t) return flow;
	long long ret = 0;
	for (int i = ne[a]; i; i = next[i], ne[a] = i)
	{
		int j = point[i];
		long long k = key[i];
		if (d[a] != d[j] + 1) continue;
		long long tmp = dfs(j, min(flow, k));
		key[i] -= tmp;
		key[pos[i]] += tmp;
		flow -= tmp;
		ret += tmp;
		if (flow == 0) return ret;
	}
	--vd[d[a]];
	if (vd[d[a]] == 0) flag = true;
	++d[a];
	++vd[d[a]];
	return ret;
}

int main() {
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d%d%d", &n, &m, &s, &t);
		ed = n;
		for (int i = 1; i <= n; ++i)
			now[i] = i, next[i] = 0, d[i] = 0, vd[i] = 0;
		vd[0] = n;
		long long sum = 0;
		while (m--)
		{
			int a, b, cc;
			scanf("%d%d%d", &a, &b, &cc);
			sum += cc;
			long long c = cc * 1001 + 1;
			linklink(a, b, c);
		}
		long long ans = 0;
		flag = false;
		while (d[s] < n)
		{
			for (int i = 1; i <= n; ++i)
				ne[i] = next[i];
			ans += dfs(s, 1LL << 60);
			if (flag) break;
		}
		long long p = sum - ans / 1001;
		long long q = ans % 1001;
		if (ans == 0)
			puts("Inf");
		else
			printf("%.2f\n", 1. * p / q);
	}
	return 0;
}
