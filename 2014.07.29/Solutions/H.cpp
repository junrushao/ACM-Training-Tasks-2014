#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define foreach(e,x) for(__typeof(x.begin()) e=x.begin(); e!=x.end(); ++e)

const int N = 100 + 10;
int n;
int a[N][N];

void solve() {
	cin >> n;
	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j < n; ++ j) {
			scanf("%d", &a[i][j]);
		}
	}
	long long ret = 0;
	for(int i = 0; i < n; ++ i) {
		for(int j = i + 1; j < n; ++ j) {
			ret += min(a[i][j], a[j][i]);
		}
	}
	cout << ret << endl;
}

int main() {
	solve();
	return 0;
}
