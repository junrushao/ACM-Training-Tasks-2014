#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#define find FIND

using namespace std;

const int N = 5005;

int aa[N], bb[N];
int n, k, t1, t2;
int hashNow[N], hashCnt;
int match[N];
string s[N];

map <string, int> pre, su;
map <string, int> :: iterator it;
vector <int> v[N], ans1[N], ans2[N];

int find(int i, int banb) {
	for (int x = 0; x < (int)v[i].size(); x++) {
		int y = v[i][x];
		if (y == banb || hashNow[y] == hashCnt) {
			continue;
		}

		hashNow[y] = hashCnt;
		int temp = match[y];
		if (temp == 0 || find(temp, banb)) {
			return 1;
		}
	}

	return 0;
}

int dfs(int i) {
	for (int x = 0; x < (int)v[i].size(); x++) {
		int y = v[i][x];
		if (hashNow[y] == hashCnt) {
			continue;
		}

		hashNow[y] = hashCnt;
		int temp = match[y];
		match[y] = i;
		if (temp == 0 || dfs(temp)) {
			return 1;
		}
		
		match[y] = temp;
	}

	return 0;
}

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		pre[s[i].substr(0, k)] = 0;
		su[s[i].substr(s[i].size() - k, k)] = 0;
	}

	t1 = 0;
	for (it = pre.begin(); it != pre.end(); ++it) {
		it->second = ++t1;
	}

	t2 = 0;
	for (it = su.begin(); it != su.end(); ++it) {
		it->second = ++t2;
	}

	for (int i = 1; i <= n; i++) {
		int a = pre[s[i].substr(0, k)], b = su[s[i].substr(s[i].size() - k, k)];
		aa[i] = a, bb[i] = b;
		v[a].push_back(b);
	}

	int ans = 0;
	for (int i = 1; i <= t1; i++) {
		hashCnt++;
		ans += dfs(i);
	}

	printf("%d\n", ans);
	for (int i = 1; i <= n; i++) {
		int a = aa[i], b = bb[i];
		hashCnt++;
		if (match[b] == 0 || find(match[b], b)) {
			ans1[a].push_back(i);
		} else {
			ans2[b].push_back(i);
		}
	}
	
	for (int i = 1; i <= t1; i++) {
		if ((int)ans1[i].size()) {
			printf("%d", (int)ans1[i].size());
			for (int j = 0; j < (int)ans1[i].size(); j++) {
				printf(" %d", ans1[i][j]);
			}

			printf("\n");
		}
	}

	for (int i = 1; i <= t2; i++) {
		if ((int)ans2[i].size()) {
			printf("%d", (int)ans2[i].size());
			for (int j = 0; j < (int)ans2[i].size(); j++) {
				printf(" %d", ans2[i][j]);
			}

			printf("\n");
		}
	}

	return 0;
}

