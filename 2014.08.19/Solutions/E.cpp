#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const char nei[28][50] {
"1 2",
"3 4 5 6 7",
"8 9 10 11 12 13",
"14 15 16 17 18",
"19 20 21 22 23 24",
"25 26 27 28 29",
"30 31",
"8 3",
"1 4 9 14 19",
"2 5 10 15 20 25",
"6 11 16 21 26",
"7 12 17 22 27 30",
"13 18 23 28 31",
"29 24",
"19 25",
"8 14 20 26 30",
"3 9 15 21 27 31",
"4 10 16 22 28",
"1 5 11 17 23 29",
"2 6 12 18 24",
"7 13",
"1 2 4 5 6 10 11",
"3 4 8 9 10 14 15",
"6 7 11 12 13 17 18",
"14 15 19 20 21 25 26",
"10 11 15 16 17 21 22",
"17 18 22 23 24 28 29",
"21 22 26 27 28 30 31"
};

const int N = 31;
vector<int> edge[N];

void prepare() {
	for (int i = 0; i < 28; ++i) {
		int l = strlen(nei[i]);
		vector<int> tmp;
		for (int j = 0; j < l; ++j) {
			if (nei[i][j] == ' ') {
				continue;
			} else {
				int k = j, t = 0;
				while (k < l && nei[i][k] != ' ') {
					t = t * 10 + nei[i][k] - '0';
					++k;
				}
				tmp.push_back(t);		
				j = k - 1;
			}
		}
		sort(tmp.begin(), tmp.end());
		for (int j = 0; j < (int)tmp.size(); ++j) {
			int u = tmp[j] - 1;
			for (int k = 0; k < (int)tmp.size(); ++k) {
				int v = tmp[k] - 1;
				if (u != v) {
					edge[u].push_back(v);
				}
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		sort(edge[i].begin(), edge[i].end());
		edge[i].erase(unique(edge[i].begin(), edge[i].end()), edge[i].end());
	}
}

int k, cnt;

int ans[N];

int use[N][N];

void paint(int pos, int col, int val = 1) {
	if (val == 1) {
		ans[pos] = col + 1;
	} else {
		ans[pos] = 0;
	}
	for (int i = 0; i < (int)edge[pos].size(); ++i) {
		int v = edge[pos][i];
		use[v][col] += val;
	}
}

void go(int pos) {
	if (pos == N) {
		--cnt;
		if (cnt == 0) {
			puts("Found");
			for (int i = 0; i < N; ++i) {
				printf("%d%c", ans[i], i == N - 1 ? '\n' : ' ');
			}
			exit(0);
		}
		return;
	}
	if (!ans[pos]) {
		for (int i = 0; i < k; ++i) {
			if (use[pos][i]) {
				continue;
			}
			paint(pos, i);
			go(pos + 1);
			paint(pos, i, -1);
		}
	} else {
		go(pos + 1);
	}
}

int main() {
	prepare();
	scanf("%d%d", &k, &cnt);
	for (int i = 0; i < N; ++i) {
		int t;
		scanf("%d", &t);
		if (t) {
			paint(i, t - 1);
		}
	}
	go(0);
	puts("No way");
	return 0;
}

