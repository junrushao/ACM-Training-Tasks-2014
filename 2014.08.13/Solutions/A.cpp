#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <ctime>
#include <cmath>
#include <set>
#include <map>

#define foreach(it,e) for (__typeof(e.begin ()) it = e.begin(); it != e.end(); it++)

#define sqr(x) ((x) * (x))
#define abs(x) (((x) > 0) ? (x) : (-(x))) 
#define lowbit(x) ((x) & (-(x)))

using namespace std;

typedef long long i64;
typedef unsigned long long u64;
typedef double dbl;

int year, month, day;

inline void solve() {
	scanf("%d%d%d", &year, &month, &day);
	day--;
	day += ((year - 1) / 3) * 200 + (year - 1 - ((year - 1) / 3)) * 195;
	if (year % 3 == 0) {
		day += 20 * (month - 1);
	} else {
		day += 19 * ((month - 1) / 2) + 20 * (month - 1 - (month - 1) / 2);
	}
	printf("%d\n", 196470 - day);
}

int main () {
	int test; scanf("%d", &test);
	for (int i = 1; i <= test; ++i) {
		solve();
	}
	return 0;
}
