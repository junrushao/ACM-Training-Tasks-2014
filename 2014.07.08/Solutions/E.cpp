#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

const int N = 66;

vector<int> vals;
int a[N], b[N], c[N];
int n, len;
long long k;
long long f[N][N], nxt[N][N];

long long solve() {
	int itr = 0;
	for(int i = 1; i <= len; i++) {
		++itr;
		while(itr <= n && a[itr] != b[i]) {
			++itr;
		}
		if (itr > n)
			return 0;
	}
	memset(f, 0, sizeof(f));
	f[itr][c[itr]] = 1;
	for(int i = itr; i <= n; i++)
		for(int j = 0; j < (int)vals.size(); j++) {
			for(int l = j + 1; l < (int)vals.size(); l++) {
				if (nxt[i][l] != n + 1) {
					f[nxt[i][l]][l] += f[i][j];
				}
			}
		}
	long long ans = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < (int)vals.size(); j++) {
			ans += f[i][j];
		}
	return ans;
	
}

int main() {
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		vals.push_back(a[i]);
	}
	sort(vals.begin(), vals.end());
	vals.erase(unique(vals.begin(), vals.end()), vals.end());
	for(int i = 1; i <= n; i++) {
		c[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < (int)vals.size(); j++) {
			nxt[i][j] = n + 1;
		}
		for(int j = n; j > i; j--) {
			nxt[i][c[j]] = j;
		}
	
	}
	/*
	for(int i = 0 ; i < (int)vals.size(); i++)
		printf("%d ", vals[i]);
	printf("\n");
	*/
	for(len = 1; len; len++) {
		for(int j = 0; j < (int)vals.size(); j++) {
			if (len > 1 && vals[j] <= b[len - 1])
				continue;
			b[len] = vals[j];
			long long r = solve();
			if (r < k) {
				k -= r;
			} else {
				if (--k == 0) {
					printf("%d\n", len);
					for(int itr = 1; itr <= len; itr++) {
						printf("%d%c", b[itr], itr == len ? '\n' : ' ');
					}
					return 0;
				}
				break;
			}
		}
	}
	return 0;
}