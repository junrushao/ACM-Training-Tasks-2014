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

int F[20];

char s[21];
int ss[21];
int T,M;

int nxt[65570][5];

int ch(char c){
	if(c=='A') return 0;
	else if(c=='C') return 1;
	else if(c=='G') return 2;
	else if(c=='T') return 3;
	return 4;
}

const int mod=1000000007;

int dp[2][65570];
int cnt[65570];
int ans[20];

void Add(int &x,int y){
	x+=y;
	if(x>=mod) x-=mod;
}

int main() {
	for(int i=1;i<65536;++i) cnt[i]=cnt[i^(i&-i)]+1;
	scanf("%d",&T);
	while(T--){
		scanf("%s%d",s+1,&M);
		int len=strlen(s+1);
		for(int i=1;i<=len;++i) ss[i]=ch(s[i]);
		for(int i=0;i<(1<<len);++i){
			for(int j=0;j<4;++j){
				for(int k=1;k<=len;++k)
					F[k]=F[k-1]+((i>>(k-1))&1);
				for(int k=len;k;--k){
					if(ss[k]==j){
						F[k]=F[k-1]+1;
					}
				}
				for(int k=1;k<=len;++k) F[k]=max(F[k],F[k-1]);
				int now=0;
				for(int k=len;k;--k) now=(now<<1)|(F[k]-F[k-1]);
				nxt[i][j]=now;
			}
		}
		dp[0][0]=1;
		int n1=0,n2=1;
		for(int i=1;i<=M;++i){
			for(int j=0;j<(1<<len);++j) if(dp[n1][j]){
				for(int k=0;k<4;++k){
					Add(dp[n2][nxt[j][k]],dp[n1][j]);
				}
				dp[n1][j]=0;
			}
			swap(n1,n2);
		}
		for(int i=0;i<(1<<len);++i) if(dp[n1][i]){
			Add(ans[cnt[i]],dp[n1][i]);
			dp[n1][i]=0;
		}
		for(int i=0;i<=len;++i) printf("%d\n",ans[i]),ans[i]=0;
	}
	return 0;
}
