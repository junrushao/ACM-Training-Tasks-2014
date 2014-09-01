#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int base = 10000000;

struct BigInt {
	int len;
	int v[3005];

	void init(const int &x) {
		for (int i = 1; i <= 3000; i++) {
			v[i] = 0;
		}

		len = 1;
		v[1] = x;
	}

	void print() {
		for (int i = len; i >= 1; i--) {
			if (i == len) {
				printf("%d", v[i]);
			} else {
				printf("%07d", v[i]);
			}
		}
		printf("\n");
	}

	void operator *= (const int &b) {
		for (int i = 1; i <= len; i++) {
			v[i] *= b;
		}

		for (int i = 1; i <= len; i++) {
			if (v[i] >= base) {
				v[i + 1] += v[i] / base;
				v[i] %= base;
			}
		}

		while (v[len + 1] > 0) {
			len++;
		}
	}

	friend BigInt operator + (const BigInt &a, const BigInt &b) {
		BigInt ret;
		for (int i = 0; i <= 3000; i++) {
			ret.v[i] = 0;
		}

		ret.len = max(a.len, b.len);
		for (int i = 1; i <= ret.len; i++) {
			ret.v[i] = a.v[i] + b.v[i];
		}

		for (int i = 1; i <= ret.len; i++) {
			if (ret.v[i] >= base) {
				ret.v[i + 1] += ret.v[i] / base;
				ret.v[i] %= base;
			}
		}

		while (ret.v[ret.len + 1] > 0) {
			ret.len++;
		}
		return ret;
	}
} ans, ans1, ans2;

const int N = 20005;

char str[N];
int ways[30];

void work() {
	int n = strlen(str + 1);
	for (int i = 1; i <= n; i++) {
		str[i] -= '0';
	}

	int i = n, j = 1, jw1 = 0, jw2 = 0;
	if (n == 1) {
		if (str[1] % 2 == 0) {
			printf("1\n");
		} else {
			printf("0\n");
		}

		return;
	}

	int flag = 0;
	ans.init(0);
	ans1.init(1);
	ans2.init(1);
	while (1) {

		if (i <= j) {
			break;
		}

		int now;
		for (now = 0; now <= 18; now++) {
			if ((now + jw1) % 10 == str[i] && ((jw2 * 10 + str[j] == now) || (jw2 * 10 + str[j] == now + 1))) {
				break;
			}
		}

		if (i == n && now < 10) {
			ans1 *= (ways[now] - 1);
		} else {
			ans1 *= (ways[now]);
		}

		jw1 = (now + jw1) / 10;
		if (jw2 * 10 + str[j] == now + 1) {
			jw2 = 1;
		} else {
			jw2 = 0;
		}

		if (now == 19) {
			flag = 1;
			break;
		}

		i--, j++;
	}

	if (!flag) {
		if (i < j) {
			if (jw1 == jw2) {
				ans = ans + ans1;
			}
		} else {
			int now;
			for (now = 0; now <= 9; now++) {
				if (now + now + jw1 == jw2 * 10 + str[i]) {
					break;
				}
			}

			if (now != 10) {
				ans = ans + ans1;
			}
		}
	}

	if (str[1] == 1) {
		i = n, j = 2, jw1 = 0, jw2 = 1;
		flag = 0;
		while (1) {
			if (i <= j) {
				break;
			}

			int now;
			for (now = 0; now <= 18; now++) {
				if ((now + jw1) % 10 == str[i] && ((jw2 * 10 + str[j] == now) || (jw2 * 10 + str[j] == now + 1))) {
					break;
				}
			}

			if (now < 10 && i == n) {
				ans2 *= (ways[now] - 1);
			} else {
				ans2 *= ways[now];
			}

			jw1 = (now + jw1)/ 10;
			if (jw2 * 10 + str[j] == now + 1) {
				jw2 = 1;
			} else {
				jw2 = 0;
			}

			if (now == 19) {
				flag = 1;
				break;
			}

			i--, j++;
		}

		if (!flag) {
			if (i < j) {
				if (jw1 == jw2) {
					ans = ans + ans2;
				}
			} else {
				int now;
				for (now = 0; now <= 9; now++) {
					if (now + now + jw1 == jw2 * 10 + str[i]) {
						break;
					}
				}

				if (now != 10) {
					ans = ans + ans2;
				}
			}
		}
	}
	ans.print();
}

int main() {
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			ways[i + j]++;
		}
	}
	while (1) {
		scanf("%s", str + 1);
		if (str[1] == '0' && str[2] == 0) {
			break;
		}
		work();
	}
	return 0;
}
