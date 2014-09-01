#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

const int N = 200 + 10;
const int INF = 1000000000;

int n;
char buf[N];
int f[N][N][2];
int sa, sb;
int va[N][2], vb[N][2];

inline void update(int &a, const int &b)
{
	if (a > b) a = b;
}

void solve() {
	scanf("%d", &n);
	sa = sb = 0;
	for(int i = 0; i < n; ++ i) {
		int x, y;
		scanf("%s%d%d", buf, &x, &y);
		if (buf[0] == 'A') {
			va[sa][0] = x;
			va[sa ++][1] = y;
		} else {
			vb[sb][0] = x;
			vb[sb ++][1] = y;
		}
	}

	for(int i = 0; i <= sa; ++ i)
		for(int j = 0; j <= sb; ++ j) {
			f[i][j][0] = f[i][j][1] = INF;
		}
	int last, tmp, tmp2;
	f[0][0][0] = f[0][0][1] = 0;
	for(int i = 0; i <= sa; ++ i) {
		for(int j = 0; j <= sb; ++ j) {
			//cout << i << ' ' << j << ' ' << f[i][j][0] << ' ' << f[i][j][1] << endl;
			last = f[i][j][1];
			tmp = last;
			tmp2 = -10;
			for(int ni = i + 1; ni <= sa; ++ ni) {
				if (va[ni - 1][0] > last)
					last = va[ni - 1][0];
				if (tmp < last + va[ni - 1][1])
					tmp = last + va[ni - 1][1];
				if (tmp < tmp2 + 10)
					update(f[ni][j][0], tmp2 + 10);
				else
					update(f[ni][j][0], tmp);
				tmp2 = f[ni][j][0];
				last += 10;
			}

			last = f[i][j][0];
			tmp = last;
			tmp2 = -10;
			for(int nj = j + 1; nj <= sb; ++ nj) {
				if (vb[nj - 1][0] > last)
					last = vb[nj - 1][0];
				if (tmp < last + vb[nj - 1][1])
					tmp = last + vb[nj - 1][1];
				if (tmp < tmp2 + 10)
					update(f[i][nj][1], tmp2 + 10);
				else
					update(f[i][nj][1], tmp);
				tmp2 = f[i][nj][1];
				last += 10;
			}
		}
	}
	printf("%d\n", min(f[sa][sb][0], f[sa][sb][1]));
}

int main() {
	int c;
	cin >> c;
	for( ; c --; ) {
		solve();
	}
	return 0;
}
