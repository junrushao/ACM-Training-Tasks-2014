#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 100005;

char str[N];
int n;

int main() {
	scanf("%d", &n);
	scanf("%s", str + 1);
	int len = strlen(str + 1);
	long long ans = 0;
	int cnt = 0, s = 0;
	for (int i = 1; i <= len; i++) {
		int now = str[i] - '0';
		if (s + now <= n) {
			s += now;
			cnt++;
		} else if (now == 1 && s > cnt) {
			s--;
		}

		ans += cnt;
	}

	cout << ans << endl;
	return 0;
}
