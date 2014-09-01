#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1505;

char equ[N];

void print(char ch, int num, bool newline = false) {
	while (num-- > 0) {
		printf("%c", ch);
	}
	if (newline) {
		printf("\n");
	}
}

void print(vector<int> &a, int pos, char op = ' ') {
	while (a.size() > 1 && a.back() == 0) {
		a.pop_back();
	}
	int space = pos - a.size();
	if (op != ' ') {
		--space;
		print(' ', space);
		printf("%c", op);
	} else {
		print(' ', space);
	}
	for (int i = (int)a.size() - 1; i >= 0; --i) {
		printf("%d", a[i]);
	}
	printf("\n");
}

int n;

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%s", equ);
		vector<int> num1, num2, num3;
		char op = ' ';
		n = strlen(equ);
		for (int i = 0; i < n; ++i) {
			if (equ[i] < '0' || equ[i] > '9') {
				op = equ[i];
			} else {
				if (op == ' ') {
					num1.push_back(equ[i] - '0');
				} else {
					num2.push_back(equ[i] - '0');
				}
			}
		}
		reverse(num1.begin(), num1.end());
		reverse(num2.begin(), num2.end());
		if (op == '+') {
			int inc = 0;
			for (int i = 0; i < (int)num1.size() || i < (int)num2.size() || inc; ++i) {
				int tmp = inc;
				if (i < (int)num1.size()) {
					tmp += num1[i];
				}
				if (i < (int)num2.size()) {
					tmp += num2[i];
				}
				inc = tmp / 10;
				tmp %= 10;
				num3.push_back(tmp);
			}
			int len = max(num3.size(), num2.size() + 1);
			print(num1, len);
			print(num2, len, '+');
			print('-', len, true);
			print(num3, len);
		} else if (op == '-') {
			int dec = 0;
			for (int i = 0; i < (int)num1.size() || i < (int)num2.size() || dec; ++i) {
				int tmp = dec;
				if (i < (int)num1.size()) {
					tmp += num1[i];
				}
				if (i < (int)num2.size()) {
					tmp -= num2[i];
				}
				if (tmp < 0) {
					dec = -1;
					tmp += 10;
				} else {
					dec = 0;
				}
				num3.push_back(tmp);
			}
			while (num3.back() == 0 && num3.size() > 1) {
				num3.pop_back();
			}
			int len = max(num1.size(), num2.size() + 1),
				r = max(num2.size() + 1, num3.size());
			print(num1, len);
			print(num2, len, '-');
			print(' ', len - r), print('-', r, true);
			print(num3, len);
		} else {
			vector<int> num3(num1.size() + num2.size());
			for (int i = 0; i < (int)num2.size(); ++i) {
				int inc = 0;
				for (int j = 0; j < (int)num1.size() || inc; ++j) {
					num3[i + j] += inc;
					if (j < (int)num1.size()) {
						num3[i + j] += num2[i] * num1[j];
					}
					inc = num3[i + j] / 10;
					num3[i + j] %= 10;
				}
			}
			while (num3.back() == 0 && num3.size() > 1) {
				num3.pop_back();
			}
			int len = max(num3.size(), num2.size() + 1);
			print(num1, len);
			print(num2, len, '*');
			int last_mul = 0;
			if (num2.size() > 1) {
				for (int i = 0; i < (int)num2.size(); ++i) {
					int clen = len - i;
					vector<int> num3(num1.size() + 1);
					int inc = 0;
					for (int j = 0; j < (int)num1.size() || inc; ++j) {
						num3[j] += inc;
						if (j < (int)num1.size()) {
							num3[j] += num2[i] * num1[j];
						}
						inc = num3[j] / 10;
						num3[j] %= 10;
					}
					while (num3.back() == 0 && num3.size() > 1) {
						num3.pop_back();
					}
					if (i == 0) {
						int r = max((int)num2.size() + 1, (int)num3.size());
						print(' ', len - r), print('-', r, true);
					}
					if (i == (int)num2.size() - 1) {
						last_mul = num3.size() + i;
					}
					print(num3, clen);
				}
			}
			int r = max(last_mul, (int)num3.size());
			print(' ', len - r), print('-', r, true);
			print(num3, len);
		}
		printf("\n");
	}
	return 0;
}
