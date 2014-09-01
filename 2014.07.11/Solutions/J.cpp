#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <map>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

const int N = 10000 + 10;
const int V = 2000 + 10;
const int INF = 100000;

int tot;
int len;
int root;
char s[N];
int lch[N], rch[N], father[N], ball[N];
int f[V][V];

void solve() {
	tot = 0;
	len = strlen(s);
	for(int i = 0; i < len; ++ i) {
		lch[i] = rch[i] = -1;
		ball[i] = 0;
	}
	root = tot ++;
	father[root] = -1;
	int cur = root;
	int cnt = 0;
	for(int i = 1; i + 1 < len; ++ i) {
		if (s[i] == '(') {
			if (lch[cur] == -1) {
				father[tot] = cur;
				lch[cur] = tot ++;
				cur = lch[cur];
			} else if (rch[cur] == -1) {
				father[tot] = cur;
				rch[cur] = tot ++;
				cur = rch[cur];
			}
		} else if (s[i] == ')') {
			cur = father[cur];
		} else if (s[i] == 'B') {
			ball[cur] = 1;
			++ cnt;
		}
	}

	//for(int i = 0; i < tot; ++ i) {
		//cout << father[i] << ' ' << lch[i] << ' ' << rch[i] << endl;
		//cout << ball[i] << endl;
	//}

	for(int i = 0; i < tot; ++ i) {
		for(int j = 0; j <= tot; ++ j) {
			f[i][j] = INF;
		}
	}

	for(int i = tot - 1; i >= 0; -- i) {
		int u = i;
		if (lch[u] == -1) {
			assert(rch[u] == -1);
			f[u][ball[u]] = 0;
			f[u][ball[u] ^ 1] = 1;
		} else {
			for(int j = 0; j <= tot; ++ j) {
				int lsize = j / 2;
				for(int tmp = 0; tmp <= (j & 1); ++ tmp, ++ lsize) {
					int rsize = j - lsize;
					f[u][j] = min(f[u][j], f[lch[u]][lsize] + f[rch[u]][rsize]);
				}
			}
		}
	}
	
	if (f[root][cnt] == INF) cout << "impossible" << endl;
	else cout << f[root][cnt] / 2 << endl;
}

int main() {
	for( ; scanf("%s", s) == 1; ) {
		solve();
	}
	return 0;
}