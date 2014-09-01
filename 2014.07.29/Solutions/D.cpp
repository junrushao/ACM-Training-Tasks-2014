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

int n, m, k, rela[200001], x, y, X, Y, mnx[200001], mny[200001], mxx[200001], mxy[200001], cnt, up, dn, le, ri;

int getr(int x) {
	int p = x, p1, p2;
	while(rela[p] != p)
		p = rela[p];
	p1 = p; p = x;
	while(rela[p] != p) {
		p2 = rela[p];
		rela[p] = p1;
		p = p2;
	}
	return p1;
}
int main() {
	scanf("%d%d%d", &k, &n, &m);
	for(int i = 1; i <= n + m; i++)
		rela[i] = i, mnx[i] = 1e9, mny[i] = 1e9, mxx[i] = -1e9, mxy[i] = -1e9;
	for(int i = 1; i <= k; i++) {
		scanf("%d%d", &x, &y);
		X = getr(x);
		Y = getr(y + n);
		rela[X] = Y;
		mnx[Y] = min(mnx[Y], min(mnx[X], x));
		mxx[Y] = max(mxx[Y], max(mxx[X], x));
		mny[Y] = min(mny[Y], min(mny[X], y));
		mxy[Y] = max(mxy[Y], max(mxy[X], y));
	}
	cnt = up = dn = le = ri = 0;
	for(int i = 1; i <= n + m; i++) if(rela[i] == i and mnx[i] != 1e9) {
		//printf("%d\n", i);
		if(mnx[i] == 1)
			up++;
		if(mxx[i] == n)
			dn++;
		if(mny[i] == 1)
			le++;
		if(mxy[i] == m)
			ri++;
		cnt++;
	}
	//printf("%d %d %d %d %d\n", le, ri, up, dn, cnt);
	if (cnt == 1) printf("%d\n", k - 1);
	else printf("%d\n", k + cnt - 1 - max(max(up, dn), max(le, ri)));
}
