#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

const int N = 20;
const int INF = 1111111;

struct Rect {
	int x1, y1, x2, y2;
	Rect(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};

vector<Rect> rect;

int n, m;
int f[1 << N];

int main() {
	while(scanf("%d %d", &n, &m) == 2 && (n || m)) {
		rect.clear();
		for(int i = 0; i < n; i++) {
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			rect.push_back(Rect(x1, y1, x2, y2));
		}
		for(int mask = 0; mask < (1 << n); mask++) {
			int sign = -1;
			int x1 = -INF, y1 = -INF, x2 = INF, y2 = INF;
			for(int j = 0; j < n; j++) {
				if (mask >> j & 1) {
					sign *= -1;
					x1 = max(rect[j].x1, x1);
					y1 = max(rect[j].y1, y1);
					x2 = min(rect[j].x2, x2);
					y2 = min(rect[j].y2, y2);
				}
			}
			f[mask] = sign * max(0, (y2 - y1)) * max(0, (x2 - x1));
		}
		
		f[0] = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < (1 << n); j++) {
				if (j & (1 << i)) {
					f[j] += f[j ^ (1 << i)];
				}
			}
		static int testCount = 0;
		printf("Case %d:\n", ++testCount);
		for(int i = 0; i < m; i++) {
			int number, mask = 0;
			scanf("%d", &number);
			for(int j = 0; j < number; j++) {
				int x;
				scanf("%d", &x);
				mask |= (1 << (x - 1));
			}
			printf("Query %d: %d\n", i + 1, f[mask]);
		}
		puts("");
	}
	return 0;
}
