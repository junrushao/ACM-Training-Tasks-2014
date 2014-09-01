#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int n = 5;

char str[16][16];
int ok[1005][5];
int test;
int dx[4] = {1, 0, 1, 1};
int dy[4] = {0, 1, 1, -1};

void work() {
	for (int i = 1; i <= n; i++) {
		scanf("%s", str[i] + 1);
	}

	for (int d = 0; d < 4; d++) {
		ok['A'][d] = ok['B'][d] = 0;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int d = 0; d < 4; d++) {
				int x1 = i + dx[d], y1 = j + dy[d];
				int x2 = x1 + dx[d], y2 = y1 + dy[d];

				if (x1 >= 1 && x1 <= 5 && x2 >= 1 && x2 <= 5 && y1 >= 1 && y1 <= 5 && y2 >= 1 && y2 <= 5
					&& str[i][j] == str[x1][y1] && str[i][j] == str[x2][y2]) {
					ok[str[i][j]][d] = 1;
				}
			}
		}
	}

	int s1 = 0, s2 = 0;
	for (int d = 0; d < 4; d++) {
		s1 += ok['A'][d];
		s2 += ok['B'][d];
	}

	if (s1 > 0 && s2 == 0) {
		printf("A wins\n");
	} else if (s2 > 0 && s1 == 0) {
		printf("B wins\n");
	} else {
		printf("draw\n");
	}
}

int main() {
	scanf("%d", &test);
	while (test--) {
		work();
	}

	return 0;
}
