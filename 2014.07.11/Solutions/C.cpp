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

const int N = 1500 + 10;
const int c[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

int n, m;
int value[N];
double prob[N];

int getValue(char *ch)
{
	if (ch[0] == 'A') return 11;
	if (ch[0] == '1' && ch[1] == '0') return 10;
	if (ch[0] >= '2' && ch[0] <= '9') return ch[0] - '0';
	return 10;
}

void solve() {
	memset(value, -1, sizeof value);
	int cur = m;
	int len;
	char buf[3];
	for(int i = 0; i < n; ++ i) {
		scanf("%s", buf);
		value[cur] = getValue(buf);
		len = cur;
		cur += value[cur];
	}
	for(int i = 1; i <= len; ++ i) {
		if (i <= 10) 
			prob[i] = 0.1;
		else prob[i] = 0;
	}
	for(int i = 1; i <= len; ++ i) {
		if (value[i] >= 0) {
			prob[i + value[i]] += prob[i];
			continue;
		}
		prob[i] /= 13;
		for(int j = 0; j < 13; ++ j) {
			prob[i + c[j]] += prob[i];
		}
	}
	printf("%.12f\n", prob[len]);
}

int main() {
	for( ; cin >> n >> m; ) {
		solve();
	}
	return 0;
}