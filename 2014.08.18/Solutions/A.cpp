#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n; 
long long m;

string ans;

const int N = 21 << 1;

long long cb[N][N], cat[N];

void go(int n, long long m) {
	if (n <= 0) {
		return;
	}
	ans += 'E';
	for (int i = n - 1; i >= 0; --i) {
		if (m < cat[i] * cat[n - 1 - i]) {
			go(i, m / cat[n - 1 - i]);
			ans += 'S';
			go(n - i - 1, m % cat[n - 1 - i]);
			break;
		} else {
			m -= cat[i] * cat[n - 1 - i];
		}
	}
}

int main() {
	for (int i = 0; i < N; ++i) {
		cb[i][0] = cb[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			cb[i][j] = cb[i - 1][j - 1] + cb[i - 1][j];
		}
	}
	cat[0] = 1;
	for (int i = 1; i < N / 2; ++i) {
		cat[i] = cb[2 * i][i] / (i + 1);
	}
	while (cin >> n >> m) {
		if (!n && !m) {
			break;
		}
		--m;
		ans = "";
		if (m < cat[n - 1]) {
			go(n - 1, m);
			printf("%s\n", ans.c_str());
		} else {
			printf("ERROR\n");
		}
	}
	return 0;
}

