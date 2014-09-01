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

const int N = 200000 + 10;

int n, q, tot;
char s[N], t[N];
int p[N], hash[N], len[N];
int sa[N], rank[N], from[N];
vector<int> tag[N * 2];

int cmp(int *x, int a, int b, int d)
{
	return x[a] == x[b] && x[a + d] == x[b + d];
}

void doubling(char *a, int n, int m)
{
	static int sRank[N], tmpA[N], tmpB[N];
	int *x = tmpA, *y = tmpB;
	for(int i = 0; i < m; ++ i) sRank[i] = 0;
	for(int i = 0; i < n; ++ i) ++ sRank[x[i] = a[i]];
	for(int i = 1; i < m; ++ i) sRank[i] += sRank[i - 1];
	for(int i = n - 1; i >= 0; -- i) sa[-- sRank[x[i]]] = i;
	for(int d = 1, p = 0; p < n; m = p, d <<= 1) {
		p = 0; for(int i = n - d; i < n; ++ i) y[p ++] = i;
		for(int i = 0; i < n; ++ i)
			if (sa[i] >= d) y[p ++] = sa[i] - d;
		for(int i = 0; i < m; ++ i) sRank[i] = 0;
		for(int i = 0; i < n; ++ i) ++ sRank[x[i]];
		for(int i = 1; i < m; ++ i) sRank[i] += sRank[i - 1];
		for(int i = n - 1; i >= 0; -- i) sa[-- sRank[x[y[i]]]] = y[i];
		swap(x, y); x[sa[0]] = 0; p = 1;
		for(int i = 1; i < n; ++ i)
			x[sa[i]] = cmp(y, sa[i], sa[i - 1], d) ? p - 1 : p ++;
	}
}

int getHash(char *c)
{
	int ret = 0;
	for( ; *c; c ++) {
		ret = ret * 37 + *c;
	}
	return ret;
}

inline int getId(const int &l, const int &r)
{
	return (l + r) | (l != r);
}

int cmp2(const int &a, const int &b)
{
	if (len[a] != len[b])
		return len[a] < len[b];
	if (hash[a] == hash[b])
		return a < b;
	return rank[p[a]] < rank[p[b]];
}

vector<int> unionIt(const vector<int> &a, const vector<int> &b)
{
	vector<int> ret;
	for(int i = 0; i < (int)a.size(); ++ i) {
		ret.push_back(a[i]);
	}
	for(int i = 0; i < (int)b.size(); ++ i) {
		ret.push_back(b[i]);
	}
	sort(ret.begin(), ret.end(), cmp2);
	ret.resize(unique(ret.begin(), ret.end()) - ret.begin());
	ret.resize(min((int)ret.size(), 10));
	return ret;
}

void build(int l, int r)
{
	int id = getId(l, r);
	if (l == r) {
		tag[id].push_back(from[sa[l]]);
		return;
	}
	int mid = (l + r) >> 1;
	int lid = getId(l, mid);
	int rid = getId(mid + 1, r);
	build(l, mid);
	build(mid + 1, r);
	tag[id] = unionIt(tag[lid], tag[rid]);
}

vector<int> ask(int l, int r, int a, int b)
{
	vector<int> ret;
	if (b < l || r < a) return ret;
	if (a <= l && r <= b) {
		return tag[getId(l, r)];
	}
	int mid = (l + r) >> 1;
	return unionIt(ask(l, mid, a, b), ask(mid + 1, r, a, b));
}

void query()
{
	scanf("%s", t);
	int length = strlen(t);
	int l = 1, r = tot - 1;
	int tl, tr, tmid;
	int nl, nr;
	for(int i = 0; i < length; ++ i) {
		tl = l - 1;
		tr = r + 1;
		for( ; tl + 1 < tr; ) {
			tmid = (tl + tr) >> 1;
			if (s[sa[tmid] + i] >= t[i]) {
				tr = tmid;
			} else tl = tmid;
		}
		if (tr < l || tr > r || s[sa[tr] + i] != t[i]) {
			puts("-1");
			return;
		}
		nl = tr;

		tl = l - 1;
		tr = r + 1;
		for( ; tl + 1 < tr; ) {
			tmid = (tl + tr) >> 1;
			if (s[sa[tmid] + i] <= t[i]) {
				tl = tmid;
			} else tr = tmid;
		}
		if (tl < l || tl > r || s[sa[tl] + i] != t[i]) {
			puts("-1");
			return;
		}
		nr = tl;

		l = nl;
		r = nr;
	}

	vector<int> ret = ask(1, tot - 1, l, r);
	for(int i = 0; i < (int)ret.size(); ++ i) {
		printf("%d%c", ret[i] + 1, i + 1 == (int)ret.size() ? '\n' : ' ');
	}
}

void solve() {
	char *c = s;
	tot = 0;
	for(int i = 0; i < n; ++ i) {
		scanf("%s", c);
		p[i] = c - s;
		len[i] = strlen(c);
		hash[i] = getHash(c);
		for(int j = 0; j <= len[i]; ++ j) {
			from[tot + j] = i;
		}
		tot += len[i] + 1;
		c = c + len[i];
		*c = 1;
		++ c;
	}
	*c = 0;
	++ c;
	tot ++;

	doubling(s, tot, 1000);
	for(int i = 0; i < tot; ++ i) {
		rank[sa[i]] = i;
	}
	for(int i = 0; i < tot + tot; ++ i) {
		tag[i].clear();
	}
	build(1, tot - 1);

	cin >> q;
	for( ; q --; ) {
		query();
	}
}

int main() {
	for( ; cin >> n; ) {
		solve();
	}
	return 0;
}
