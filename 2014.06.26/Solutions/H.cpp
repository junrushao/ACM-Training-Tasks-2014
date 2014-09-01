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

#define MAXN 129
#define MAXLEN 1025

#define numP 1021LL
#define hashMod 1000000007LL

LL PowP[MAXLEN];

struct HashString {

	int h[MAXLEN];

	void set(char *s, int n) {
		h[0] = 0;
		Rep(i, 1, n)
			h[i] = (h[i - 1] * numP + s[i]) % hashMod;
	}

	int getHash(int L, int R) {
		--L;
		LL res = (h[R] - h[L] * PowP[R - L]) % hashMod;
		return (int)(res < 0 ? res + hashMod : res);
	}
} Hash[MAXN];

int N, Len[MAXN];
char str[MAXN][MAXLEN];

bool check(int len, bool print) {
	map<int, int> cntTimes;
	bool ok = false;

	Rep(i, 1, N) {
		static int h[MAXLEN];
		int cnt = 0;
		for (int L = 1, R = len; R <= Len[i]; ++L, ++R) {
			h[++cnt] = Hash[i].getHash(L, R);
		}
		sort(h + 1, h + cnt + 1);
		Rep(itr, 1, cnt)
			if (itr == 1 || h[itr - 1] != h[itr])
				if ( ++cntTimes[ h[itr] ] > N / 2) {
					ok = true;
				}
	}
	if (ok == false) return false;
	if (!print) return true;

	vector<string> ans;
	Rep(i, 1, N) {
		for (int L = 1, R = len; R <= Len[i]; ++L, ++R) {
			int code = Hash[i].getHash(L, R);
			int &t = cntTimes[code];
			if (t > N / 2) {
				t = -1;
				ans.push_back( string(str[i] + L, str[i] + R + 1) );
			}
		}
	}
	sort(ans.begin(), ans.end());
	for (unsigned i = 0; i < ans.size(); ++i)
		if (i == 0 || ans[i] != ans[i - 1])
			cout << ans[i] << endl;
	return true;
}

bool isFirst = true;
void solve() {
	if (isFirst) isFirst = false; else puts("");
	Rep(i, 1, N) {
		scanf("%s", str[i] + 1);
		Hash[i].set(str[i], Len[i] = strlen(str[i] + 1));
	}
	int L = 0, R = *max_element(Len + 1, Len + N + 1) + 1;
	while (L + 1 != R) {
		int M((L + R) >> 1);
		if (check(M, false)) L = M;
		else R = M;
	}
	if (L > 0)
		check(L, true);
	else
		puts("?");
}

void init() {
	PowP[0] = 1;
	Foru(i, 1, MAXLEN) PowP[i] = PowP[i - 1] * numP % hashMod;
}

int main() {
	init();
	while (scanf("%d", &N), N != 0) solve();
	return 0;
}

