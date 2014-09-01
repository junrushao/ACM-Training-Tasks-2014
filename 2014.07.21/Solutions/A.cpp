#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n;

const int N = 255;

int match[N];

char s[N];

bool ban[N];

//0 NULL 1 + 2 - 3 * 4 /

inline int sym(char ch) {
	if (ch == '+') {
		return 1;
	} else if (ch == '-') {
		return 2;
	} else if (ch == '*') {
		return 3;
	} else if (ch == '/') {
		return 4;
	}
	return -1;
}

//0 NULL + or - front 1  - after 2 * or / front 3 / after 4

bool check(int in, int out) {
	if (in == 5 || out == 0) {
		return true;
	} else if (out == 1) {
		return true;
	} else if (out == 2 || out == 3) {
		return in >= 3;
	} else {
		return false;
	}
}

void release(int l, int r) {
	if (l >= 0 && r < n) {
		ban[l] = ban[r] = true;
	}
}

int front_sym(int i) {
	while (i >= 0 && ban[i]) {
		--i;
	}
	if (i < 0) {
		return 0;
	}
	if (s[i] == '+') {
		return 1;
	} else if (s[i] == '-') {
		return 2;
	} else if (s[i] == '*') {
		return 3;
	} else if (s[i] == '/') {
		return 4;
	}
	return -1;
}

int back_sym(int i) {
	while (i < n && ban[i]) {
		++i;
	}
	if (i >= n) {
		return 0;
	}
	if (s[i] == '+') {
		return 1;
	} else if (s[i] == '-') {
		return 1;
	} else if (s[i] == '*') {
		return 3;
	} else if (s[i] == '/') {
		return 3;
	}
	return -1;
}

void solve(int l, int r, int out_sym) {
	int in_sym = 5;
	for (int i = l; i <= r; ++i) {
		if (match[i] != -1) {
			i = match[i];
			continue;
		}
		if (sym(s[i]) != -1) {
			in_sym = min(in_sym, sym(s[i]));
		}
	}
	if (check(in_sym, out_sym)) {
		release(l - 1, r + 1);
	}
	for (int i = l; i <= r; ++i) {
		if (s[i] == '(') {
			int l = i, r = match[i];
			solve(l + 1, r - 1, max(front_sym(l - 1), back_sym(r + 1)));
			i = match[i];
		}
	}
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%s", s);
		n = strlen(s);
		vector<int> last;	
		memset(match, -1, sizeof(match));
		for (int i = 0; i < n; ++i) {
			if (s[i] == '(') {
				last.push_back(i);
			} else if (s[i] == ')') {
				int j = last.back();
				last.pop_back();
				match[j] = i;
				match[i] = j;
			}
		}
		memset(ban, 0, sizeof(ban));
		solve(0, n - 1, 0);
		string ans;
		for (int i = 0; i < n; ++i) {
			if (!ban[i]) {
				ans += s[i];
			}
		}
		printf("%s\n", ans.c_str());
	}
	return 0;
}

