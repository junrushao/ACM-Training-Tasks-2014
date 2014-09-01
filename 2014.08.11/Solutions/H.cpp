#include <set>
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100005 << 1, MOD = 1000000007;

int n;
long long m;
pair<long long, long long> point[N];

#define transform TRANSFORM

int fa[N], transform[N];

inline long long sqr(long long x) {
	x %= MOD;
	return x * x % MOD;
}

int find(int u) {
	return u == fa[u] ? u : fa[u] = find(fa[u]);
}

void merge(int u, int v) {
	fa[u] = v;
}

int main() {
	ios::sync_with_stdio(false);
	while (cin >> n >> m) {
		map<pair<long long, long long>, int> counter;
		map<long long, set<int> > row, column;
		for (int i = 0; i < n; ++i) {
			cin >> point[i].first >> point[i].second;
			++counter[point[i]];
			row[point[i].first].insert(i);
			column[point[i].second].insert(i);
			fa[i] = i;
			transform[i] = i;
		}
		int t, top = n;
		cin >> t;
		long long lastans = 0;
		while (t--) {
			int x;
			char op[2];
			cin	>> op;
			if (op[0] == 'Q') {
				cin >> x;
				x ^= lastans;
				--x;
				x = find(transform[x]);
				long long r = point[x].first, c = point[x].second, ans = 0;
				vector<int> del;
				for (set<int>::iterator it = row[r].begin(); it != row[r].end(); ++it) {
					if ((*it) != x) {
						long long u = *it, nr = point[u].first, nc = point[u].second, sz = counter[point[u]];
						counter[point[x]] += sz;
						counter[point[u]] -= sz;
						(ans += (sqr((nr - r) % MOD) + sqr((nc - c) % MOD)) % MOD * sz % MOD) %= MOD;
						merge(u, x);
						del.push_back(u);
					}
				}
				for (int i = 0; i < (int)del.size(); ++i) {
					row[r].erase(del[i]);
				}
				del.clear();
				for (set<int>::iterator it = column[c].begin(); it != column[c].end(); ++it) {
					if ((*it) != x) {
						long long u = *it, nr = point[u].first, nc = point[u].second, sz = counter[point[u]];
						counter[point[x]] += sz;
						counter[point[u]] -= sz;
						(ans += (sqr((nr - r) % MOD) + sqr((nc - c) % MOD)) % MOD * sz % MOD) %= MOD;
						merge(u, x);
						del.push_back(u);
					}
				}
				for (int i = 0; i < (int)del.size(); ++i) {
					column[c].erase(del[i]);
				}
				cout << ans << endl;
				lastans = ans;
			} else {
				long long d;
				cin >> x >> d;
				x ^= lastans;
				--x;
				int ori = x;
				x = find(transform[x]);
				long long r = point[x].first, c = point[x].second, 
						  nr = r, nc = c;
				counter[point[x]]--;
				if (op[0] == 'U') {
					nr -= d;
				} else if (op[0] == 'L') {
					nc -= d;
				} else if (op[0] == 'D') {
					nr += d;
				} else if (op[0] == 'R') {
					nc += d;
				}
				point[top] = make_pair(nr, nc);
				fa[top] = top;
				row[nr].insert(top);
				column[nc].insert(top);
				transform[ori] = top;
				counter[point[top]]++;
				++top;
			}
		}
	}
	return 0;
}

