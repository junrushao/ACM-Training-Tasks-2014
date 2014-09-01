#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
char s[105][35];
int b[30];
int main() {
	int n, i;
	scanf("%d", &n);
	fgets(s[0], 35, stdin);
	for (i = 1; i <= n; i++) {
		fgets(s[i], 35, stdin);
		b[s[i][0] - 65] = 1;
	}
	for (i = 0; i < 26; i++) {
		if (!b[i]) {
			break;
		}
	}
	printf("%d\n", i);
	return 0;
}

