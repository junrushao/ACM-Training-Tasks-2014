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

int maxopt;
const int mod=1000000007;
map<int,int> DP[22][22];
int N,K,L,T;
int ans;
int Pow[22];

LL C[22][22];
LL P[22];

void Add(int &x,LL y){
	if(y>=mod) y%=mod;
	x+=y;
	if(x>=mod) x-=mod;
}

LL total;

int main() {
	for(int i=0;i<=20;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j){
			C[i][j]=C[i-1][j]+C[i-1][j-1];
			if(C[i][j]>=mod) C[i][j]-=mod;
		}
	}
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&N,&K,&L);
		int lim=min(K,L);
		P[0]=1;
		P[1]=L+1-lim;
		for(int i=2;i<=N;++i){
			P[i]=P[i-1]*P[1];
			if(P[i]>=mod) P[i]%=mod;
		}
		for(int i=0;i<=lim+1;++i) for(int j=0;j<=N;++j) DP[i][j].clear();
		DP[1][N].insert(make_pair(1,1));
		maxopt=(1<<(K+1))-1;
		for(int i=1;i<=lim;++i){
			for(int j=0;j<=N;++j){
				for(map<int,int>::iterator iter=DP[i][j].begin();iter!=DP[i][j].end();++iter){
					int opt=iter->first,add=iter->second;
					for(int k=0;k<=j;++k){
						Add(DP[i+1][j-k][opt&(maxopt>>(i+1))],add*C[j][k]);
						opt=(opt|(opt<<i))&maxopt;
						if(opt&(1<<K)) break;
					}
				}
			}
		}
		ans=0;
		for(int i=lim+1;i<=lim+1;++i) for(int j=0;j<=N;++j){
			int sum=0;
			for(map<int,int>::iterator iter=DP[i][j].begin();iter!=DP[i][j].end();++iter){
				Add(sum,iter->second);
			}
			Add(ans,sum*P[j]);
		}
		total=1;
		for(int i=1;i<=N;++i){
			total*=L+1;
			if(total>=mod) total%=mod;
		}
		ans=total-ans;
		if(ans<0) ans+=mod;
		printf("%d\n",ans);
	}
	return 0;
}
