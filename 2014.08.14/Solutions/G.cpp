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

map<LL,int> DP[14][14];
int T;
int N,K,L;
LL F[14];
LL powL[300];
LL C[14][14];
const int mod=1000000007;
void Add(int &x,LL y){
	if(y>=mod) y%=mod;
	x+=y;
	if(x>=mod) x-=mod;
}
int ans;
LL Pow(LL x,LL y){
	LL res=1;
	while(y){
		if(y&1){
			res*=x;
			if(res>=mod) res%=mod;
		}
		x*=x;
		if(x>=mod) x%=mod;
		y>>=1;
	}
	return res;
}
int main() {
	for(int i=0;i<=13;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j){
			C[i][j]=C[i-1][j]+C[i-1][j-1];
			if(C[i][j]>=mod) C[i][j]-=mod;
		}
	}
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&N,&K,&L);
		powL[0]=1;
		for(int i=1;i<=N*N;++i){
			powL[i]=powL[i-1]*L;
			if(powL[i]>=mod) powL[i]%=mod;
		}
		int lim=K-1;
		for(int i=0;i<=lim+1;++i){
			for(int j=0;j<=N;++j) DP[i][j].clear();
		}
		DP[1][0][0]=1;
		for(int i=1;i<=lim;++i){
			for(int j=0;j<=N-2;++j){
				for(map<LL,int>::iterator iter=DP[i][j].begin();iter!=DP[i][j].end();++iter) if(iter->second){
					LL now=iter->first;
					for(int k=0;k<=j;++k){
						F[k]=now%13;
						now/=13;
					}
					LL method=1;
					LL decmethod=1;
					for(int k=0;k<=j;++k){
						method*=max(0LL,L+1-(i-F[k]));
						decmethod*=max(0LL,L-(i-F[k]));
						if(method>=mod) method%=mod;
						if(decmethod>=mod) decmethod%=mod;
					}
					method-=decmethod;
					if(method<0) method+=mod;
					now=iter->first;
					LL nowmethod=iter->second;
					for(int k=j;k<=N-2;++k){
						Add(DP[i+1][k][now],nowmethod*C[N-2-j][k-j]%mod*powL[(k-j)*(k-j-1)/2]);
						nowmethod*=method;
						if(nowmethod>=mod) nowmethod%=mod;
						now=now*13+i;
					}
				}
			}
		}
		ans=0;
		for(int j=0;j<=N-2;++j){
			for(map<LL,int>::iterator iter=DP[lim+1][j].begin();iter!=DP[lim+1][j].end();++iter) if(iter->second){
				LL now=iter->first;
				for(int k=0;k<=j;++k){
					F[k]=now%13;
					now/=13;
				}
				LL method=1;
				LL decmethod=1;
				for(int k=0;k<=j;++k){
					method*=max(0LL,L+1-(lim+1-F[k]));
					decmethod*=max(0LL,L-(lim+1-F[k]));
					if(method>=mod) method%=mod;
					if(decmethod>=mod) decmethod%=mod;
				}
				decmethod=method-decmethod;
				if(decmethod<0) decmethod+=mod;
				Add(ans,iter->second*decmethod%mod*Pow(method,N-2-j)%mod*powL[(N-1-j)*(N-2-j)/2]);
			}
		}
		printf("%d\n",ans);
	}
}
