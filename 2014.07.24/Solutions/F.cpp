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

const int N = 3000000 + 10;

int n;
int qh, qt;
int que[N];

int main() {
	cin >> n;
	int x;
	qh = qt = 1500000;
	for( ; n --; ) {
		scanf("%d", &x);
		if (x > 0) {
			que[qt ++] = x;
			continue;
		} else if (x == -1) {
			printf("%d\n", que[qt - 1]);
			qt --;
			continue;
		} else {
			int tmp = qh;
			for(int i = qt - 1; i >= tmp && qt - qh < 1000010; -- i) {
				-- qh;
				que[qh] = que[i];
			}
		}
	}
}
