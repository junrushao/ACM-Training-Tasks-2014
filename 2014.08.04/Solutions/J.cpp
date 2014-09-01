#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int NN = 100005, L = 100005, MOD = 1000000000;

int n, x[NN], sum[11];

char s[L];

struct Data {
	int v[11];

	Data (int n = 0) {
		memset(v, 0, sizeof(v));
		v[0] = n;
	}

	int& operator[] (const int &i) {
		return v[i];
	}

	const int operator[] (const int &i) const {
		return v[i];
	}

	Data fold() {
		int s = 0;
		for (int i = 0; i <= 10; ++i) {
			(s += (long long)v[i] * sum[i] % MOD) %= MOD;
		}
		return Data(s);
	}
};

Data operator + (const Data &a, const Data &b) {
	Data ret;
	for (int i = 0; i <= 10; ++i) {
		ret[i] = (a[i] + b[i]) % MOD;
	}
	return ret;
}

Data operator - (const Data &a, const Data &b) {
	Data ret;
	for (int i = 0; i <= 10; ++i) {
		ret[i] = (a[i] - b[i]) % MOD;
	}
	return ret;
}

Data operator * (const Data &a, const Data &b) {
	Data ret;
	for (int i = 0; i <= 10; ++i) {
		for (int j = 0; j <= 10; ++j) {
			if (a[i] && b[j]) {
				(ret[i + j] += (long long)a[i] * b[j] % MOD) %= MOD;
			}
		}
	}
	return ret;	
}

int match[L];

int l, cur;

Data X, N;

Data term();

Data expr() {
	char ch = s[cur], ch2 = s[cur + 1];
	if (ch == '(' || ch == 'N' || ch == 'X' || isdigit(ch)) {
		Data tmp = term();
		if (s[cur] == '+' || s[cur] == '-' | s[cur] == '*') {
			char op = s[cur];
			++cur;
			Data tmp2 = expr();
			if (op == '+') {
				tmp = tmp + tmp2;
			} else if (op == '-') {
				tmp = tmp - tmp2;
			} else {
				tmp = tmp * tmp2;
			}
		}
		return tmp;
	} else if (ch == '-' || ch == '*' && ch2 == ':' || ch == '+' && ch2 == '/') {
		if (ch == '-') {
			cur += 1;
		} else {
			cur += 2;
		}
		Data tmp = expr();
		if (ch == '-') {
			tmp = Data(0) - tmp;
		} else if (ch == '*') {
			tmp = tmp * tmp;
		} else if (ch == '+') {
			tmp = tmp.fold();
		}
		return tmp;
	}
}

Data num();

Data term() {
	if (s[cur] == '(') {
		++cur;
		Data ret = expr();
		++cur;
		return ret;
	} else if (s[cur] == 'N') {
		++cur;
		return N;
	} else if (s[cur] == 'X') {
		++cur;
		return X;
	} else {
		return num();
	}
}

Data num() {
	int ret = 0;
	while (isdigit(s[cur])) {
		ret = ret * 10 + s[cur++] - '0';
	}
	return Data(ret);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", x + i);
	}
	fgets(s, L - 1, stdin);
	fgets(s, L - 1, stdin);

	for (int i = 0; i < n; ++i) {
		int mul = 1;
		for (int j = 0; j <= 10; ++j) {
			(sum[j] += mul) %= MOD;	
			mul = (long long)mul * x[i] % MOD;
		}
	}

	N[0] = n;
	X[1] = 1;

	memset(match, -1, sizeof(match));
	l = strlen(s);
	vector<int> stack;
	for (int i = 0; i < l; ++i) {
		if (s[i] == '(') {
			stack.push_back(i);
		} else if (s[i] == ')') {
			match[stack.back()] = i;
			stack.pop_back();
		}
	}

	cur = 0;

	Data ans = expr();
	printf("%d\n", (ans[0] + MOD) % MOD);
	return 0;
}

