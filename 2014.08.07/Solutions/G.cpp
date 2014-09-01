#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100005;
const int M = 10000005;
bool b[M];
char s[N];
int main() {
	scanf("%s", s + 1);
	int l = strlen(s + 1), r;
	for (int i = 1; i <= l; i++) {
		r = min(l, i + 6);
		int x = 0;
		for (int j = i; j <= r; j++) {
			x = x * 10 + s[j] - 48;
			b[x] = 1;
		}
	}
	int i;
	for (i = 1; i < M; i++) {
		if (b[i] == 0) {
			break;
		}
	}
	printf("%d\n", i);
	return 0;
}

