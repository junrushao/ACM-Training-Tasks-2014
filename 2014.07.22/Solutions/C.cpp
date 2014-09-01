#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int a[10][10];

pair<int, int> len(int x, int y) {
	int i, j;
	pair<int, int> ans;
	ans.first = ans.second = 0;
	i = x, j = y;
	while (a[i][j]) {
		ans.first++;
		i--;
	}
	i = x + 1, j = y;
	while (a[i][j]) {
		ans.first++;
		i++;
	}
	i = x, j = y;
	while (a[i][j]) {
		ans.second++;
		j++;
	}
	i = x, j = y - 1;
	while (a[i][j]) {
		ans.second++;
		j--;
	}
	return ans;
}

int main() {
	while (1) {
		int n, i, j, k, p, x, y, sli;
		scanf("%d", &n);
		if (n == 0) {
			return 0;
		}
		for (i = 0; i <= 8; i++) {
			for (j = 0; j <= 8; j++) {
				a[i][j] = 0;
			}
		}
		sli = 0;
		while (n--) {
			scanf("%d%d", &x, &y);
			if (sli == 1) {
				continue;
			}
			i = 1, j = y;
			while (a[i][j]) {
				i++;
			}
			a[i][j] = x;
			if (i > 7) {
				printf("Game Over!\n\n");
				sli = 1;
				continue;
			}
			p = 1;
			while (p) {
				p = 0;
				vector<pair<int, int> > que;
				que.clear();
				for (i = 1; i <= 7; i++) {
					for (j = 1; j <= 7; j++) {
						if (a[i][j]) {
							pair<int, int> ans = len(i, j);
							if (ans.first == a[i][j] || ans.second == a[i][j]) {
								que.push_back(make_pair(i, j));
								p = 1;
							}
						}
					}
				}
				for (i = 0; i < (int)que.size(); i++) {
					a[que[i].first][que[i].second] = 0;
				}
				for (i = 6; i >= 1; i--) {
					for (j = 1; j <= 7; j++) {
						if (a[i][j] == 0 && a[i + 1][j] != 0) {
							for (k = i; k <= 6; k++) {
								a[k][j] = a[k + 1][j];
							}
							a[7][j] = 0;
						}
					}
				}
			}
		}
		if (sli == 0) {
			for (i = 7; i >= 1; i--, printf("\n")) {
				for (j = 1; j <= 7; j++) {
					if (a[i][j] == 0) {
						printf("#");
					} else {
						printf("%d", a[i][j]);
					}
				}
			}
			printf("\n");
		}
	}
	return 0;
}

