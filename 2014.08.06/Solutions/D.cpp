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

long long a, b;

long long work(long long n) {
	long long temp = n;
	int a[105] = {0};
	if (n == 0LL) {
		return 0LL;
	}
	
	while (n) {
		a[++a[0]] = (n & 1LL);
		n >>= 1;
	}
	
	n = temp;
	long long ret = 0;
	for (int i = a[0]; i >= 1; i--) {
		if (a[i] == 0) {
			continue;
		} else {
			if (i > 1) {
				ret += (1LL << i - 2) * (i - 1);
			}
			
			n -= (1LL << i - 1);
			ret += (n + 1);
		}
	}
	
	return ret;
}

int main() {
	while (cin >> a >> b) {
		cout << work(b) - work(a - 1LL) << endl;
	}
	
	return 0;
}
