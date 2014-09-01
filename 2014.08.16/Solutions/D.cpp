#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#define pb push_back
#define mp make_pair

using namespace std;

const int N = 3005;
const int INF = 1000000000;

int b, ins, d, c, l1, l2;
int f[N][N];
char s1[N], s2[N];
pair <int, int> succ[N][N], best[N];
vector <pair <int, int> > ans1;
string ans2;

int main() {
	scanf("%d %d %d %d", &b, &ins, &d, &c);
	scanf("%s", s1 + 1);
	scanf("%s", s2 + 1);
	l1 = strlen(s1 + 1), l2 = strlen(s2 + 1);
	for (int i = 0; i <= l1; i++) {
		for (int j = 0; j <= l2; j++) {
			f[i][j] = INF;
		}
	}

	for (int i = 1; i <= l2; i++) {
		best[i] = mp(INF, 0);
	}

	f[0][0] = 0;
	best[0] = mp(0, 0);
	for (int i = 0; i <= l1; i++) {
		for (int j = 0; j <= l2; j++) {
			if (i == 0 && j == 0) {
				continue;
			}

			int costB = best[j].first + b, costI = j ? f[i][j - 1] + ins : INF;
			int costD = i ? f[i - 1][j] + d : INF, costC = (i && j && s1[i] == s2[j]) ? f[i - 1][j - 1] + c : INF;
			f[i][j] = min(min(costB, costI), min(costD, costC));
			if (costB == f[i][j]) {
				succ[i][j] = mp(1, best[j].second);
			} else if (costI == f[i][j]) {
				succ[i][j] = mp(2, 0);
			} else if (costD == f[i][j]) {
				succ[i][j] = mp(3, 0);
			} else {
				succ[i][j] = mp(4, 0);
			}

			best[j] = min(best[j], mp(f[i][j], i));
		}
	}

	printf("%d\n", f[l1][l2]);
	while (l1 || l2) {
		//printf("%d %d\n", l1, l2);
		int type = succ[l1][l2].first;
		if (type == 1) {
			ans1.pb(mp(succ[l1][l2].second + 1, l1));
			l1 = succ[l1][l2].second;
		} else if (type == 2) {
			ans2 += 'I';
			l2--;
		} else if (type == 3) {
			ans2 += 'D';
			l1--;
		} else {
			ans2 += 'C';
			l1--;
			l2--;
		}
	}

	printf("%d\n", (int)ans1.size());
	for (int i = 0; i < (int)ans1.size(); i++) {
		printf("%d %d\n", ans1[i].first, ans1[i].second);
	}

	reverse(ans2.begin(), ans2.end());
	printf("%s\n", ans2.c_str());
	return 0;
}

