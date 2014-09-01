#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n, k;

int ans[105][105], fin[105][105];

int main() {
	while (scanf("%d%d", &n, &k) == 2) {
		vector<vector<int> > ans1;
		static int id = 0;
		printf("Case #%d:\n", ++id);
		if (k == 1) {
			printf("%d\n", n - 1);
			for (int i = 0; i < n; ++i) {
				printf("%d\n", i + 1);
			}
		} else if (k % 2 == 0) {
			printf("%d\n", 0);
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < k; ++j) {
					printf("%d%c", j & 1 ? n - i : i + 1, j == k - 1 ? '\n' : ' ');
				}
			}
		} else {
			printf("%d\n", 1 - n % 2);
			vector<int> rnd;
			for (int i = 0; i < n; ++i) {
				rnd.push_back(i + 1);
			}
			for (int i = 0; i < k / 2 - 1; ++i) {
				ans1.push_back(rnd);
				reverse(rnd.begin(), rnd.end());
				ans1.push_back(rnd);
				reverse(rnd.begin(), rnd.end());
			}
			if (n % 2 == 0) {
				ans1.push_back(rnd);
				vector<int> nrnd;
				for (int i = 0; i < n / 2; ++i) {
					nrnd.push_back(i + 1 + n / 2);
				}
				for (int i = n / 2; i < n; ++i) {
					nrnd.push_back(i + 1 - n / 2);
				}
				ans1.push_back(nrnd);
				nrnd.clear();
				for (int i = 0; i < n / 2; ++i) {
					nrnd.push_back(i + 1);
					nrnd.push_back(i + 1 + n / 2);
				}
				reverse(nrnd.begin(), nrnd.end());
				ans1.push_back(nrnd);
			} else {
				ans1.push_back(rnd);
				vector<int> nrnd;
				for (int i = 0; i < n / 2; ++i) {
					nrnd.push_back(i + n / 2 + 2);
				}
				for (int i = 0; i <= n / 2; ++i) {
					nrnd.push_back(i + 1);
				}
				ans1.push_back(nrnd);
				nrnd.clear();
				for (int i = 0; i < n / 2 + 1; ++i) {
					nrnd.push_back(i + 1);
					nrnd.push_back(i + 2 + n / 2);
				}
				nrnd.pop_back();
				reverse(nrnd.begin(), nrnd.end());
				ans1.push_back(nrnd);
			}
			vector<vector<int> > rnk(n);
			for (int i = 0; i < k; ++i) {
				for (int j = 0; j < n; ++j) {
					rnk[ans1[i][j] - 1].push_back(j + 1);
				}
			}
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < k; ++j) {
					printf("%d%c", rnk[i][j], j == k - 1 ? '\n' : ' ');
				}
			}
		}
		puts(n % 2 == 0 ? "Yes" : "No");
		if (n % 2 == 0 && n <= 100) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					ans[i][j] = -1;
				}
			}
			for (int i = 0; i < n; ++i) {
				ans[i][i] = 0;
				ans[i][0] = i;
                ans[0][i] = i;
			}
			for (int i = 1; i < n - 1; ++i) {
				int delta = 0;
				for (int j = 1; j < n; ++j) {
					int y = (i + j + delta) % n;
					if (y == 0) {
						++delta;
						++y;
					}
					if (j == i) {
						ans[j][y] = n - 1;
					} else {
						ans[j][y] = i;
					}
				}
			}
			for (int i = 1; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					bool appear = false;
					for (int k = 0; k < n - 1; ++k) {
                        /*
						if (ans[k][i] == -1) {
							ans[k][i] = n - 1;
						}
                        */
						if (ans[k][i] == j) {
							appear = true;
						}
					}
					if (!appear) {
						ans[n - 1][i] = j;
					}
				}
			}
			for (int j = 1; j < n; ++j) {
				for (int i = 0; i < n; ++i) {
					ans[i][j] = ans[ans[i][j]][j - 1];
				}
			}
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    fin[ans[i][j]][j] = i;
                }
            }
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					printf("%d%c", fin[i][j] + 1, j == n - 1 ? '\n' : ' ');
				}
			}
		}
	}
	return 0;
}
