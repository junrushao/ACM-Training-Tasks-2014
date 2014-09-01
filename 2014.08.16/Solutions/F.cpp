#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100005;
const int INF = 1000000000;
char s[N];
struct node {
	int b;
	int a[2][2];
} fu[N];

int main() {
	int i, l, n = 0;
	scanf("%s", s + 1);
	l = strlen(s + 1);
	for (int i = 1; i <= l; i++) {
		if (s[i] == 'S') {
			fu[++n].b = 1; 
		} else if (s[i] == 'P') {
			fu[++n].b = 2;
		} else {
			fu[++n].b = 3;
			fu[n].a[0][0] = 0, fu[n].a[0][1] = 1, fu[n].a[1][0] = 1, fu[n].a[1][1] = -INF;
			while (n >= 3 && fu[n].b == 3 && fu[n - 1].b == 3) {
				if (fu[n - 2].b == 2) {
					fu[n - 2].b = 3;
					for (int i = 0; i <= 1; i++) {
						for (int j = 0; j <= 1; j++) {
							fu[n - 2].a[i][j] = -INF;
						}
					}
					for (int i = 0; i <= 1; i++) {
						for (int j = 0; j <= 1; j++) {
							fu[n - 2].a[i][j] = max(fu[n - 2].a[i][j], fu[n - 1].a[i][j] + fu[n].a[i][j] - i - j);
						}
					}
					n -= 2;
				} else if (fu[n - 2].b == 1) {
					fu[n - 2].b = 3;
					for (int i = 0; i <= 1; i++) {
						for (int j = 0; j <= 1; j++) {
							fu[n - 2].a[i][j] = -INF;
						}
					}
					for (int i = 0; i <= 1; i++) {
						for (int j = 0; j <= 1; j++) {
							for (int k = 0; k <= 1; k++) {
								fu[n - 2].a[i][k] = max(fu[n - 2].a[i][k], fu[n - 1].a[i][j] + fu[n].a[j][k] - j);
							}
						}
					}
					n -= 2;
				}
			}
		}
	}
	int ans = -INF;
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 1; j++) {
			ans = max(ans, fu[1].a[i][j]);
		}
	}
	printf("%d\n", ans);
	return 0;
}

