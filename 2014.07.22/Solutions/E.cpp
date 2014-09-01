#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10005;

int id[30][100];
int hh[N], mm[N], n, m, k, tot;
int hashNow[N], hashCnt;
int a[N], b[N], c[N];

int get(int a, int b, int c) {
	if (a > b) {
		swap(a, b);
	}

	if (b - a == c) {
		return b;
	}

	if (b - a > c) {
		return tot + 1;
	}
	
	c -= (b - a);
	if ((c & 1) == 0) {
		int now = b + (c >> 1);
		if (now > tot) {
			now -= tot;
		}

		return now;
	} else {
		return tot + 1;
	}

	return tot + 1;
}

void work() {
	for (int i = 1; i <= n; i++) {
		int h, m;
		scanf("%d:%d", &h, &m);
		a[i] = id[h][m];
	}

	for (int i = 1; i <= m; i++) {
		int h, m;
		scanf("%d:%d", &h, &m);
		b[i] = id[h][m];
	}

	scanf("%d", &k);
	for (int i = 1; i <= k; i++) {
		int h, m;
		scanf("%d:%d", &h, &m);
		c[i] = id[h][m];
	}

	int s = 0, ans = 0;
	for (int i = 2; i <= tot; i++) {
		hashCnt++;
		for (int j = 1; j <= n; j++) {
			for (int l = 1; l <= m; l++) {
				hashNow[get(a[j], b[l], i - 1)] = hashCnt;
				//if (i == 427 && j == 1 && l == 1) {
				//	printf("%d\n", get(a[j], b[l], i - 1));
				//}
			}
		}

		int flag = 1;
		for (int j = 1; j <= k; j++) {
			if (hashNow[c[j]] != hashCnt) {
				flag = 0;
				break;
			}
		}

		if (flag == 1) {
			s++;
			ans = i;
		}
	}

	if (s == 0) {
		printf("il bugiardo passeggeri!\n");
	} else if (s == 1) {
		printf("%02d:%02d\n", hh[ans], mm[ans]);
	} else {
		printf("%d scelte\n", s);
	}
}

int main() {
	tot = 0;
	for (int i = 0; i <= 23; i++) {
		for (int j = 0; j <= 59; j++) {
			id[i][j] = ++tot;
			hh[tot] = i;
			mm[tot] = j;
		}
	}

	while (scanf("%d %d", &n,&m) == 2 && (n + m)) {
		work();
	}

	return 0;
}
