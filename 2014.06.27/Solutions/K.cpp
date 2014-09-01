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

int N, M, L, P[129], G[129][129], dist[129];
int cost[129], value[129];
bitset<1024> dp[1025];
set<int> valid;
bitset<1024> res;

void solve() {
	{
		scanf("%d %d %d", &N, &M, &L);
		Rep(i, 1, N) scanf("%d", P + i);
		sort(P + 1, P + N + 1);
		Rep(i, 1, M) scanf("%d %d", cost + i, value + i);
	}

	{
		Rep(i, 0, L) dp[i].reset();
		dp[0].set(0, true);
		Rep(i, 1, M) {
			Til(j, L - cost[i], 0) {
				dp[j + cost[i]] |= dp[j] << value[i];
			}
		}
	}

	{
		res.reset();
		Rep(i, 0, L)
			res |= dp[i];
		Rep(i, 1, N) Rep(j, 1, N)
			G[i][j] = res[ abs(P[i] - P[j]) ];
//		printf("dist =");
//		Rep(i, 0, 1000)
//			if (res[i])
//				printf(" %d", i);
//		puts("");
	}

	{
		static int Q[129];
		int head = 0, tail = 0;
		Rep(i, 1, N) dist[i] = INF;
		for (dist[1] = 0, Q[++tail] = 1; head < tail; ) {
				int x = Q[++head];
			Rep(y, 1, N) if (G[x][y])
				if (dist[y] >= INF) {
					dist[y] = dist[x] + 1;
					Q[++tail] = y;
				}
		}
		if (dist[N] >= INF)
			puts("-1");
		else
			printf("%d\n", dist[N]);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) solve();
	return 0;
}

