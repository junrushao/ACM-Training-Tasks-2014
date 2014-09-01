#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int INF = 1000000000;

int n;

int main() {
	while (scanf("%d", &n) == 1 && n) {
		vector<int> front, back, maxs;
		maxs.push_back(-INF);
		int sum = 0;
		while(n--) {
			char op[2];
			scanf("%s", op);
			if (op[0] == 'I') {
				int x;
				scanf("%d", &x);
				front.push_back(x);
				maxs.push_back(max(maxs.back(), sum += front.back()));
			} else if (op[0] == 'D') {
				sum -= front.back();
				front.pop_back();
				maxs.pop_back();
			} else if (op[0] == 'L') {
				if (front.size()) {
					back.push_back(front.back());
					sum -= front.back();
					front.pop_back();
					maxs.pop_back();
				}
			} else if (op[0] == 'R') {
				if (back.size()) {
					front.push_back(back.back());
					maxs.push_back(max(maxs.back(), sum += front.back()));
					back.pop_back();
				}
			} else if (op[0] == 'Q') {
				int k;
				scanf("%d", &k);
				printf("%d\n", maxs[k]);
			}
		}
	}
	return 0;
}

