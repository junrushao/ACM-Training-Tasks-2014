#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, k;

const int M = 105;
vector<int> bus[M];

const int K = 105;
int t[K], r[K];

int gettime() {
	int h, m;
	scanf("%d:%d", &h, &m);
	return h * 60 + m;
}

const int N = 105;

int minf, maxf;

int theBus, source, target;

bool check(int uu, int vv, int t) {
	int dis = vv - uu, u = bus[theBus][uu], v = bus[theBus][vv];
	for (int i = 0; i < k - 1; ++i) {
		int b = r[i], m = bus[b].size();
		int cntu = -1, cntv = -1, cnt0 = -1;
		for (int j = 0; j < m; ++j) {
			if (bus[b][j] == u) {
				cntu = j;
			}
			if (bus[b][j] == v) {
				cntv = j;
			}
			if (bus[b][j] == 0) {
				cnt0 = j;
			}
		}
		if (cntu == -1 || cntv == -1 || cntu > cntv) {
			continue;
		}
		int rt = ::t[i] - cnt0 + cntu;
		if (rt > t) {
			continue;
		}
		if (rt < t) {
			return false;
		} else {
			if (cntv - cntu < dis || cntv - cntu == dis && r[i] < r[k - 1]) {
				return false;
			}
		}
	}
	return true;
}

void calf() {
	minf = 13, maxf = 0;
	for (int i = source + 1; i < (int)bus[theBus].size(); ++i) {
		if (check(source, i, t[k - 1])) {
			if (i < target) {
				minf = 0;
			} else {
				maxf = 13;
			}
		}
	}
}

int ming, maxg;

void calg() {
	ming = 42, maxg = 0;
	for (int i = 0; i < source; ++i) {
		for (int j = source + 1; j < (int)bus[theBus].size(); ++j) {
			if (check(i, j, t[k - 1] - (source - i))) {
				if (j < target) {
					ming = 0;
				} else {
					maxg = 42;
				}
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++i) {
		int tmp;
		scanf("%d", &tmp);
		while (tmp != -1) {
			--tmp;
			bus[i].push_back(tmp);
			scanf("%d", &tmp);
		}
	}
	scanf("%d", &k);
	for (int i = 0; i < k; ++i) {
		t[i] = gettime();
		scanf("%d", r + i);
		--r[i];
	}
	theBus = r[k - 1], source = -1, target = -1;
	for (int i = 0; i < (int)bus[theBus].size(); ++i) {
		int u = bus[theBus][i];
		if (u == 0) {
			source = i;
		} else if (u == 1) {
			target = i;
		}
	}
	calf();
	calg();
	printf("%d %d\n", minf + ming, maxf + maxg);
	return 0;
}

