#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1005;
int n, cost[N];

long long cal(vector<int> &a, vector<int> &b, vector<int> &c) {
	sort(a.begin(), a.end());
	reverse(a.begin(), a.end());
	sort(b.begin(), b.end());
	long long ret = 0, cur = 0;
	for (int i = 0; i < (int)c.size(); ++i) {
		cur += c[i];
	}
	for (int i = 0; i < (int)a.size(); ++i) {
		cur += a[i];
	}
	for (int i = 0; i < (int)a.size(); ++i) {
		cur -= a[i];
		ret += cur;
	}
	for (int i = 0; i < (int)b.size(); ++i) {
		cur += b[i];
		ret += cur;
	}
	return ret;
}

char s[N], e[N];

int main() {
	while (scanf("%d", &n) == 1 && n) {
		scanf("%s%s", s, e);
		for (int i = 0; i < n; ++i) {
			scanf("%d", cost + i);
		}
		vector<int> zero_one, one_zero, one_one;
		for (int i = 0; i < n; ++i) {
			if (s[i] == '0' && e[i] == '1') {
				zero_one.push_back(cost[i]);
			}
			if (s[i] == '1' && e[i] == '1') {
				one_one.push_back(cost[i]);
			}
			if (s[i] == '1' && e[i] == '0') {
				one_zero.push_back(cost[i]);
			}
		}
		sort(one_one.begin(), one_one.end());
		long long ans = cal(one_zero, zero_one, one_one);
		while (one_one.size()) {
			int v = one_one.back();
			one_one.pop_back();
			one_zero.push_back(v);
			zero_one.push_back(v);
			ans = min(ans, cal(one_zero, zero_one, one_one));
		}
		static int id = 0;
		printf("Case %d: ", ++id);
		cout << ans << endl;
	}
	return 0;
}
