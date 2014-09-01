#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n;

double abi;
char buf[25];

const int N = 2505;
bool fa[N][N];
double dp[N][N];

int main() {
	bool first = true;
	while (scanf("%d", &n) == 1 && n) {
		if (!first) {
			printf("\n");
		} else {
			first = false;
		}
		vector<pair<double, string> > knight;
		for (int i = 0; i < n; ++i) {
			scanf("%s%lf", buf, &abi);
			knight.push_back(make_pair(abi, buf));
		}
		sort(knight.begin(), knight.end());
		int m = 1;
		while (m < n) {
			m <<= 1;
		}
		m -= n;
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= m; ++j) {
				dp[i][j] = 1e100;
			}
		}
		dp[0][0] = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j <= m; ++j) {
				if (i + 1 < n) {
					double cost = knight[i].first - knight[i + 1].first;
					cost *= cost;
					if (dp[i + 2][j] > dp[i][j] + cost) {
						dp[i + 2][j] = dp[i][j] + cost;
						fa[i + 2][j] = true;
					}
				}
				if (j < m) {
					if (dp[i + 1][j + 1] > dp[i][j]) {
						dp[i + 1][j + 1] = dp[i][j];
						fa[i + 1][j + 1] = false;
					}
				}
			}
		}
		vector<string> ans;
		int i = n, j = m;
		while (i || j) {
			if (!fa[i][j]) {
				ans.push_back(knight[i - 1].second);
				i -= 1;
				j -= 1;
			} else {
				i -= 2;
			}
		}
		for (int i = 0; i < (int)ans.size(); ++i) {
			printf("%s\n", ans[i].c_str());
		}
	}
	return 0;
}
