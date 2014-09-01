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

int n,m;
bool af[37][37];
bool con[37][37];
const int mod=1000000007;
LL C[37][37];
LL vis;
LL connect[37];
int concnt[37];
int dp[524290];
int afdp[20];
vector<int> V;
void Add(int &x,int y){
	x+=y;
	if(x>=mod) x-=mod;
}
int Calcans(LL bitmask){
	V.clear();
	for(int i=1;i<=n;++i) if((1LL<<(i-1))&bitmask){
		V.push_back(i);
	}
	for(int i=0;i<(int)V.size();++i){
		afdp[i]=0;
		for(int j=0;j<(int)V.size();++j) if(af[V[i]][V[j]]){
			afdp[i]|=1<<j;
		}
	}
	dp[0]=1;
	for(int i=0;i<(1<<(V.size()))-1;++i) if(dp[i]){
		for(int j=0;j<(int)V.size();++j) if(~i&(1<<j)){
			if((afdp[j]&i)==afdp[j]){
				Add(dp[i|(1<<j)],dp[i]);
			}
		}
		dp[i]=0;
	}
	int ret=dp[(1<<(V.size()))-1];
	dp[(1<<(V.size()))-1]=0;
	return ret;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;++i){
		C[i][0]=1;
		con[i][i]=1;
		for(int j=1;j<=n;++j){
			C[i][j]=C[i-1][j]+C[i-1][j-1];
			if(C[i][j]>=mod) C[i][j]-=mod;
		}
	}
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		af[x][y]=1;
		con[x][y]=con[y][x]=1;
	}
	for(int k=1;k<=n;++k) for(int i=1;i<=n;++i) for(int j=1;j<=n;++j){
		af[i][j]|=af[i][k]&&af[k][j];
		con[i][j]|=con[i][k]&&con[k][j];
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(con[i][j]){
				++concnt[i];
				connect[i]|=1LL<<(j-1);
			}
		}
	}
	vis=(1LL<<n)-1;
	int nowcnt=n;
	LL ans=1;
	for(int i=1;i<=n;++i) if(vis&(1LL<<(i-1))){
		ans=ans*C[nowcnt][concnt[i]]%mod*Calcans(connect[i]);
		if(ans>=mod) ans%=mod;
		nowcnt-=concnt[i];
		vis^=connect[i];
	}
	printf("%d\n",int(ans));
	return 0;
}
