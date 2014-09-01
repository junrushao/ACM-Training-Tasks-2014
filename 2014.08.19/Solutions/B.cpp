#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 21;

int n;
int net[N];

int sum[1 << N], marker[1 << N], ans[1 << N];

int getans(int st) {
	if (ans[st] != -1) {
		return ans[st];
	}
	ans[st] = 0;
	for (int sub = st; sub; sub = (sub - 1) & st) {
		if (marker[sub] == 1 && sum[sub] == 0) {
			ans[st] = max(ans[st], 1 + getans(st ^ sub));
		}
	}
	return ans[st];
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int a;
		scanf("%d", &a);
		net[i] += a;
	}
	for (int i = 0; i < n; ++i) {
		int b;
		scanf("%d", &b);
		net[i] -= b;
	}
	{
		int newn = 0, sum = 0;
		for (int i = 0; i < n; ++i) {
			sum += net[i];
			if (net[i] != 0) {
				net[newn++] = net[i];	
			}
		}
		n = newn;
		if (sum != 0) {
			printf("-1\n");
			return 0;
		}
	}
	for (int st = 1; st < 1 << n; ++st) {
		for (int j = 0; j < n; ++j) {
			if (st >> j & 1) {
				sum[st] += net[j];
			}
		}
		if (sum[st] == 0) {
			marker[st] = 1;
		} else {
			marker[st] = 0;
		}
		for (int j = 0; j < n; ++j) {
			if (st >> j & 1) {
				marker[st] += marker[st ^ (1 << j)];
			}
		}
		marker[st] = min(marker[st], 2);
	}
	memset(ans, -1, sizeof(ans));
	printf("%d\n", n - getans((1 << n) - 1));
	return 0;
}

