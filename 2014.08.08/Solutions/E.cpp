#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1100005;
const int MAX = 100000;
char s[N];

int main() {
	int n;
	while (scanf("%d", &n) != EOF) {
		string a;
		a.clear();
		gets(s);
		for (int i = 1; i <= n; i++) {
			gets(s);
			a += s;
		}
		long long ans = 1;
		int sli = 0;
		for (int i = 0; i < (int)a.size(); i++) {
			if (a[i] == '{') {
				long long now = 1;
				while (a[i] != '}' && i < (int)a.size()) {
					if (a[i] == '|') {
						now++;
					}
					i++;
				}
				ans *= now;
				if (ans > MAX) {
					sli = 1;
				}
			} else {
				if (a[i] == '$') {
					i++;
					long long now1 = 1;
					while (a[i] != '$' && i < (int)a.size()) {
						long long now2 = 1;
						if (a[i] == ' ') {
							while (a[i] == ' ' && i < (int)a.size()) {
								now2++;
								i++;
							}
							now1 *= now2;
							if (now1 > MAX) {
								sli = 1;
							}
						} else {
							i++;
						}
					}
					ans *= now1;
					if (ans > MAX) {
						sli = 1;
					}
				}
			}
		}
		if (sli == 1) {
			printf("doge\n");
		} else {
			cout << ans << endl;
		}
	}
	return 0;
}

