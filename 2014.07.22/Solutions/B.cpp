#include<cstdio>
#include<string>
#include<iostream>
using namespace std;
string a, b, c;
int main() {
	int T, TT, i;
	scanf("%d", &TT);
	for (T = 1; T <= TT; T++) {
		cin >> a >> b;
		printf("Case %d: ", T);
		if (a == b) {
			printf("Login successful.\n");
			continue;
		}
		c = a;
		for (i = 0; i < c.length(); i++) {
			if (c[i] >= 'A' && c[i] <= 'Z') {
				c[i] = c[i] - 'A' + 'a';
			} else if (c[i] >= 'a' && c[i] <= 'z') {
				c[i] = c[i] - 'a' + 'A';
			}
		}
		if (c == b) {
			printf("Wrong password. Please, check your caps lock key.\n");
			continue;
		}
		for (i = 0; i < c.length(); i++) {
			if (c[i] >= '0' && c[i] <= '9') {
				c.erase(i, 1);
				i--;
			}
		}
		if (c == b) {
			printf("Wrong password. Please, check your caps lock and num lock keys.\n");
			continue;
		}
		for (i = 0; i < c.length(); i++) {
			if (c[i] >= 'A' && c[i] <= 'Z') {
				c[i] = c[i] - 'A' + 'a';
			} else if (c[i] >= 'a' && c[i] <= 'z') {
				c[i] = c[i] - 'a' + 'A';
			}
		}
		if (c == b) {
			printf("Wrong password. Please, check your num lock key.\n");
			continue;
		}
		printf("Wrong password.\n");
	}
	return 0;
}
