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

const int N = 10;

int n, k;
int high[N];
map< pair<int, vector<int> >, int> s;

int okNext(vector<int> cur, int ns, vector<int> &nxt)
{
	nxt.clear();
	for(int i = 0; i < 7; ++ i) {
		int tmp = cur[i] + (ns >> i & 1);
		if (tmp > high[i]) {
			return false;
		}
		nxt.push_back(tmp);
		if (i && nxt[i] > nxt[i - 1]) {
			return false;
		}
	}
	return true;
}

int dfs(int cur, vector<int> lines)
{
	if (s.count(make_pair(cur, lines))) {
		return s[make_pair(cur, lines)];
	}
	if (cur >= k) return 0;
	vector<int> nxt;
	int ret = 0;
	for(int ns = 0; ns < (1 << 7); ++ ns) {
		if (okNext(lines, ns, nxt)) {
			ret += dfs(cur + 1, nxt);
		}
	}
	s[make_pair(cur, lines)] = ret;
	return ret;
}

void solve() {
	s.clear();
	memset(high, 0, sizeof high);
	int x;
	for(int i = 0; i < n; ++ i) {
		cin >> x;
		for(int j = 0; j < x; ++ j) {
			++ high[j];
		}
	}
	cin >> k;
	vector<int> goal;
	for(int i = 0; i < 7; ++ i) {
		goal.push_back(high[i]);
	}
	s[make_pair(k, goal)] = 1;
	goal.clear();
	for(int i = 0; i < 7; ++ i) {
		goal.push_back(0);
	}
	cout << dfs(0, goal) << endl;
}

int main() {
	for( ; cin >> n; ) {
		solve();
	}
}