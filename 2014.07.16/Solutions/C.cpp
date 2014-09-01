#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n, q;

const int V = 65;

int v;
long long dp[V];

void bp(vector<pair<int, int> > &vs) {
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	for (int i = 0; i < (int)vs.size(); ++i) {
		int w = vs[i].first, m = vs[i].second;
		for (int j = 0; j < m; ++j) {
			for (int k = v - w; k >= 0; --k) {
				dp[k + w] += dp[k];
			}
		}
	}
}

int main() {
	while (scanf("%d%d", &n, &q) == 2 && n) {
		vector<pair<int, int> > vs;
		v = 0;
		for (int i = 0; i < n; ++i) {
			int vi, mi;
			scanf("%d%d", &vi, &mi);	
			vs.push_back(make_pair(vi, mi));
			v += vi * mi;
		}
		static int id = 0;
		printf("Case %d:", ++id);
		for (int i = 0; i < n; ++i) {
			--vs[i].second;
			bp(vs);
			long long cnt = 0;
			for (int j = 0; j <= v - vs[i].first; ++j) {
				if (j < q && j + vs[i].first >= q) {
					cnt += dp[j];
				}
			}
			++vs[i].second;
			cout << ' ' << cnt;
		}
		printf("\n");	
	}
	return 0;
}
