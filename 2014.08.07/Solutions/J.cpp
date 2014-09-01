#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define left LEFT
#define right RIGHT

using namespace std;

const int N = 500005;

int n, s, k;
int left[N], right[N];
long long val[N], ans[N], tagA[N], tagB[N], ansNow;

void down(const int &i) {
	int lc = (i << 1), rc = (lc | 1);
	if (!tagA[i]) {
		return;
	}

	tagA[lc] = tagA[i];
	tagB[lc] = tagB[i];
	tagA[rc] = tagA[i];
	tagB[rc] = tagB[i];
	tagA[i] = tagB[i] = 0;
}

void make(const int &l, const int &r, const int &i) {
	int mid = (l + r) >> 1;
	left[i] = l, right[i] = r;
	tagA[i] = tagB[i] = 0;
	if (l == r) {
		ans[i] = val[l];
		return;
	}

	make(l, mid, (i << 1));
	make(mid + 1, r, ((i << 1) | 1));
}

void ask(const int &l, const int &r, const int &i) {
	if (l > right[i] || r < left[i]) {
		return;
	}

	if (l <= left[i] && r >= right[i]) {
		if (tagA[i]) {
			ans[i] = (tagA[i] * (long long)l + tagB[i]);
			tagA[i] = tagB[i] = 0;
		}

		ansNow = ans[i];
		return;
	}

	down(i);
	ask(l, r, (i << 1));
	ask(l, r, ((i << 1) | 1));
}

void add(const int &l, const int &r, const int &i, const long long &a, const long long &b) {
	if (l > right[i] || r < left[i]) {
		return;
	}

	if (l <= left[i] && r >= right[i]) {
		tagA[i] = a;
		tagB[i] = b;
		return;
	}

	down(i);
	add(l, r, (i << 1), a, b);
	add(l, r, ((i << 1) | 1), a, b);
}

int main() {
	scanf("%d %d %d", &n, &s, &k);
	for (int i = 1; i <= n; i++) {
		val[i] = abs(i - s);
	}

	make(1, n, 1);
	for (int i = 1; i <= k; i++) {
		int l, r;
		long long a, b;
		scanf("%d %d", &l, &r);
		if (l == 1) {
			ask(r + 1, r + 1, 1);
			b = ansNow;
			add(1, r, 1, -1, b + r + 1);
		} else if (r == n) {
			ask(l - 1, l - 1, 1);
			a = ansNow;
			add(l, n, 1, 1, a - l + 1);
		} else {
			ask(l - 1, l - 1, 1);
			a = ansNow;
			ask(r + 1, r + 1, 1);
			b = ansNow;
			int ll = l - 1, rr = r;
			while (ll < rr) {
				int mid = (ll + rr + 1) >> 1;
				if ((long long)mid + (a - (long long)l + 1LL) < (b + (long long)r + 1LL) - (long long)mid) {
					ll = mid;
				} else {
					rr = mid - 1;
				}
			}

			if (ll >= l) {
				add(l, ll, 1, 1, a - l + 1);
			}

			if (ll + 1 <= r) {
				add(ll + 1, r, 1, -1, b + r + 1);
			}
		}
	}

	long long lastAns = (1LL << 60);
	for (int i = 1; i <= n; i++) {
		ask(i, i, 1);
	//	cout << ansNow << endl;
		lastAns = min(lastAns, ansNow);
	}

	cout << lastAns << endl;	
	return 0;
}

