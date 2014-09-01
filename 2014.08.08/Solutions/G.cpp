#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define left LEFT
#define right RIGHT

using namespace std;

const int N = 500005;

int n, m, tot;
int left[N], right[N], tag[N];
long long sum[N], fib[N];

void up(const int &i) {
	sum[i] = sum[i << 1] + sum[(i << 1) | 1];
}

void make(int l, int r, int i) {
	int mid = (l + r) >> 1;
	left[i] = l, right[i] = r, tag[i] = sum[i] = 0;
	if (l == r) {
		return;
	}

	make(l, mid, (i << 1));
	make(mid + 1, r, ((i << 1) | 1));
}

void work(const int &l, const int &r, const int &i, const int &type, long long &v) {
	if (l > right[i] || r < left[i]) {
		return;
	}

	if (l <= left[i] && r >= right[i]) {
		if (type == 1) {
			sum[i] += v;
			tag[i] = 0;
		} else {
			v += sum[i];
		}

		return;
	}

	if (type == 1) {
		tag[i] = 0;
	}

	work(l, r, (i << 1), type, v);
	work(l, r, ((i << 1) | 1), type, v);
	up(i);
}

long long ask(const long long &v) {
	if (v <= 1LL) {
		return 1LL;
	}

	int pos = upper_bound(fib + 1, fib + tot + 1, v) - fib;
	if (fib[pos] - v < v - fib[pos - 1]) {
		return fib[pos];
	} else {
		return fib[pos - 1];
	}
}

void modify(const int &l, const int &r, const int &i) {
	if (l > right[i] || r < left[i]) {
		return;
	}

	if (tag[i]) {
		return;
	}

	if (left[i] == right[i]) {
		sum[i] = ask(sum[i]);
		return;
	}

	if (l <= left[i] && r >= right[i]) {
		tag[i] = 1;
	}

	modify(l, r, (i << 1));
	modify(l, r, ((i << 1) | 1));
	up(i);
}

void work() {
	make(1, n, 1);
	while (m--) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			int k, d;
			scanf("%d %d", &k, &d);
			long long dd = d;
			work(k, k, 1, 1, dd);
		} else if (type == 2) {
			long long ans = 0;
			int l, r;
			scanf("%d %d", &l, &r);
			work(l, r, 1, 2, ans);
			cout << ans << endl;
		} else {
			int l, r;
			scanf("%d %d", &l, &r);
			modify(l, r, 1);
		}
	}
}

int main() {
	fib[1] = 1, fib[2] = 1;
	for (int i = 3; fib[i - 1] < (1LL << 60); i++) {
		tot = i;
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	
	while (scanf("%d %d", &n, &m) == 2 && (n + m)) {
		work();
	}

	return 0;
}
