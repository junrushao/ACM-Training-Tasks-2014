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
#include <cassert>

using namespace std;
typedef long long LL;
typedef long double LD;

#define PII pair<int, int>
#define sz(X) ((int)((X).size()))

#define Rep(i, a, b) for (int i(a); i <= (b); ++i)

template<class T> T abs(T x){return x < 0 ? -x : x;}

int a[1000000];

int main(){
	int Cases;
	scanf("%d", &Cases);
	for (; Cases; --Cases){
		int n, k;
		scanf("%d%d", &n, &k);
		int tot = 0, ans = -1;
		for (int i = 1; i * i <= n; ++i)
			if (n % i == 0){
				--k;
				if (k == 0){
					ans = i;
					break;
				}
				if (i * i != n) a[++tot] = n / i;
			}
		if (ans != -1){
			printf("%d\n", ans);
		} else printf("%d\n", a[tot - k + 1]);
	}
	return 0;
}
