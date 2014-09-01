#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <ctime>
#include <sstream>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <assert.h>

using namespace std;
typedef long long LL;
typedef long double LD;

#define PII pair<int, int>
#define sz(X) ((int)((X).size()))

template<class T> T abs(T x){return x < 0 ? -x : x;}

const int maxn = 1000;
int c[maxn], x[maxn], y[maxn], r[maxn], tt[maxn];
bool b[maxn];
int n;
map<int, int> M;
queue<int> Q;

int sqr(int t){
	return t * t;
}

bool check(int u, int now){
	for (int i = 0; i < u; ++i)
		if ((now & tt[i])){
			if (sqr(x[i] - x[u]) + sqr(y[i] - y[u]) < sqr(r[i] + r[u])) return false;
		}
	return true;
}

int main(){
	for (int i = 0; i < 24; ++i)
		tt[i] = 1 << i;
	while (scanf("%d", &n)){
		if (n == 0) break;
		for (int i = 0; i < n; ++i){
			scanf("%d%d%d%d", &x[i], &y[i], &r[i], &c[i]);
		}

		M.clear();
		M[(1 << n) - 1] = 0;
		while (!Q.empty()) Q.pop();
		Q.push((1 << n) - 1);

		int ans = 0;
		while (!Q.empty()){
			int now = Q.front();
			for (int i = 0; i < n; ++i){
				if ((now & tt[i]) && check(i, now)) b[i] = true; else b[i] = false;
			}
			for (int i = 0; i < n; ++i)
				if (b[i])
					for (int j = i + 1; j < n; ++j)
						if (b[j] && c[i] == c[j]){
							int tmp = now ^ tt[i] ^ tt[j];
							if (M.find(tmp) == M.end()){
								M[tmp] = M[now] + 2;
								ans = max(ans, M[tmp]);
								Q.push(tmp);
							}
						}
			Q.pop();
		}
		printf("%d\n", ans);
	}
	return 0;
}
