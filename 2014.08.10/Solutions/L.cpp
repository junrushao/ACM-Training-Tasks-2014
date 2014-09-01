#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		printf("%d\n", (int)((1LL << n) - 1));
	}
	return 0;
}
