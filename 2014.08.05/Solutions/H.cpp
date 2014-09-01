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
#include <queue>
#include <set>
#include <map>
using namespace std;
char bd[111111], s[111111], t[111111];
int cl, pw[111111], nxt[111111][3], len, ans, pre[111111][3];
int modulo(21092013);
int main() {
	int tst;
	scanf("%d", &tst);
	for(int qq = 1; qq <= tst; qq++) {
		scanf("%s%s", s, t);
		len = strlen(s);
		cl = 0;
		for(int i = 0; i < len; i++) {
			if(s[i] == 'U')
				cl = max(0, cl - 1);
			else
				bd[++cl] = s[i];
		}
		len = strlen(t);
		pw[len] = 1;
		nxt[len][0] = nxt[len][1] = nxt[len][2] = -1;
		for(int i = len - 1; i >= 0; i--) {
			nxt[i][0] = nxt[i + 1][0];
			nxt[i][1] = nxt[i + 1][1];
			nxt[i][2] = nxt[i + 1][2];
			if(t[i] == 'U') {
				nxt[i][0] = i;
			}else {
				if(t[i] == 'L') {
					nxt[i][1] = i;
				}else {
					nxt[i][2] = i;
				}
			}
			pw[i] = 1;
			if(nxt[i][1] != -1)
				pw[i] = (pw[i] + pw[nxt[i][1] + 1]) % modulo;
			if(nxt[i][2] != -1)
				pw[i] = (pw[i] + pw[nxt[i][2] + 1]) % modulo;
		}
		
		ans = pw[0];
		for(int i = 0; i < len and cl; i++) if(t[i] == 'U') {
			ans = (ans + 1) % modulo;
			int x(nxt[i][bd[cl] == 'L'?2:1]);
			if(x != -1) {
				ans = (ans + pw[x + 1]) % modulo;
			}
			cl--;
		}
		printf("Case %d: %d\n", qq, ans);
	}
}
