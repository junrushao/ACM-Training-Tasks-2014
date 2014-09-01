#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2000005;

int fipu[260];

int size[10] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23};
char cha[10] = {79, 95, 46, 44, 45, 126, 61, 39, 94, 34};
int value[11];

char in[N];

char out[N];
int tot = 0;

char ans[N];
int m = 0;

int n = 0, l;

int lib[N], loc[N], v[N];

bool deci(char c) {
	return (c >= '0' && c <= '9');
}

bool dipu(char c) {
	return (fipu[c] >= 0);
}

int cade(int &i) {
	int ans = 0;
	if (in[i] == '0') {
		i++;
		return 0;
	}
	while (i < l && deci(in[i])) {
		if ((long long)ans * 10 + in[i] - 48 >= value[10]) {
			return ans;
		}
		ans = ans * 10 + in[i] - 48;
		i++;
	}
	return ans;
}

int cadi(int &i) {
	int lib, qua, ans = 0;
	lib = fipu[in[i]], qua = 1, i++;
	if (lib == 0) {
		return 0;
	}
	ans += value[lib];
	while (i < l && dipu(in[i])) {
		if (fipu[in[i]] == lib) {
			qua++;
		} else if (fipu[in[i]] > lib) {
			return ans;
		} else {
			lib = fipu[in[i]];
			qua = 1;
		}
		if (qua > size[lib] || lib == 0) {
			return ans;
		}
		ans += value[lib];
		i++;
	}
	return ans;
}

void oude(int x) {
	if (x == 0) {
		ans[++m] = '0';
		return;
	}
	int l = m;
	while (x > 0) {
		ans[++m] = x % 10 + 48;
		x /= 10;
	}
	reverse(ans + l + 1, ans + m + 1);
	return;
}
void oudi(int x) {
	if (x == 0) {
		ans[++m] = 'O';
		return;
	}
	for (int i = 9; i >= 1; i--) {
		while (x >= value[i]) {
			x -= value[i];
			ans[++m] = cha[i];
		}
	}
	return;
}

int main() {
	for (int i = 0; i <= 255; i++) {
		fipu[i] = -1;
	}
	for (int i = 0; i <= 9; i++) {
		fipu[cha[i]] = i;
	}
	value[1] = 1;
	for (int i = 2; i <= 10; i++) {
		value[i] = value[i - 1] * (size[i - 1] + 1);
	}
	tot = 0; n = 0;
	while (fgets(in, N, stdin)) {
		l = strlen(in);
		for (int i = 0; i < l;) {
			if (deci(in[i])) {
				++n, lib[n] = 2, loc[n] = tot, v[n] = cade(i);
			} else if (dipu(in[i])) {
				++n, lib[n] = 1, loc[n] = tot, v[n] = cadi(i);
			} else {
				out[++tot] = in[i];
				i++;
			}
		}
	}
	m = 0;
	out[tot + 1] = '\0';
	if (n & 1) {
		sort(v + 1, v + n + 1);
	}
	loc[n + 1] = 1000000000;
	int y = 1;
	for (int i = 1; i <= tot; i++) {
		while (i > loc[y]) {
			if (lib[y] == 1) {
				oude(v[y]);
			} else {
				oudi(v[y]);
			}
			y++;
		}
		ans[++m] = out[i];
	}
	ans[m] = '\0';
	puts(ans + 1);
	return 0;
}
