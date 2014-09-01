#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	printf("%d\n", n <= k ? 2 : (n * 2 + k - 1) / k);
	return 0;
}

