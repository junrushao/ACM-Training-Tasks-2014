#include <cassert>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 505, M = 1005;

int n, m, h[N], pos[M], place[N], nexthigh[N];

int hastop[N];

vector<int> hill[N];

const int INF = 1000000000;

int dp[N][2];

bool check(int i, int j) {
	return hill[j].size() != 0 && (pos[0] < place[i] || pos[m - 1] > place[j]);
}

const double eps = 1e-6;

int geth(int pos) {
	int nx = lower_bound(place, place + n + 2, pos) - place,
		pc = upper_bound(place, place + n + 2, pos) - place - 1;
	if (pos >= place[nx] - h[nx]) {
		return h[nx] - (place[nx] - pos);
	}
	if (pos <= place[pc] + h[pc]) {
		return h[pc] - (pos - place[pc]);
	}
	assert(false);
	return 0;
}

bool see_left(int left, int pos) {
	int mid = place[(upper_bound(place, place + n + 2, pos) - place) - 1];
//cout << "LEFT" << ' ' << left << ' ' << pos << ' ' << mid << endl;
	if (mid <= left || mid >= pos) {
		return true;
	}
	int hpos = geth(pos), hleft = geth(left);
	return (double)(hpos - hleft) / (pos - left) * (mid - left) + hleft >= 50 - eps;
}

bool see_right(int right, int pos) {
	int mid = place[(lower_bound(place, place + n + 2, pos) - place)];
//cout << pos << ' ' << right << ' ' << mid << endl;
	if (mid <= pos || mid >= right) {
		return true;
	}
	int hpos = geth(pos), hright = geth(right);
//cout << hpos << ' ' << hright << endl;
	return (double)(hpos - hright) / (pos - right) * (mid - right) + hright >= 50 - eps;
}

int cost(int l, int r, int sl, int sr) {
	if (hill[r].size() == 0) {
		return 0;
	}
	int left = sl ? place[l] : hill[r].front(),
		right = sr ? place[r] : hill[r].back();
	vector<int> tmp = hill[r];
	if (left <= place[l] + 50) {
		vector<int> ntmp;
		for (int i = 0; i < (int)tmp.size(); ++i) {
			if (!see_left(left, tmp[i])) {
				ntmp.push_back(tmp[i]);
			}
		}
		tmp = ntmp;
	}
	if (right >= place[r] - 50) {
		vector<int> ntmp;
		for (int i = 0; i < (int)tmp.size(); ++i) {
			if (!see_right(right, tmp[i])) {
//cout << "HAHAH" << endl;
				ntmp.push_back(tmp[i]);
			}
		}
		tmp = ntmp;
	}
	for (int i = l + 1; i <= r - 1; ++i) {
		if (hastop[i] != -1 && tmp.size()) {
			tmp.erase(lower_bound(tmp.begin(), tmp.end(), place[i] - 100), upper_bound(tmp.begin(), tmp.end(), place[i] + 100));
		}
	}
	vector<int> need;
	for (int i = 0; i < (int) tmp.size(); ++i) {
		int p = tmp[i];
		need.push_back(lower_bound(place, place + n + 2, p) - place);
	}
	int ret = 0, last = l - 1;
	for (int i = 0; i < (int)need.size(); ++i) {
		if (need[i] <= last + 1) {
			continue;
		} else {
			++ret;
			last = need[i];
		}
	}
	if (sl == 0 && sr == 0 && need.size() && need.front() == need.back()) {
		ret = 0;
	}
	return ret;
}

int main() {
	while (scanf("%d%d", &n, &m) == 2 && (n || m)) {
		h[0] = 100;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", h + i);
		}
		h[n + 1] = 100;
		for (int i = 0; i < m; ++i) {
			scanf("%d", pos + i);
			pos[i] += 200;
		}
		sort(pos, pos + m);
		m = unique(pos, pos + m) - pos;
		{
			int cur = 0;
			for (int i = 0; i <= n + 1; ++i) {
				cur += h[i];
				place[i] = cur;
				cur += h[i];
			}
			int j = 0;
			for (int i = 0; i <= n + 1; ++i) {
				hill[i].clear();
				hastop[i] = -1;
				while (j < m && pos[j] < place[i]) {
					++j;
				}
				if (j < m && pos[j] == place[i]) {
					hastop[i] = j;
				}
			}
			j = 0;
			for (int i = 0; i <= n + 1; ++i) {
				if (h[i] == 50) {
					continue;
				}
				while (j < m && pos[j] < place[i]) {
					hill[i].push_back(pos[j++]);
				}
				while (j < m && pos[j] == place[i]) {
					++j;
				}
			}
			int last = n + 1;
			for (int i = n; i >= 0; --i) {
				nexthigh[i] = last;
				if (h[i] == 100) {
					last = i;
				}
			}
		}
		for (int i = 0; i <= n + 1; ++i) {
			for (int j = 0; j <= 1; ++j) {
				dp[i][j] = INF;
			}
		}
		dp[0][0] = 0;
		for (int i = 0; i <= n; i = nexthigh[i]) {
			for (int j = 0; j < 2; ++j) {
				if (dp[i][j] == INF) {
					continue;
				}
//cout << "DP" << ' ' << i << ' ' << j << ' ' << dp[i][j] << endl;
				for (int k = 0; k < 2; ++k) {
					if (j == 0 && k == 0 && check(i, nexthigh[i])) {
						continue;
					}
					int l = nexthigh[i];
//cout << l << ' ' << k << ' ' << cost(i, l, j, k) << ' ' << k << ' ' << hastop[l] << endl;
					dp[l][k] = min(dp[l][k], 
								   dp[i][j] + cost(i, l, j, k) + (k && hastop[l] == -1));
				}
			}
		}
		printf("%d\n", dp[n + 1][0]);
	}
	return 0;
}
