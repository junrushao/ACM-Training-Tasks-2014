#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cassert>
#include <bitset>
#include <numeric>

using namespace std;

const int MAXN = 1111;
const int MAXM = 411111;

int to[MAXM], e_next[MAXM], edge[MAXN + MAXN], edge_cnt, in_deg[MAXN + MAXN];

void add_edge(int u, int v) {
//	fprintf(stderr, "%d ---> %d\n", u, v);
	++in_deg[v];
	e_next[edge_cnt] = edge[u];
	edge[u] = edge_cnt;
	to[edge_cnt] = v;
	++edge_cnt;
}

bool solve(int n, vector<pair<int, int> > rel_I, vector<pair<int, int> > rel, vector<pair<int, int> > &box) {
	edge_cnt = 0;
	for (int index = 0; index < n + n; ++index) {
		edge[index] = -1;
		in_deg[index] = 0;
	}
	for (int index = 0; index < n; ++index) {
		add_edge(index * 2, index * 2 + 1);
	}
	for (int index = 0; index < (int)rel_I.size(); ++index) {
		add_edge(rel_I[index].first * 2, rel_I[index].second * 2 + 1);
		add_edge(rel_I[index].second * 2, rel_I[index].first * 2 + 1);
	}
	for (int index = 0; index < (int)rel.size(); ++index) {
		add_edge(rel[index].first * 2 + 1, rel[index].second * 2);
	}
	int ret = n + n;
//	fprintf(stderr, "=================\n");
	vector<int> queue;
	for (int index = 0; index < n + n; ++index) {
		if (in_deg[index] == 0) {
			queue.push_back(index);
			--ret;
		}
	}
	int q_it = 0;
	while (q_it < queue.size()) {
		int v = queue[q_it++];
		for (int e = edge[v]; e != -1; e = e_next[e]) {
			int v_n = to[e];
			--in_deg[v_n];
			if (in_deg[v_n] == 0) {
				queue.push_back(v_n);
				--ret;
			}
		}
	}
	box = vector<pair<int, int> >(n, make_pair(0, 0));
	for (int index = 0; index < (int)queue.size(); ++index) {
		if (queue[index] & 1) {
			box[queue[index] >> 1].second = index;
		}
		else {
			box[queue[index] >> 1].first = index;
		}
	}
	return ret == 0;
}

int main() {
	int n, R;
	while (scanf("%d %d", &n, &R) == 2 && (n != 0 || R != 0)) {
		vector<pair<int, int> > rel_I, rel_X, rel_Y, rel_Z;
		for (int index = 0; index < R; ++index) {
			char buf[5];
			int u, v;
			scanf("%s %d %d", buf, &u, &v);
			--u; --v;
			if (buf[0] == 'I') {
				rel_I.push_back(make_pair(u, v));
			}
			else if (buf[0] == 'X') {
				rel_X.push_back(make_pair(u, v));
			}
			else if (buf[0] == 'Y') {
				rel_Y.push_back(make_pair(u, v));
			}
			else if (buf[0] == 'Z') {
				rel_Z.push_back(make_pair(u, v));
			}
			else {
				assert(false);
			}
		}

		vector<pair<int, int> > box_X, box_Y, box_Z;
		bool valid_X = solve(n, rel_I, rel_X, box_X);
		bool valid_Y = solve(n, rel_I, rel_Y, box_Y);
		bool valid_Z = solve(n, rel_I, rel_Z, box_Z);

		static int task_index = 0;
		printf("Case %d: ", ++task_index);
		if (!valid_X || !valid_Y || !valid_Z) {
			puts("IMPOSSIBLE");
			puts("");
		}
		else {
			puts("POSSIBLE");
			for (int index = 0; index < n; ++index) {
				printf("%d ", box_X[index].first);
				printf("%d ", box_Y[index].first);
				printf("%d ", box_Z[index].first);
				printf("%d ", box_X[index].second);
				printf("%d ", box_Y[index].second);
				printf("%d\n", box_Z[index].second);
			}
			puts("");
		}
	}
	return 0;
}
