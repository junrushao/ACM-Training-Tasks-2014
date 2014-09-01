#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 1000005;

int beg[N], now[N],nex[N], tot, d[N];
int ans[N];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m, x, y;
		scanf("%d%d", &n, &m);
		tot = 0;
		for (int i = 1; i <= n; i++) {
			beg[i] = 0;
		}
		priority_queue<pair<int, int> > a;
		for (int i = 1; i <= m; i++) {
			scanf("%d", &d[i]);
			x = d[i];
			if (beg[x] == 0) {
				beg[x] = i;
				now[x] = i;
				nex[i] = 0;
			} else {
				nex[now[x]] = i;
				now[x] = i;
				nex[now[x]] = 0;
			}
		}
		for (int i = 1; i <= n; i++) {
			if (beg[i]) {
				y = beg[i];
				a.push(make_pair(-y, i));
				beg[i] = nex[y];
			}
		}
		int flag = 1, l = 0;
		for (int i = 1; i <= m; i++) {
			x = d[i];
			if (x) {
				if (!a.empty() && a.top().second == x) {
					printf("NO\n");
					flag = 0;
					break;
				} else {
					if (beg[x] != 0) {
						y = beg[x];
						beg[x] = nex[y];
						a.push(make_pair(-y , x));
					}
				}
			} else {
				if (a.empty()) {
					ans[++l] = 0;
				} else {
					x = a.top().second;
					ans[++l] = x;
					a.pop();
				}
			}
		}
		if (flag == 1) {
			printf("YES\n");
			for (int i = 1; i <= l; i++) {
				printf("%d%c", ans[i], i == l ? '\n' : ' ');
			}
		}
	}
	return 0;
}

