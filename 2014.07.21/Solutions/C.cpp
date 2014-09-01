#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <bitset>
#include <string>
#define PQ priority_queue
#define OO 2147483647
#define Max(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((b) & FASTBUFFER | (a) & ~FASTBUFFER))
#define Min(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((a) & FASTBUFFER | (b) & ~FASTBUFFER))
#define Swap(a, b) (a ^= b, b ^= a, a ^= b)

int FASTBUFFER;

using namespace std;

const int mo = 1000000009;
const int x = 383008016;
const int y = 500000005;

int z1 = (long long)y * (1 + x) % mo;
int z2 = (long long)y * (1 - x) % mo + mo;

long long n;
int k;

int sumi(int a, long long b) {
	int ret = 1, c = a;
	while (b) {
		if (b & 1LL) {
			ret = (long long)ret * c % mo;
		}
		
		b >>= 1;
		c = (long long)c * c % mo;
	}
	
	return ret;
}

void work() {
	cin >> n >> k;
	int C = 1;
	int ans = 0;
	for (int i = 0; i <= k; i++) {
		if (i) {
			C = (long long)C * (k - i + 1) % mo * sumi(i, mo - 2) % mo;
			//printf("C = %d\n", C);
		}
		
		int q = (long long)sumi(z1, i) * sumi(z2, k - i) % mo;
		int now = (long long)(sumi(q, n + 1) - q) * sumi(q - 1, mo - 2) % mo * C % mo;
		if (q == 1) {
			now = (long long)n % mo * C % mo;
		}
		
		if ((k - i) & 1) {
			(ans -= now) %= mo;
		} else {
			(ans += now) %= mo;
		}
	}
	
	ans = (long long)ans * sumi(sumi(x, k), mo - 2) % mo;
	while (ans < 0) {
		ans += mo;
	}
	
	printf("%d\n", ans);
}

int test;

int main() {
	//printf("%d\n", (long long)(sumi(z1, 4) - sumi(z2, 4) + mo) * sumi(x, mo - 2) % mo);
	scanf("%d", &test);
	while (test--) {
		work();
	}
	
	return 0;
}
