#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 105;
int n, g[N][N];

vector<pair<int, int> > pos[N];
int p[N];

vector<pair<int, int> > getpos(int dis) {
	int l = 0, r = sqrt(dis) + 1;
	vector<pair<int, int> > ret;
	while (l <= r) {
		int s = l * l + r * r;
		if (s == dis) {
			ret.push_back(make_pair(l, r));
			++l;
		} else if (s < dis) {
			++l;
		} else {
			--r;
		}
	}
	return ret;
}

inline int sqr(long long x) {
	return x * x;
}

inline bool judge(int i, int j) {
	long long rd = sqr(pos[i][p[i]].first - pos[j][p[j]].first) + sqr(pos[i][p[i]].second - pos[j][p[j]].second);
	return g[i][j] == rd;
}

bool go(int dep) {
	if (dep == n) {
		return true;
	}
	p[dep] = 0;
	for (int &i = p[dep]; i < (int)pos[dep].size(); ++i) {
		bool check = true;
		for (int j = 1; j < dep && check; ++j) {
			check = judge(j, dep);
		}
		if (check) {
			if (go(dep + 1)) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%d", &g[i][j]);
		}
	}
	bool meet = false;	
	for (int i = 0; i < n; ++i) {
		if (g[i][0] == 0) {
			pos[i].push_back(make_pair(0, 0));
		} else {
			vector<pair<int, int> > tmp = getpos(g[i][0]);
			for (int j = 0; j < (int)tmp.size(); ++j) {
				int a = tmp[j].first, b = tmp[j].second;
				pos[i].push_back(make_pair(a, b));
				if (meet) {
					if (a != 0) {
						pos[i].push_back(make_pair(-a, b));
					}
					if (b != 0) {
						pos[i].push_back(make_pair(a, -b));
					}
					if (a != 0 && b != 0) {
						pos[i].push_back(make_pair(-a, -b));
					}
					if (a != b) {
						pos[i].push_back(make_pair(b, a));
						if (a != 0) {
							pos[i].push_back(make_pair(b, -a));
						}
						if (b != 0) {
							pos[i].push_back(make_pair(-b, a));
						}
						if (a != 0 && b != 0) {
							pos[i].push_back(make_pair(-b, -a));
						}
					}
				}
			}
			meet = true;
		}
/*
cout << i << endl;
for (int j = 0; j < (int)pos[i].size(); ++j) {
	cout << pos[i][j].first << ' ' << pos[i][j].second << endl;
}
*/
	}
	if (go(0)) {
		for (int i = 0; i < n; ++i) {
			printf("%d %d\n", pos[i][p[i]].first, pos[i][p[i]].second);
		}
	} else {
		printf("Impossible\n");
	}
	return 0;
}
