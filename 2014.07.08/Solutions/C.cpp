#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

long long n;

int main() {
	int test = 0;
	while(scanf("%I64d", &n) == 1) {
		long long ans = 0;
		for(long long a = 1; a * a * a <= n; a++) {
			ans++;
			for(long long b = a + 1; a * b * b <= n; b++) {
				long long upper = n / (a * b);
				if (b < upper) {
					ans += 6 * (upper - b);
				}
			}
		}
		for(long long a = 1; a * a <= n; a++) {
			long long limit = n / a / a;
			if (limit >= a && limit) {
				limit--;
			}
			ans += 3 * limit;
		} 
		printf("Case %d: %I64d\n", ++test, ans);
	}
	return 0;
}