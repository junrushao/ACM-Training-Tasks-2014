#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cassert>
#include <bitset>
#include <numeric>

using namespace std;

int main() {
	int n, D;
	while (scanf("%d %d", &n, &D) == 2 && (n != 0 || D != 0)) {
		static int task_index = 1;
		double ret = D;
		for (int _ = 0; _ < n; ++_) {
			int p, L, v;
			scanf("%d %d %d", &p, &L, &v);
			ret += 2.0 * L / v - L;
		}
		printf("Case %d: %.3f\n", task_index, ret);
		puts("");
		++task_index;
	}
	return 0;
}

