#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int LOG = 21;

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		printf("%d\n", LOG);
		for (int i = 0; i < LOG - 1; ++i) {
			for (int j = 0; j < LOG; ++j) {
				putchar('0' + ((i + 1) >= j));
			}
			printf("\n");
		}
		putchar('0');
		for (int i = 1; i < LOG; ++i) {
			putchar('0' + (n >> i - 1 & 1));
		}
		printf("\n");
	}
	return 0;
}
