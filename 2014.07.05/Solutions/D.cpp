#include<set>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int MOD = 1000000007;
int n, m, k;

inline long long cb(long long n) {
	return n * (n + 1) / 2 % MOD;
}

int main() {
	while (scanf("%d%d%d", &n, &m, &k) == 3) {
		vector<pair<int, int> > evt;
		evt.push_back(make_pair(0, -1));
		for (int i = 0; i < k; ++i) {
			int px, py;
			scanf("%d%d", &px, &py);
			evt.push_back(make_pair(px, py));
		}
		sort(evt.begin(), evt.end());
		long long ans = cb(n) * cb(m) % MOD;
		for (int i = 1; i < (int)evt.size(); ++i) {
			if (evt[i - 1].first == evt[i].first) {
				continue;
			}
			long long xmin0 = evt[i - 1].first + 1, xmin1 = evt[i].first;
			long long met = cb(m);
			ans = (ans - cb(xmin1 - 1 - xmin0 + 1) * met % MOD + MOD) % MOD;
			set<pair<int, int> > interval;
			interval.insert(make_pair(m, 1));
			for (int j = i; j < (int)evt.size(); ++j) {
				int k = j;
				while (k < (int)evt.size() && evt[k].first == evt[j].first) {
					int y = evt[k].second;
					set<pair<int, int> >::iterator it = interval.lower_bound(make_pair(y, -1));	
					if (it != interval.end() && (*it).second <= y) {
						int l = it->second, r = it->first;
						interval.erase(it);
						met = (met - cb(r - l + 1) + MOD) % MOD;
						if (l <= y - 1) {
							interval.insert(make_pair(y - 1, l));
							met = (met + cb(y - 1 - l + 1)) % MOD;
						}
						if (y + 1 <= r) {
							interval.insert(make_pair(r, y + 1));
							met = (met + cb(r - (y + 1) + 1)) % MOD;
						}
					}

					++k;
				}
				long long xmax0 = evt[j].first, xmax1 = k < (int)evt.size() ? evt[k].first - 1 : n;
				ans = (ans - (xmin1 - xmin0 + 1) * (xmax1 - xmax0 + 1) % MOD * met % MOD + MOD) % MOD;
				j = k - 1;
			}
		}
		{
			long long xmin0 = evt.back().first + 1, xmin1 = n;
			long long met = cb(m);
			ans = (ans - cb(xmin1 - xmin0 + 1) * met % MOD + MOD) % MOD;
		}
		printf("%d\n", (int)ans);
	}
	return 0;
}
