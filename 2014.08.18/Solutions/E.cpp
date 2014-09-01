#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n;

const int N = 10005;

int num[N];
pair<int, int> ans[N];

int stamp, vis[10][10];

bool hasSame(int n) {
	int tmp[4];
	for (int i = 0; i < 4; ++i) {
		tmp[i] = n % 10;
		n /= 10;
	}
	sort(tmp, tmp + 4);
	for (int i = 0; i < 3; ++i) {
		if (tmp[i] == tmp[i + 1]) {
			return true;
		}
	}
	return false;
}

pair<int, int> cal(int a, int b) {
	int hit = 0, blow = 0, ta[4], tb[4];
	for (int i = 0; i < 4; ++i) {
		ta[i] = a % 10, tb[i] = b % 10;
		a /= 10, b /= 10;
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (ta[i] == tb[j]) {
				if (i == j) {
					++hit;
				} else {
					++blow;
				}
			}
		}
	}
	return make_pair(hit, blow);
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; ++i) {
			int ta, tb;
			scanf("%d%d%d", &num[i], &ta, &tb);
			ans[i] = make_pair(ta, tb);
		}
		vector<int> sec;
		for (int i = 0; i < 10000 && sec.size() <= 15; ++i) {
			if (hasSame(i)) {
				continue;
			}
			bool flag = true;
			for (int j = 0; j < n && flag; ++j) {
				if (cal(num[j], i) != ans[j]) {
					flag = false;
				}
			}
			if (flag) {
				sec.push_back(i);
			}
		}
		if (sec.size() == 1) {
			printf("%04d\n", sec[0]);
		} else if (sec.size() > 15) {
			printf("????\n");
		} else {
			bool find = false;
			for (int i = 0; i < 10000 && !find; ++i) {
				if (hasSame(i)) {
					continue;
				}
				bool flag = true;
				++stamp;
				for (int j = 0; j < (int)sec.size() && flag; ++j) {
					pair<int, int> res = cal(sec[j], i);
					if (vis[res.first][res.second] == stamp) {
						flag = false;
					} else {
						vis[res.first][res.second] = stamp;
					}
				}
				if (flag) {
					printf("%04d\n", i);
					find = true;
				}
			}
			if (!find) {
				printf("????\n");
			}
		}
	}
	return 0;
}
