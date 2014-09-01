#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 50005;
const int M = 100005;
int b[M];
int p[N];
int use[N];
int x[N], y[N];
int main() {
	int l, n;
	scanf("%d%d", &l, &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &x[i], &y[i]);
	}
	int f = 0;
	if (x[1] > y[1]) {
		f = 1;
		for (int i = 1; i <= n; i++) {
			if (x[i] <= y[i]) {
				printf("0\n");
				return 0;
			}
			swap(x[i], y[i]);
		}
	}
	if (x[1] == y[1]) {
		for (int i = 1; i <= n; i++) {
			if (x[i] != y[i]) {
				printf("0\n");
				return 0;
			}
			p[i] = i;
			if (x[i] != x[1]) {
				x[i] = l - x[i], y[i] = l - y[i];
				p[i] = -i;
			}
			if (x[i] != x[1]) {
				printf("0\n");
				return 0;
			}
		}
		for (int i = 1; i <= n; i++) {
			printf("%d%c", p[i], i == n ? '\n' : ' ');
		}
		return 0;
	}
	int dd = y[1] - x[1];
	for (int i = 1; i <= n; i++) {
		if (b[x[i]] == 0) {
			b[x[i]] = i;
			b[l - y[i]] = -i;
		} else if (b[x[i]] == -b[l - y[i]]) {
			b[x[i]] = i;
		} else {
			printf("0\n");
			return 0;
		}
		if (y[i] - x[i] != dd) {
			printf("0\n");
			return 0;
		}
	}
	int now;
	for (now = 0; now <= 100000; now++) {
		if (b[now] != 0) {
			break;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (b[now] == 0 || use[abs(b[now])]) {
			printf("0\n");
			return 0;
		}
		p[i] = b[now];
		use[abs(b[now])] = 1;
		now += dd;
	}
	if (f == 0) {
		for (int i = 1; i <= n; i++) {
			printf("%d%c", p[i], i == n ? '\n' : ' ');
		}
	} else {
		for (int i = n; i >= 1; i--) {
			printf("%d%c", p[i], i == 1 ? '\n' : ' ');
		}
	}
	return 0;
}
