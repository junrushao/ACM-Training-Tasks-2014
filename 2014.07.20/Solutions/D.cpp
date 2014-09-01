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

int T,N,K;
int inv[101];
int fact[101];
const int mod=1000000007;
int dp[101];
LL Pow(LL x,LL y,LL p){
	LL ans=1;
	x%=p;
	while(y){
		if(y&1){
			ans*=x;
			if(ans>=p) ans%=p;
		}
		x*=x;
		y>>=1;
		if(x>=p) x%=p;
	}
	return ans;
}

void DP(int K){
	memset(dp,0,sizeof(dp));
	dp[N]=1;
	for(int i=1;i<=N;++i){
		if(K%i==0){
			for(int j=1;j<=N;++j){
				LL now=1;
				for(int k=1;k*i<=j;++k){
					now=now*inv[i]%mod*fact[i-1]%mod;
					dp[j-k*i]+=(LL)dp[j]*fact[j]%mod*now%mod*inv[j-k*i]%mod*inv[k]%mod;
					if(dp[j-k*i]>=mod) dp[j-k*i]-=mod;
				}
			}
		}
	}
}
vector<int> show;
int ans;
void dfs(int now,int v,int sign){
	DP(v);
	ans+=sign*dp[0];
	if(ans<0) ans+=mod;
	if(ans>=mod) ans-=mod;
	for(int i=now;i<int(show.size());++i){
		dfs(i+1,v/show[i],-sign);
	}
}
int main() {
	fact[0]=inv[0]=fact[1]=inv[1]=1;
	for(int i=2;i<=100;++i){
		fact[i]=((LL)fact[i-1]*i)%mod;
		inv[i]=Pow(i,mod-2,mod);
	}
	for(int i=1;i<=100;++i) inv[i]=(LL)inv[i-1]*inv[i]%mod;
	scanf("%d",&T);
	for(int tt=1;tt<=T;++tt){
		scanf("%d%d",&N,&K);
		ans=0;
		int W=K;
		show.clear();
		for(int i=2;i*i<=W;++i){
			if(W%i==0){
				show.push_back(i);
				while(W%i==0) W/=i;
			}
		}
		if(W!=1) show.push_back(W);
		dfs(0,K,1);
		printf("Case %d: %d\n",tt,ans);
	}
	return 0;
}
