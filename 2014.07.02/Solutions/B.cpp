#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

char name[25];

int main() {
	scanf("%d", &n);
	vector<pair<int, pair<int, string> > > ath;
	for (int i = 0; i < n; ++i) {
		int m, s, d;
		scanf("%s%d:%d.%d", name, &m, &s, &d);
		int t0 = m * 600 + s * 10 + d, t1 = t0 + i * 300;
		ath.push_back(make_pair(t1, make_pair(t0, name)));
	}
	sort(ath.begin(), ath.end());
	vector<string> ans;
	int best = 1000000000;
	for (int i = 0; i < n; ++i) {
		if (ath[i].second.first < best) {
			ans.push_back(ath[i].second.second);
			best = ath[i].second.first;
		}
	}
	sort(ans.begin(), ans.end());
	printf("%d\n", (int)ans.size());
	for (int i = 0; i < (int)ans.size(); ++i) {
		printf("%s\n", ans[i].c_str());
	}
	return 0;
}

