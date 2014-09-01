
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
#define Rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define Foru(i, a, b) for(int i = (a); i < (b); ++i)

using namespace std;

typedef long long LL;

const int MAXN = 2033;
const int MAXS = 2000033;

struct seg {
	LL a, b, c, norm;

	bool operator < (const seg &rhs) const {
		if (a != rhs.a) return a < rhs.a;
		if (b != rhs.b) return b < rhs.b;
		if (norm != rhs.norm) return norm < rhs.norm;
		return c < rhs.c;
	}
};

inline LL sqr(LL x) {
	return x * x;
}

int N, X[MAXN], Y[MAXN];
seg S[MAXS];

inline LL C2(LL x) {
	return x * (x - 1) / 2;
}

void solve(){
	scanf("%d", &N);
	Rep(i, 1, N) scanf("%d %d", X + i, Y + i);
	
	int cnt = 0;
	Rep(i, 1, N) Rep(j, i + 1, N) {
		LL x1 = X[i], x2 = X[j], y1 = Y[i], y2 = Y[j];
		if (x1 == x2 && y1 == y2) continue;

		++cnt;
		LL &a = S[cnt].a = y1 - y2;
		LL &b = S[cnt].b = x2 - x1;
		LL &c = S[cnt].c = x1 * y2 - x2 * y1;
		S[cnt].norm = sqr(x1 - x2) + sqr(y1 - y2);

		if (a < 0) a = -a, b = -b, c = -c;
		else if (a == 0 && b < 0) b = -b, c = -c;
	}
	sort(S + 1, S + cnt + 1);
	
	LL ans = 0;
	for (int L1 = 1, R1; L1 <= cnt; L1 = R1) {
		LL a = S[L1].a, b = S[L1].b, norm = S[L1].norm;
		for (R1 = L1; R1 <= cnt && S[R1].a == a && S[R1].b == b && S[R1].norm == norm; ++R1);

		// [L1, R1) same a, b, norm
		ans += C2(R1 - L1);
		for (int L2 = L1, R2; L2 < R1; L2 = R2) {
			LL c = S[L2].c;
			for (R2 = L2; R2 < R1 && S[R2].c == c; ++R2);
			// [L2, R2) same c;
			ans -= C2(R2 - L2);
		}
	}
	cout << ans / 2 << endl;
}

int main() {
	solve();
	return 0;
}

