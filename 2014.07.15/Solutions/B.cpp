#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

int flag, test;
string str;

void dfs(string now) {
	if (flag) {
		return;
	}

	//cout << now << endl;
	int f[30] = {0};
	if (now.size() == 0) {
		flag = 1;
		return;
	}

	int ss = now.size();
	f[ss - 1] = 1;
	for (int i = ss - 2; i >= 0; i--) {
		if (now[i] == now[i + 1]) {
			f[i] = f[i + 1] + 1;
		} else {
			f[i] = 1;
		}
	}

	//printf("f[0] = %d\n", f[0]);
	string temp;
	for (int i = 0; i < ss; i++) {
		if (f[i] == 1) {
			continue;
		}

		if (i == 0 || now[i] != now[i - 1]) {
			temp = now;
			temp.erase(i, f[i]);
			dfs(temp);
		}
	}
}

void work() {
	cin >> str;
	flag = 0;
	dfs(str);
	printf("%d\n", flag);
}

int main() {
	scanf("%d", &test);
	while (test--) {
		work();
	}
}
