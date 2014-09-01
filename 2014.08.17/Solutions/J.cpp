#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <bitset>
#include <map>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

int n;
char g[1600][1600];

bitset<1500> I[1500], O[1500];

int main() {
	scanf("%d", &n);
	gets(g[0]);
	REP(i, n) gets(g[i]);
	REP(i, n) REP(j, n) 
	if (g[i][j] == '+') {
		I[j][i] = 1;
		O[i][j] = 1;
	}
	long long ans = 0;
	REP(i, n) REP(j, n) 
	if (g[i][j] == '+') {
		ans += (I[i] & O[j]).count();
	}
	cout << ans / 3 << endl;

}
