#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n;

bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
	return (long long)a.first * b.second < (long long)a.second * b.first;
}

int main() {
	while (scanf("%d", &n) == 1) {
		vector<pair<int, int> > b(n);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &b[i].first);
		}
		for (int i = 0; i < n; ++i) {
			scanf("%d", &b[i].second);	
		}
		sort(b.begin(), b.end(), cmp);
		long long ans = 0, t = 0;
		for (int i = 0; i < n; ++i) {
			t += b[i].first;
			ans += t * b[i].second;
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
