#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <set>
using namespace std;

const int DELTA = 3;
long long DELTA2;

const int N = 1111;

vector<long long> s;
long long vet[N][N], f[N][N];
char map[N][N];
long long power[N], power2[N];
int n, m, t, p, q;

int main() {
	while(scanf("%d %d %d %d %d", &n, &m, &t, &p, &q) == 5) {
		if (n == 0 || m == 0 || t == 0 || p == 0 || q == 0) {
			break;
		}
		s.clear();
		power[0] = 1;
		for(int i = 1; i <= m; i++) {
			power[i] = power[i - 1] * DELTA;
		}
		for(int i = 1; i <= n; i++) {
			scanf("%s", map[i] + 1);
		}
		for(int i = 1; i <= n; i++) {
			long long h = 0;
			for(int j = 0; j < q; j++) {
				h = h * DELTA + (map[i][m - j] == '*');
			}
			for(int j = m - q + 1; j >= 1; j--) {
				vet[i][j] = h;
				h = h - power[q - 1] * (map[i][j + q - 1] == '*');
				h = h * DELTA + (map[i][j - 1] == '*');
			}
		}
		DELTA2 = power[q];
		power2[0] = 1;
		for(int i = 1; i <= n; i++) {
			power2[i] = power2[i - 1] * DELTA2;
		}
		m = m - q + 1;
		for(int i = 1; i <= m; i++) {
			long long h = 0;
			for(int j = 0; j < p; j++) {
				h = h * DELTA2 + vet[n - j][i];
			}
			for(int j = n - p + 1; j >= 1; j--) {
				s.push_back(h);
				//cout << h << endl;
				h = h - power2[p - 1] * vet[j + p - 1][i];
				h = h * DELTA2 + vet[j - 1][i];
			}
		} 
		sort(s.begin(), s.end());
		s.erase(unique(s.begin(), s.end()), s.end());
			int result = 0;
		for(int i = 1; i <= t; i++) {
			for(int j = 1; j <= p; j++) {
				scanf("%s", map[j] + 1);
			}
			long long cur = 0;
			for(int j = p; j >= 1; j--)
				for(int k = q; k >= 1; k--) {
					cur = cur * DELTA + (map[j][k] == '*');
				}
			int pos = lower_bound(s.begin(), s.end(), cur) - s.begin();
			if (pos < (int)s.size() && s[pos] == cur) {
				result++;
			}
		}
		static int testCount = 0;
		printf("Case %d: %d\n", ++testCount, result);
	}	
	return 0;
}

