#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

LL dp[5001];
const int mod=1000000007;
int n;

int main() {
	for(int i=1;i<=5000;++i){
		LL now=1;
		for(int j=i-1;j>=1;--j){
			now*=i;
			if(now>=mod) now%=mod;
			dp[i]+=dp[j]*now;
			if(dp[i]>=mod) dp[i]%=mod;
		}
		now*=i;
		if(now>=mod) now%=mod;
		dp[i]=now-dp[i];
		if(dp[i]<0) dp[i]+=mod;
	}
	scanf("%d",&n);
	printf("%d\n",(int)dp[n]);
	return 0;
}
