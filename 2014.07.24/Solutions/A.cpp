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

const int N = 100000;
int x[N];

int main() {
	int n;
	cin >> n;
	scanf("%d%d%d", x, x + 1, x + 2);
	int ret = x[0] + x[1] + x[2];
	int tmp = 2;
	for(int i = 3; i < n; ++ i) {
		scanf("%d", x + i);
		if (x[i] + x[i - 1] + x[i - 2] > ret) {
			ret  = x[i] + x[i - 1] + x[i - 2];
			tmp = i;
		}
	}
	cout << ret << ' ' << tmp << endl;
}
