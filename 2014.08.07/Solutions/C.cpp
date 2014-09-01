#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100005;

int n, m, GCD, tot;
int factor[N], type[N];
vector <int> ans;

void doWith(int st, int b) {
	int next = st + b;
	for (int i = st; i < next; i += GCD) {
		int s[3] = {0};
		for (int j = i; j <= n; j += b) {
			s[type[j]]++;
		}

		if (s[1]) {
			for (int j = i; j <= n; j += b) {
				if (!type[j]) {
					ans.push_back(j);
				}
			}
		}
	}
}

int work(int st, int b) {
	int next = st + b, ret = 0;
	for (int i = st; i < next; i += GCD) {
		int s[3] = {0};
		for (int j = i; j <= n; j += b) {
			s[type[j]]++;
		}

		if (s[1]) {
			ret += s[0];
		}
	}

	return ret;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int x;
		scanf("%d", &x);
		type[x] = 1;
	}

	int temp = n;
	for (int i = 2; i * i <= temp; i++) {
		if (temp % i == 0) {
			factor[++tot] = i;
			while (temp % i == 0) {
				temp /= i;
			}
		}
	}

	if (temp > 1) {
		factor[++tot] = temp;
	}

	if (tot == 1) {
		int a = factor[1];
		for (int i = 1; i <= n / a; i++) {
			int s[3] = {0};
			for (int j = i; j <= n; j += n / a) {
				s[type[j]]++;
			}

			if (s[1]) {
				for (int j = i; j <= n; j += n / a) {
					if (!type[j]) {
						ans.push_back(j);
					}
				}
			}
		}
	} else {
		int a = factor[1], b = factor[2];
		GCD = __gcd(n / a, n / b);
		for (int i = 1; i <= GCD; i++) {
			if (work(i, n / a) < work(i, n / b)) {
				doWith(i, n / a);
			} else {
				doWith(i, n / b);
			}
		}
	}

	if (ans.size() + m == n) {
		printf("-1\n");
	} else {
		printf("%d\n", (int)ans.size());
		for (int i = 0; i < (int)ans.size(); i++) {
			if (i == (int)ans.size() - 1) {
				printf("%d\n", ans[i]);
			} else {
				printf("%d ", ans[i]);
			}
		}
	}

	return 0;
}
