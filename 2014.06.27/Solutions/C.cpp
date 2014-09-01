#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

const int N = 155;
const int M = 3333;

int stamp[N][N], f[N][N], times;
vector<pair<int, pair<int, int> > > e;
int n, m, qq;
vector<pair<int, pair<int, int> > > q[N];
int ans[M];

void solve(int s) {
	times++;
	stamp[s][0] = times;
	f[s][0] = 0;
	for(int i = 0; i < m; i++) {
		int cost = e[i].first;
		int a = e[i].second.first, b = e[i].second.second;
		for(int j = 0; j < n; j++) {
			if (stamp[a][j] == times) {
				if (stamp[b][j + 1] != times || stamp[b][j + 1] == times && f[b][j + 1] > f[a][j] + cost) {
					f[b][j + 1] = f[a][j] + cost;
					stamp[b][j + 1] = times;
				}
			}
		}
	}
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d %d", &n, &m, &qq);
		e.clear();
		for(int i = 1; i <= m; i++) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			e.push_back(make_pair(c, make_pair(a, b)));
		}		
		sort(e.begin(), e.end());
		for(int i = 1; i <= n; i++) {
			q[i].clear();
		}
		for(int i = 1; i <= qq; i++) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			q[a].push_back(make_pair(i, make_pair(b, c)));
		}
		for(int source = 1; source <= n; source ++) {
			if ((int)q[source].size() == 0)
				continue;
			solve(source);
			for(int it = 0; it < (int)q[source].size(); it++) {
				int target = q[source][it].second.first;
				int limit = q[source][it].second.second;
				int result = -1;
				for(int i = 0; i <= limit && i <= n; i++) {
					if (stamp[target][i] == times && (result == -1 || result > f[target][i])) {
						result = f[target][i];
					}
				}
				ans[q[source][it].first] = result;
			}
		}
		for(int i = 1; i <= qq; i++)
			printf("%d\n", ans[i]);
	} 
	return 0;
}


