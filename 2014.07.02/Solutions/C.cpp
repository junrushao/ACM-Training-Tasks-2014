#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 10005;

int n, tt;

int t[N];

vector<int> edge[N];

int cal(int u, double x) {
	if (edge[u].size() == 0) {
		return t[u];
	} else {
		vector<int> tmp;
		for (int i = 0; i < (int)edge[u].size(); ++i) {
			int v = edge[u][i];
			tmp.push_back(cal(v, x));
		}
		sort(tmp.begin(), tmp.end());
		for (int i = 0; i < (int)tmp.size(); ++i) {
			if ((double)(i + 1) / (int)tmp.size() >= x / 100) {
				return tmp[i] + t[u];
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &tt);
	for (int i = 1; i < n; ++i) {
		int fa;
		scanf("%d%d", &fa, t + i);
		--fa;
		edge[fa].push_back(i);
	}
	double l = 0, r = 100;
	while (r - l > 1e-7) {
		double m = (l + r) / 2;
		if (cal(0, m) <= tt) {
			l = m;
		} else {
			r = m;
		}
	}
	printf("%.12f\n", (l + r) / 2);
	return 0;
}

