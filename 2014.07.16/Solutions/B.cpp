#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 2505, M = 505;

int n, m, rnk[N][M];

bool beat(int a, int b)  {
	int wins = 0;
	for (int i = 0; i < m; ++i) {
		wins += rnk[a][i] < rnk[b][i];
	}
	return wins * 2 >= m;
}

bool mem[N];

int main() {
	while (scanf("%d%d", &m, &n) == 2 && n) {
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				int a;
				scanf("%d", &a);
				rnk[a][i] = j;
			}
		}
		memset(mem, 0, sizeof(bool) * n);
		int ans = -1;
		for (int i = 0; i < n; ++i) {
			if (mem[i]) {
				continue;
			}
			for (int j = 0; j < n && !mem[i]; ++j) {
				if (i == j) {
					continue;
				}
				if (beat(j, i)) {
					mem[i] = true;
				} else {
					mem[j] = true;
				}
			}
			if (!mem[i]) {
				ans = i;
				break;
			}
		}
		static int id = 0;
		printf("Case %d: ", ++id);
		if (ans != -1) {
			printf("%d\n", ans);
		} else {
			printf("No Condorcet winner\n");
		}
	}
	return 0;
}
