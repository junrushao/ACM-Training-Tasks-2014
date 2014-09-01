#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char s[6][6], c, out[6];
int a[7778], b[7778];

int calc(int i, int j, int k, int l, int m) {
	return
	(s[i][0] - 65) * 26 * 26 * 26 * 26 +
	(s[j][1] - 65) * 26 * 26 * 26 +
	(s[k][2] - 65) * 26 * 26 +
	(s[l][3] - 65) * 26 +
	(s[m][4] - 65);
}

int read(int a[]) {
	int i, j, k, l, m, tot;
	for (i = 0; i < 6; i++) {
		scanf("%s%c", s[i], &c);
	}
	tot = 0;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 6; j++) {
			for (k = 0; k < 6; k++) {
				for (l = 0; l < 6; l++) {
					for (m = 0; m < 6; m++) {
						a[tot++] = calc(i, j, k, l, m);
					}
				}
			}
		}
	}
	sort(a, a+tot);
	tot = unique(a, a+tot) - a;
	return tot;
}
int main() {
	int i, j, k, T, TT, ans, tot, la, lb, mem;
	scanf("%d%c", &TT, &c);
	for (T = 1; T <= TT; T++) {
		scanf("%d", &ans);
		la = read(a), lb = read(b);
		j = k = 0;
		mem = -1;
		while (j < la && k < lb) {
			if (a[j] < b[k]) {
				j++;
			} else if (a[j] > b[k]) {
				k++;
			} else {
				ans--;
				if (ans == 0) {
					mem = a[j];
					break;
				}
				j++,k++;
			}
		}
		if (mem == -1) {
			printf("NO\n");
			continue;
		}
		for (i = 4; i >= 0; i--) {
			out[i] = mem % 26 + 65;
			mem /= 26;
		}
		out[5] = '\0';
		printf("%s\n", out);
	}
	return 0;
}
