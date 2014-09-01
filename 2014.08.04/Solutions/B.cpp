#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
struct can{
	int v, n;
	char s[105];
} a[15];
char s[25];
bool cmp(can a, can b) {
	if (a.v != b.v) {
		return a.v > b.v;
	}
	return a.n < b.n;
}

double fix(int a, int b) {
	int c = a * 100000 / b;
	c += 5;
	return c / 10;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", a[i].s);
		a[i].n = i;
		a[i].v = 0;
	}
	a[n + 1].v = 0;
	for (int i = 1; i <= m; i++) {
		scanf("%s", s + 1);
		int k = 0;
		for (int j = 1; j <= n; j++) {
			if (s[j] == 'X') {
				if (k == 0) {
					k = j;
				} else {
					k = n + 1;
				}
			}
		}
		if (k == 0) {
			k = n + 1;
		}
		a[k].v++;
	}
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		printf("%s %.2f%%\n", a[i].s, fix(a[i].v, m) / 100);
	}
	printf("Invalid %.2f%%\n", fix(a[n + 1].v, m) / 100); 
	return 0;
}
