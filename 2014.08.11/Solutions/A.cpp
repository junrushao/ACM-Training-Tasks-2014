#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, q;

const int N = 105;
long long tag[N][N][N];

void debug(long long tag[N][N][N]) {
	for (int x = 1; x <= n; ++x) {
		for (int z = 1; z <= x; ++z) {
			for (int y = 1; y <= x; ++y) {
				if (y < z) {
					printf("  ");
				} else { 
					printf("%lld ", tag[x][y][z]);
				}
			}
			printf("\n");
		}
		printf("\n");
	}
}

long long sumr[N][N][N], sumd[N][N][N], sumc[N][N][N];

int main() {
	while (scanf("%d%d%d", &n, &m, &q) == 3) {
		for (int x = 0; x <= n + 2; ++x) {
			for (int y = 0; y <= x; ++y) {
				for (int z = 0; z <= y; ++z) {
					tag[x][y][z] = 0;
				}
			}
		}
		while (m--) {
			int sx, sy, sz, l;
			scanf("%d%d%d%d", &sx, &sy, &sz, &l);
			for (int i = 1; i <= l; ++i) {
				int x = sx + i - 1;
				++tag[x][sy][sz];	
				--tag[x][sy + i + 1][sz + i + 1];

				--tag[x][sy][sz + 1];
				++tag[x][sy + i][sz + i + 1];

				--tag[x][sy + i][sz];
				++tag[x][sy + i + 1][sz + 1];
			}
		}
		for (int x = 1; x <= n; ++x) {
			for (int y = 1; y <= x; ++y) {
				for (int i = 0; i < x - y + 1; ++i) {
					tag[x][y + i][i + 1] += tag[x][y + i - 1][i];
				}
			}
		}
		for (int x = 1; x <= n; ++x) {
			for (int y = 2; y <= x; ++y) {
				tag[x][y][1] += tag[x][y - 1][1];
			}
			for (int z = 2; z <= x; ++z) {
				tag[x][z][z] += tag[x][z][z - 1];
				tag[x][z][z] -= tag[x][z - 1][z - 1];
				for (int y = z + 1; y <= x; ++y) {
					tag[x][y][z] += tag[x][y][z - 1];
					tag[x][y][z] += tag[x][y - 1][z];
					tag[x][y][z] -= tag[x][y - 1][z - 1];	
				}
			}
		}
//debug(tag);
		for (int x = 1; x <= n; ++x) {
			for (int z = 1; z <= x; ++z) {
				sumr[x][z - 1][z] = 0;
				for (int y = z; y <= x; ++y) {
					sumr[x][y][z] = sumr[x][y - 1][z] + tag[x][y][z];
				}
			}
			for (int y = 1; y <= x; ++y) {
				sumd[x][y - 1][0] = 0;
				for (int z = 1; y + z - 1 <= x; ++z) {
					sumd[x][y + z - 1][z] = sumd[x][y + z - 2][z - 1] + sumr[x][y + z - 1][z];
				}
			}
			for (int y = 1; y <= x; ++y) {
				sumc[x][y][0] = 0;
				for (int z = 1; z <= y; ++z) {
					sumc[x][y][z] = sumc[x][y][z - 1] + sumr[x][y][z];
				}
			}
		}
		while (q--) {
			int sx, sy, sz, l; 
			long long ans = 0;
			scanf("%d%d%d%d", &sx, &sy, &sz, &l);
			for (int x = sx; x < sx + l; ++x) {
				int i = x - sx;
				ans += sumc[x][sy + i][sz + i] - sumc[x][sy + i][sz - 1] + (sy >= 2 ? sumd[x][sy - 2][sz - 1] : 0ll) - sumd[x][sy + i - 1][sz + i];
//cout << x << ' ' << sy + i - 1 << ' ' << sz + i << ' ' << sumd[x][sy + i - 1][sz + i] << endl;
			}
			printf("%I64d\n", ans);
		}
	}
	return 0;
}
