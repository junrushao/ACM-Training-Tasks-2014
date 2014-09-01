#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
	int c;
	while (scanf("%d", &c) != EOF) {
		long long a = 2147483647;
		printf("61 90\n");
		
		int j = 32;
		a = 2147483647;
		a++;
		a >>= 1;
		for (int i = 1; i <= 30; i++) {
			if (i < 30) {
				cout << i << ' ' << j << ' ' << -a << endl;
				cout << j << ' ' << i + 1 << ' ' << -a << endl;
			} else {
				cout << i << ' ' << 31 << ' ' << -a << endl;
				cout << 31 << ' ' << 61 << ' ' << -a << endl;
			}
			j++;
			a >>= 1;
		}
		a = 2147483647;
		a++;
		long long b = a;
		b >>= 2;
		for (int i = 1; i <= 30; i++) {
			if (i < 30) {
				cout << i << ' ' << i + 1 << ' ' << b - a << endl;
			} else {
				cout << i << ' ' << 61 << ' ' << b - a << endl;
			}
			a >>= 1;
			b >>= 1;
		}
	}
	return 0;
}

