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

void solve() {
}

int f[4101];
LL dp[4101];
LL ans;
int T;
int K,M;
int main() {
	f[0]=f[1]=1;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&K,&M);
		for(int i=2;i<=K;++i){
			f[i]=f[i-1]+f[i-2];
			if(f[i]>=M) f[i]-=M;
		}
		for(int i=1;i<=K;++i){
			int x;
			scanf("%d",&x);
			dp[i]=x;	
		}
		ans=0;
		for(int i=1;i<=K;++i){
		//	printf("%d %d\n",f[i],(int)dp[K+1-i]);
			ans+=f[i]*dp[K+1-i];
			if(ans>=M) ans%=M;
			for(int j=1;j<K+1-i;++j){
				dp[j]=dp[j+1]-dp[j]*f[i];
				dp[j]%=M;
				if(dp[j]<0) dp[j]+=M;
			}
		}
		printf("%d\n",(int)ans);
	}
	return 0;
}

