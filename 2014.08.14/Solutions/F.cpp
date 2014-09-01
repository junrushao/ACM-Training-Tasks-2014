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
#include <cassert>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

const int N = 200000 + 10;
int n, q;
bool same[N];
unsigned color[N];
unsigned a[N];

inline int getId(int l, int r)
{
	return (l + r) | (l != r);
}

void update(int l, int r)
{
	int id = getId(l, r);
	int mid = (l + r) >> 1;
	int lid = getId(l, mid);
	int rid = getId(mid + 1, r);
	if (same[lid] && same[rid] && color[lid] == color[rid]) {
		same[id] = true;
		color[id] = color[lid];
		return;
	}
	same[id] = false;
}

void relax(int l, int r)
{
	int id = getId(l, r);
	if (! same[id]) return;
	int mid = (l + r) >> 1;
	int lid = getId(l, mid);
	int rid = getId(mid + 1, r);
	same[lid] = true;
	color[lid] = color[id];
	same[rid] = true;
	color[rid] = color[id];
}

void build(int l, int r)
{
	int id = getId(l, r);
	if (l == r) {
		same[id] = true;
		color[id] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid);
	build(mid + 1, r);
	update(l, r);
}

void change1(int l, int r, int a, int b, unsigned x)
{
	if (b < l || r < a) return;
	if (a <= l && r <= b) {
		int id = getId(l, r);
		same[id] = true;
		color[id] = x;
		return;
	}
	relax(l, r);
	int mid = (l + r) >> 1;
	change1(l, mid, a, b, x);
	change1(mid + 1, r, a, b, x);
	update(l, r);
}

void change2(int l, int r, int a, int b, unsigned x)
{
	if (b < l || r < a) return;
	int id = getId(l, r);
	if (a <= l && r <= b && same[id] == true) {
		if (color[id] >= x) {
			color[id] = __gcd(color[id], x);
		}
		return;
	}
	relax(l, r);
	int mid = (l + r) >> 1;
	change2(l, mid, a, b, x);
	change2(mid + 1, r, a, b, x);
	update(l, r);
}

void output(int l, int r)
{
	if (l == r) {
		assert(same[getId(l, r)]);
		printf("%u ", color[getId(l, r)]);
		return;
	}
	relax(l, r);
	int mid = (l + r) >> 1;
	output(l, mid);
	output(mid + 1, r);
}

void solve() {
	cin >> n;
	for(int i = 0; i < n; ++ i) {
		scanf("%u", a + i);
	}
	cin >> q;
	build(0, n - 1);
	int t, l, r;
	unsigned x;
	for(int i = 0; i < q; ++ i) {
		scanf("%d%d%d%u", &t, &l, &r, &x);
		-- l, -- r;
		if (t == 1) {
			change1(0, n - 1, l, r, x);
		} else {
			change2(0, n - 1, l, r, x);
		}
	}
	output(0, n - 1);
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
