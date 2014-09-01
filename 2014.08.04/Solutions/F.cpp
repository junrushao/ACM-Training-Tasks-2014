#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1005;
const int INF = 1000000000;

int n, s, k;
int f[N][N], cost[N][N];
int A[N];
vector <int> v[N];

void add(int a) {
	for (int i = a; i <= n; i += (i & (0 - i))) {
		A[i]++;
	}
}

int ask(int a) {
	int ret = 0;
	for (int i = a; i; i -= (i & (0 - i))) {
		ret += A[i];
	}

	return ret;
}

int main() {
	scanf("%d %d %d", &n, &s, &k);
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		v[x].push_back(i);
	}

	for (int i = 1; i <= s; i++) {
		for (int j = 1; j <= n; j++) {
			A[j] = 0;
		}

		cost[i][i - 1] = 0;
		for (int j = i; j <= s; j++) {
			cost[i][j] = cost[i][j - 1];
			for (int k = 0; k < (int)v[j].size(); k++) {
				cost[i][j] += ask(v[j][k]);
			}

			for (int k = 0; k < (int)v[j].size(); k++) {
				add(v[j][k]);
			}
		}
	}

	for (int i = 0; i <= k; i++) {
		for (int j = 0; j <= s; j++) {
			f[i][j] = INF;
		}
	}

	f[0][0] = 0;
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= s; j++) {
			for (int l = 0; l < j; l++) {
				f[i][j] = min(f[i][j], f[i - 1][l] + cost[l + 1][j]);
			}
		}
	}

	printf("%d\n", f[k][s]);
	return 0;
}
