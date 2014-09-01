#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int n, a, b;

int main() {
	scanf("%d %d %d", &n, &a, &b);
	int ans = -100, ansx, ansy;
	for (int i = 1; i <= n; i++) {
		for (int x = i; x; x = (x - 1) & i) {
			int now = (a * x + b * i) ^ (a * i + b * x);
			if (now > ans) {
				ans = now;
				ansx = i, ansy = x;
			}
		}
	}

	printf("%d %d\n", ansx, ansy);
	return 0;
}
