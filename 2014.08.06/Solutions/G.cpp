#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n, k, len, b[30];

#define pow POW

int pow[30];

int main() {
	pow[0] = 1;
	for (int i = 1; pow[i - 1] <= 1000000000; ++i) {
		pow[i] = pow[i - 1] * 3;
	}
	while (scanf("%d%d", &n, &k) == 2) {
		len = 0;
		int nn = n;
		while (n) {
			b[len++] = n % 3;
			n /= 3;
		}
		int ans = 0;
		for (int i = len - 1; i >= -1; --i) {
			int a[2] = {0, 0}, c[2] = {0, 1};
			//0 smaller 1 equal
			for (int j = len - 1; j > i; --j) {
				int aa[2] = {0, 0}, cc[2] = {0, 0};	
				for (int d = 0; d < 2; ++d) {
					(aa[0] += a[0] * 3 + c[0] * d) %= k;
					cc[0] += c[0];
					if (d < b[j]) {
						(aa[0] += a[1] * 3 + c[1] * d) %= k;
						cc[0] += c[1];
					} else if (d == b[j]) {
						(aa[1] += a[1] * 3 + c[1] * d) %= k;
						cc[1] += c[1];				
					}
				}
				a[0] = aa[0], a[1] = aa[1], c[0] = cc[0], c[1] = cc[1];
			}	
			if (i == -1) {
				(ans += a[0] + a[1]) %= k;
			} else {
				(ans += a[0] * (pow[i] % k) % k) %= k;
				if (b[i] == 2) {
					(ans += a[1] * ((nn % pow[i] + 1) % k) % k) %= k;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
