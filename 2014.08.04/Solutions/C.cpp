#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define mp make_pair

using namespace std;

const int base = 277;
const int INF = 100000;
const int N = 2025;

long long h1[N][N], h2[N][N];
int ans1, ans2, ans3, ans4, ans = INF;
int len1, len2, tot;
char s1[N], s2[N];
pair <long long, int> a[N];

int main() {
	gets(s1 + 1);
	gets(s2 + 1);
	len1 = strlen(s1 + 1);
	len2 = strlen(s2 + 1);
	for (int i = 1; i <= len1; i++) {
		h1[i][i - 1] = 0;
		for (int j = i; j <= len1; j++) {
			h1[i][j] = h1[i][j - 1] * base + s1[j];
		}
	}

	for (int i = 1; i <= len2; i++) {
		h2[i][i - 1] = 0;
		for (int j = i; j <= len2; j++) {
			h2[i][j] = h2[i][j - 1] * base + s2[j];
		}
	}

	for (int len = 1; len <= len1; len++) {
		tot = 0;
		for (int i = 1; i + len - 1 <= len1; i++) {
			a[++tot] = mp(h1[i][i + len - 1], i); 
		}

		sort(a + 1, a + tot + 1);

		for (int i = 1; i <= tot; i++) {
			int j;
			for (j = i + 1; j <= tot && a[i].first == a[j].first; j++);
			j--;

			int last = -INF, s = 0;
			for (int k = i; k <= j; k++) {
				if (last + len - 1 < a[k].second) {
					s++;
					last = a[k].second;
				}
			}

			int newLen = len1 - s * len;
			if (len2 < newLen || (len2 - newLen) % s) {
				i = j;
				continue;
			}

			long long temp;
			int lenDown = (len2 - newLen) / s, pos = 0, flag = 1;
			last = -INF;
			for (int k = i; k <= j; k++) {
				if (last + len - 1 < a[k].second) {
					int lenNow = 0;
					long long fNow = 0;
					if (last == -INF) {
						lenNow = a[k].second - 1;
						fNow = h1[1][a[k].second - 1];
					} else {
						lenNow = a[k].second - (last + len);
						fNow = h1[last + len][a[k].second - 1];
					}
					
					if (fNow != h2[pos + 1][pos + lenNow]) {
						flag = 0;
						break;
					}

					if (pos == 0) {
						temp = h2[pos + lenNow + 1][pos + lenNow + lenDown];
					} else {
						if (temp != h2[pos + lenNow + 1][pos + lenNow + lenDown]) {
							flag = 0;
							break;
						}
					}

					pos += lenNow;
					pos += lenDown;
					last = a[k].second;
				}
			}

			if (flag && h1[last + len][len1] != h2[pos + 1][len2]) {
				flag = 0;
			}

			if (flag) {
				if (lenDown + len < ans) {
					ans = lenDown + len;
					ans1 = a[i].second, ans2 = ans1 + len - 1;
					ans3 = a[i].second, ans4 = ans3 + lenDown - 1;
				}
			}

			i = j;
		}
	}

	printf("s/");
	for (int i = ans1; i <= ans2; i++) {
		printf("%c", s1[i]);
	}

	printf("/");
	for (int i = ans3; i <= ans4; i++) {
		printf("%c", s2[i]);
	}
	printf("/g\n");
	return 0;
}
