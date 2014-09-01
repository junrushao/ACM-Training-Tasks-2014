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

long long a, b;
long long p10[20];
long long lasta[20], lastb[20];
int bita[20], bitb[20];
int f[10][10][20];
int dp[10][20][20];
int ret[20];

int calcSame(int st, int b, long long t)
{
	int ret = st;
	for(int i = 0; i < 20; ++ i) {
		int cur = t % 10;
		for(int j = 0; j < cur; ++ j) {
			ret = f[ret][b][i];
		}
		t /= 10;
	}
	return ret;
}

int calcDiff(int st, long long k, long long t)
{
	int ret = st;
	for(int i = 0; i < 20; ++ i) {
		int cur = t % 10;
		for(int j = 0; j < cur; ++ j) {
			ret = dp[ret][k][i];
		}
		t /= 10;
	}
	return ret;
}

int calc(int k)
{
	int ret;
	int st = bita[k], ed = bitb[k];
	if (lasta[k] == lastb[k]) {
		return calcSame(st, st, b - a);
	}
	if (lasta[k + 1] == lastb[k + 1]) {
		ret = calcSame(st, st, (lasta[k] + 1) * p10[k] - a - 1);
		for(int i = st + 1; i < ed; ++ i) {
			ret = f[ret][i][k];
		}
		ret = calcSame(ret, ed, b - lastb[k] * p10[k] + 1);
		return ret;
	}
	ret = calcSame(st, st, (lasta[k] + 1) * p10[k] - a - 1);
	for(int i = st + 1; i < 10; ++ i) {
		ret = f[ret][i][k];
	}
	ret = calcDiff(ret, k, lastb[k + 1] - lasta[k + 1] - 1);
	for(int i = 0; i < ed; ++ i) {
		ret = f[ret][i][k];
	}
	ret = calcSame(ret, ed, b - lastb[k] * p10[k] + 1);
	return ret;
}

void solve() {
	for(int i = 0; i < 10; ++ i)
		for(int j = 0; j < 10; ++ j) 
			cin >> f[i][j][0];
	cin >> a >> b;

	if (a == b) {
		cout << a << endl;
		return;
	}

	p10[0] = 1;
	for(int i = 1; i < 20; ++ i) { //overflow is ok
		p10[i] = p10[i - 1] * 10;
	}

	long long cura = a, curb = b;
	for(int i = 0; i < 20; ++ i) {
		lasta[i] = cura;
		lastb[i] = curb;
		bita[i] = cura % 10;
		bitb[i] = curb % 10;
		cura /= 10;
		curb /= 10;
	}

	for(int k = 1; k < 20; ++ k) {
		for(int a = 0; a < 10; ++ a)
			for(int b = 0; b < 10; ++ b) {
				int cur = a;
				for(int i = 0; i < 10; ++ i) {
					cur = f[cur][b][k - 1];
				}
				f[a][b][k] = cur;
			}
	}

	for(int a = 0; a < 10; ++ a)
		for(int l = 0; l < 20; ++ l) {
			int cur = a;
			for(int i = 0; i < 10; ++ i) {
				cur = f[cur][i][l];
			}
			dp[a][l][0] = cur;
		}

	for(int k = 1; k < 20; ++ k) {
		for(int a = 0; a < 10; ++ a) {
			for(int l = 0; l < 20; ++ l) {
				int cur = a;
				for(int i = 0; i < 10; ++ i) {
					cur = dp[cur][l][k - 1];
				}
				dp[a][l][k] = cur;
			}
		}
	}

	
	for(int i = 0; i < 20; ++ i) {
		ret[i] = calc(i);
	}
	int flag = false;
	for(int i = 19; i >= 0; -- i) {
		if (ret[i]) flag = true;
		if (flag) printf("%d", ret[i]);
	}
	if (! flag) cout << 0;
	cout << endl;
}

int main() {
	int test;
	cin >> test;
	for( ; test --; ) {
		solve();
	}
	return 0;
}

