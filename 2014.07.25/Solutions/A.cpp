#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


const int N = 1000005;
bool f[N];

int main() {
	f[1] = true;
	for (int i = 2; i < N; ++i) {
		if (!f[i]) {
			for (long long j = (long long)i * i; j < N; j += i) {
				f[j] = true;
			}
		}
	}
	int a, d, n;
	while (scanf("%d%d%d", &a, &d, &n) && (a || d || n)) {
		while (n) {
			n -= !f[a];
			if (n == 0) {
				break;
			}
			a += d;
		}
		printf("%d\n", a);
	}
	return 0;
}
