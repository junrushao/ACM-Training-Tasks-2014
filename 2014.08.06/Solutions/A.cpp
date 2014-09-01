#include <climits>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100005;
char s[N], t[6];

int q, n, m;

inline char reverse(char ch) {
	if (ch >= 'A' && ch <= 'Z') {
		return ch - ('A' - 'a');
	} else {
		return ch - ('a' - 'A');
	}
}

inline int getID(int l, int r) {
	return l + r | l != r;
}

bool rev[N << 1];

char getpos(int l, int r, int pos) {
	if (l == r) {
		return rev[getID(l, r)] ? reverse(s[l]) : s[l];
	}
	int m = l + r >> 1;
	char ret;
	if (pos <= m) {
		ret = getpos(l, m, pos);
	} else {
		ret = getpos(m + 1, r, pos);
	}
	return rev[getID(l, r)] ? reverse(ret) : ret;
	
}

int mins[N << 1], maxs[N << 1];

void clear(int l, int r) {
	int x = getID(l, r);
	rev[x] = false;
	mins[x] = -1;
	maxs[x] = -1;
	if (l == r) {
		return;
	}
	int m = l + r >> 1;
	clear(l, m);
	clear(m + 1, r);
}

void pushdown(int l, int r) {
	int x = getID(l, r), m = l + r >> 1, lc = getID(l, m), rc = getID(m + 1, r);
	if (rev[x]) {
		rev[lc] ^= 1;
		swap(mins[lc], maxs[lc]);
		rev[rc] ^= 1;
		swap(mins[rc], maxs[rc]);
		rev[x] = false;
	}
}

void update(int l, int r) {
	int x = getID(l, r), m = l + r >> 1, lc = getID(l, m), rc = getID(m + 1, r);
	mins[x] = max(mins[lc], mins[rc]);
	maxs[x] = max(maxs[lc], maxs[rc]);
}

void insert(int l, int r, int pos, int val) {
	int x = getID(l, r);
	if (l == r) {
		mins[x] = val;
		maxs[x] = m - val;
		return;
	}
	pushdown(l, r);
	int m = l + r >> 1;
	if (pos <= m) {
		insert(l, m, pos, val);
	} else {
		insert(m + 1, r, pos, val);
	}
	update(l, r);
}

void flip(int l, int r, int a, int b) {
	if (r < a || b < l) {
		return;
	}
	int x = getID(l, r);
	if (a <= l && r <= b) {
		rev[x] ^= 1;
		swap(mins[x], maxs[x]);
		return;
	}
	pushdown(l, r);
	int m = l + r >> 1;
	flip(l, m, a, b);
	flip(m + 1, r, a, b);
	update(l, r);
}

inline char nocase(char ch) {
	if (ch >= 'A' && ch <= 'Z') {
		return ch - ('A' - 'a');
	} else {
		return ch;
	}
}

void recalc(int pos) {
	if (pos < 0 || pos + m - 1 >= n) {
		return;
	}
	bool flag = true;
	int cnt = 0;
	for (int i = 0; i < m; ++i) {
		char ch = getpos(0, n - 1, pos + i);
		if (nocase(ch) != nocase(t[i])) {
			flag = false;
		}
		if (ch != t[i]) {
			++cnt;
		}
	}
	if (!flag) {
		return;
	}
	insert(0, n - 1, pos, cnt);
}

int getans(int l, int r, int a, int b) {
	if (b < l || r < a) {
		return INT_MIN;
	}
	int x = getID(l, r);
	if (a <= l && r <= b) {
		return mins[x];
	}
	pushdown(l, r);
	int m = l + r >> 1;
	return max(getans(l, m, a, b), getans(m + 1, r, a, b));
	update(l, r);
}

int main() {
	while (scanf("%d", &q) == 1) {
		scanf("%s%s", t, s);
		m = strlen(t), n = strlen(s);
		clear(0, n - 1);
		for (int i = 0; i + m <= n; ++i) {
			recalc(i);
		}
		for (int i = 0; i < q; ++i) {
			int l, r;
			scanf("%d%d", &l, &r);
			--l, --r;
			int ans = (l + m - 1 <= r) ? getans(0, n - 1, l, r - m + 1) : INT_MIN;
			if (ans > 5 || ans < 0) {
				ans = -1;
			}
			printf("%d\n", ans);
			flip(0, n - 1, l, r);
			for (int i = l - 1; i + m - 1 >= l; --i) {
				recalc(i);
			}
			for (int i = r - m + 2; i <= r; ++i) {
				recalc(i);
			}
		}
	}
	return 0;
}
