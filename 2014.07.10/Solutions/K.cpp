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

const int D = 7;

long long calc(pair<int, int> a, pair<int, int> b)
{
	long long dx = a.first - b.first;
	long long dy = a.second - b.second;
	return dx * dx + dy * dy;
}

void solve() {
	long long ret = 0;
	set< pair<int, int> > s;
	long long x = 0, y = 0;
	long long Ax, Bx, Cx;
	long long Ay, By, Cy;
	int n;
	cin >> n;
	n --;
	cin >> Ax >> Bx >> Cx;
	cin >> Ay >> By >> Cy;
	x = (x * Ax + Bx) % Cx;
	y = (y * Ay + By) % Cy;
	s.insert(make_pair(x, y));
	long long ans = -1;
	for(int j = 0; j < n; ++ j) {
		x = (x * Ax + Bx) % Cx;
		y = (y * Ay + By) % Cy;
		set<pair<int, int> >::iterator it = s.lower_bound(make_pair(x, y)), tmp;
		pair<int, int> cur;
		long long tmpans;
		if (it == s.end()) -- it;

		{
			tmp = it;
			for(int i = 0; i < D; ++ i) {
				cur = *tmp;
				tmpans = calc(cur, make_pair(x, y));
				if (ans < 0 || tmpans < ans)
					ans = tmpans;
				if (tmp == s.begin()) break;
				-- tmp;
			}
			++ it;
		}

		if (it != s.end()) {
			tmp = it;
			for(int i = 0; i < D; ++ i) {
				cur = *tmp;
				tmpans = calc(cur, make_pair(x, y));
				if (ans < 0 || tmpans < ans)
					ans = tmpans;
				++ tmp;
				if (tmp == s.end()) break;
			}
		}

		ret += ans;
		s.insert(make_pair(x, y));
	}
	cout << ret << endl;
}

int main() {
	int test; cin >> test;
	for( ; test --; ) {
		solve();
	}
	return 0;
}