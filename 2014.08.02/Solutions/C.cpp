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
const int MOD = 1e9 + 7;

int n;
int b[N];
long long mul1[N], sum1[N], mul2[N], sum2[N];
int vis[N], c[N];
pair<int, int> a[N];

long long modPow(long long a, long long p)
{
	long long ret = 1;
	for( ; p; p >>= 1) {
		if (p & 1) {
			ret = ret * a % MOD;
		}
		a = a * a % MOD;
	}
	return ret;
}

int getId(int l, int r)
{
	return (l + r) | (l != r);
}

void multi(int l, int r, int a, int b, long long *mul, long long *sum)
{
	if (a > b) return;
	if (b < l || a > r) return;
	int id = getId(l, r);
	if (a <= l && r <= b) {
		mul[id] = mul[id] * 2 % MOD;
		sum[id] = sum[id] * 2 % MOD;
		return;
	}
	int mid = (l + r) >> 1;
	int lid = getId(l, mid);
	int rid = getId(mid + 1, r);
	if (mul1[id] != -1) {
		mul1[lid] = mul1[lid] * mul1[id] % MOD;
		sum1[lid] = sum1[lid] * mul1[id] % MOD;
		mul1[rid] = mul1[rid] * mul1[id] % MOD;
		sum1[rid] = sum1[rid] * mul1[id] % MOD;
		mul1[id] = 1;
	}
	if (mul2[id] != -1) {
		mul2[lid] = mul2[lid] * mul2[id] % MOD;
		sum2[lid] = sum2[lid] * mul2[id] % MOD;
		mul2[rid] = mul2[rid] * mul2[id] % MOD;
		sum2[rid] = sum2[rid] * mul2[id] % MOD;
		mul2[id] = 1;
	}
	multi(l, mid, a, b, mul, sum);
	multi(mid + 1, r, a, b, mul, sum);
	sum1[id] = (sum1[lid] + sum1[rid]) % MOD;
	sum2[id] = (sum2[lid] + sum2[rid]) % MOD;
}

void modify(int l, int r, int p, long long val)
{
	if (p < l || p > r) return;
	int id = getId(l, r);
	if (l == r) {
		sum1[id] = mul1[id] * val % MOD;
		sum2[id] = mul2[id] * val % MOD;
		return;
	}
	int mid = (l + r) >> 1;
	int lid = getId(l, mid);
	int rid = getId(mid + 1, r);
	if (mul1[id] != -1) {
		mul1[lid] = mul1[lid] * mul1[id] % MOD;
		sum1[lid] = sum1[lid] * mul1[id] % MOD;
		mul1[rid] = mul1[rid] * mul1[id] % MOD;
		sum1[rid] = sum1[rid] * mul1[id] % MOD;
		mul1[id] = 1;
	}
	if (mul2[id] != -1) {
		mul2[lid] = mul2[lid] * mul2[id] % MOD;
		sum2[lid] = sum2[lid] * mul2[id] % MOD;
		mul2[rid] = mul2[rid] * mul2[id] % MOD;
		sum2[rid] = sum2[rid] * mul2[id] % MOD;
		mul2[id] = 1;
	}
	modify(l, mid, p, val);
	modify(mid + 1, r, p, val);
	sum1[id] = (sum1[lid] + sum1[rid]) % MOD;
	sum2[id] = (sum2[lid] + sum2[rid]) % MOD;
}

long long query(int l, int r, int a, int b, long long *sum)
{
	if (a > b) return 0;
	if (b < l || a > r) return 0;
	int id = getId(l, r);
	if (a <= l && r <= b) {
		return sum[id];
	}
	int mid = (l + r) >> 1;
	int lid = getId(l, mid);
	int rid = getId(mid + 1, r);
	if (mul1[id] != -1) {
		mul1[lid] = mul1[lid] * mul1[id] % MOD;
		sum1[lid] = sum1[lid] * mul1[id] % MOD;
		mul1[rid] = mul1[rid] * mul1[id] % MOD;
		sum1[rid] = sum1[rid] * mul1[id] % MOD;
		mul1[id] = 1;
	}
	if (mul2[id] != -1) {
		mul2[lid] = mul2[lid] * mul2[id] % MOD;
		sum2[lid] = sum2[lid] * mul2[id] % MOD;
		mul2[rid] = mul2[rid] * mul2[id] % MOD;
		sum2[rid] = sum2[rid] * mul2[id] % MOD;
		mul2[id] = 1;
	}
	return query(l, mid, a, b, sum) + query(mid + 1, r, a, b, sum);
}

int ask(int p)
{
	++ p;
	int ret = 0;
	for( ; p; p -= p & -p)
		ret += c[p];
	return ret;
}

void add(int p, int x)
{
	++ p;
	for( ; p < N; p += p & -p)
		c[p] += x;
}

void solve() {
	cin >> n;
	for(int i = 0; i < n; ++ i) {
		scanf("%d%d", &a[i].first, &a[i].second);
		b[i] = a[i].second;
	}
	sort(a, a + n);
	sort(b, b + n);
	int m = unique(b, b + n) - b;

	for(int i = 0; i < n + n; ++ i) {
		mul1[i] = 1;
		mul2[i] = 1;
	}

	long long ret = 0, ans, val;
	for(int i = 0; i < n; ++ i) {
		ans = modPow(2, a[i].first);
		val = modPow(3, a[i].second);
		int pos = lower_bound(b, b + m, a[i].second) - b;
		int cnt = ask(pos);
		long long tmp1 = query(0, n - 1, pos + 1, n - 1, sum1);
		long long tmp2 = query(0, n - 1, pos + 1, n - 1, sum2);
		ret = (ret + ans * val % MOD * modPow(2, cnt) % MOD + ans * ((tmp1 - tmp2) % MOD + MOD) % MOD) % MOD;

		if (vis[pos]) {
		} else {
			vis[pos] = true;
			modify(0, n - 1, pos, val);
		}
		add(pos, 1);
		multi(0, n - 1, pos, n - 1, sum1, mul1);
		multi(0, n - 1, pos + 1, n - 1, sum2, mul2);
	}
	cout << ret << endl;
}

int main() {
	solve();
	return 0;
}
