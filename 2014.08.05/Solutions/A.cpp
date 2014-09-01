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
using namespace std;
map<string, int> mp;
string st, sL[111], sR[111], sS[111];
double dp[502][502][102], a[511][333];
string color[333];
int rules[111][3];
int nC, nC1;
int hsh(const string & st) {
	if(mp.count(st)) {
		return mp[st];
	}else {
		color[nC + 1] = st;
		return mp[st] = ++nC;	
	}
}
double getdp(int i, int j, int c) {
	if(i == j)
		return a[i][c];
	else {
		if(c > nC1)
			return 0;
		else
			return dp[i][j][c];
	}
}
int main() {
	int nR;
	ios::sync_with_stdio(false);
	for(int qq = 1; cin >> nR; qq++) {
		if(qq > 1)
			printf("\n");
		mp.clear();
		nC = 0;
		for(int i = 1; i <= nR; i++) {
			cin >> sL[i] >> sR[i] >> sS[i];
			rules[i][2] = hsh(sS[i]);
		}
		nC1 = nC;
		for(int i = 1; i <= nR; i++) {
			rules[i][0] = hsh(sL[i]);
			rules[i][1] = hsh(sR[i]);
		}
		int tst;
		cin >> tst;
		for(int qq = 1; qq <= tst; qq++) {
			int n;
			cin >> n;
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= 300; j++)
					a[i][j] = 0;
			for(int i = 1; i <= n; i++) {
				for(;;) {
					cin >> st;
					if(st != string("END")) {
						cin >> a[i][hsh(st)]; 
					}else break;
				}
			}
			for(int len = 2; len <= n; len++) {
				for(int i = 1; i + len - 1 <= n; i++) {
					for(int s = 1; s <= nC1; s++)
						dp[i][i + len - 1][s] = 0;
					for(int s = 1; s <= nR; s++) {
						for(int k = i; k < i + len - 1; k++) {
							dp[i][i + len - 1][rules[s][2]] = max(dp[i][i + len - 1][rules[s][2]], getdp(i, k, rules[s][0]) * getdp(k + 1, i + len - 1, rules[s][1]));
							dp[i][i + len - 1][rules[s][2]] = max(dp[i][i + len - 1][rules[s][2]], getdp(i, k, rules[s][1]) * getdp(k + 1, i + len - 1, rules[s][0]));
						}
					}	
				}
			}
			double mx = -1;
			double tmp;
			string mxc;
			for(int i = 1; i <= nC; i++) if(getdp(1, n, i) != 0) {
				if((tmp = getdp(1, n, i)) > mx) {
					mx = tmp;
					mxc = color[i];
				}
			}
			if(mx == -1) printf("GAMEOVER\n");
			else printf("%s\n", mxc.c_str());
		}
	}
	return 0;
}
