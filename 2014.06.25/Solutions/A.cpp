
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

const int maxn = 1000000;
int prime[maxn], sum[maxn];
bool b[maxn];
int tot, n;

int main(){
	memset(b, false, sizeof(b));
	b[1] = true;
	tot = 0;
	for (int i = 2; i <= 300000; ++i){
		if (!b[i]){
			prime[++tot] = i;
		}
		for (int j = 1; j <= tot; ++j){
			if (i * prime[j] > 300000) break;
			b[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}

	memset(sum, 0, sizeof(sum));
	for (int i = 1; i <= 300000; ++i){
		sum[i] = sum[i - 1];
		if (!b[i]) ++sum[i];
	}

	while (scanf("%d", &n)){
		if (n == 0) break;
		printf("%d\n", sum[2 * n] - sum[n]);
	}
	return 0;
}

