#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, k;

const int N = 30;
bool dir[N], vis[N];

inline int goLeft(int u) {
	return u ? u - 1 : n - 1;
}

inline int goRight(int u) {
	return u == n - 1 ? 0 : u + 1;
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		scanf("%d", &k);
		for (int i = 0; i < n; ++i) {
			vis[i] = false;
			char op[2];
			scanf("%s", op);
			dir[i] = op[0] == 'L';
		}
		int last = 0, cur = k - 1, cnt = n, rnd = 1;
		vis[cur] = true, --cnt;
		while (cnt) {
			int next = dir[cur] ? goLeft(last) : goRight(last);
			if (next == cur) {
				next = dir[cur] ? goLeft(cur) : goRight(cur);
			}
			dir[cur] ^= 1;
			last = cur, cur = next;
			if (!vis[cur]) {
				--cnt;
				vis[cur] = true;
			}
			++rnd;
		}
		printf("Classmate %d got the ball last after %d tosses.\n", cur + 1, rnd);
	}
	return 0;
}
