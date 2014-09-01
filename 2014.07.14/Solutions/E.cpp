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

LL dp[2][4001];
short pre[9000001];
const LL inf = 0x7f7f7f7f7f7f7f7fLL;
int n,m;
pair<int,int> a[4001];
pair<int,int> b[4001];

inline int Abs(int x){
	return x<0?-x:x;
}

int ans[4001];
int T;

int main() {
	ios::sync_with_stdio(false);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i) scanf("%d",&a[i].first),a[i].second=i;
		scanf("%d",&m);
		for(int i=1;i<=m;++i) scanf("%d",&b[i].first),b[i].second=i;
		sort(a+1,a+n+1);
		sort(b+1,b+m+1);
		for(int i=0;i<2;++i) for(int j=0;j<=m;++j) dp[i][j]=inf;
		int n1=1,n2=0;
		dp[1][1]=Abs(a[1].first-b[1].first);
		for(int i=1;i<n;n1^=1,n2^=1,++i) for(int j=1;j<=m;++j) if(dp[n1][j]!=inf){
			if(j!=m){
				if(dp[n2][j+1]>dp[n1][j]+Abs(a[i+1].first-b[j+1].first)){
					dp[n2][j+1]=dp[n1][j]+Abs(a[i+1].first-b[j+1].first);
					pre[(i+1)*i/2+j+1]=j;
				}
			}
			if(dp[n2][j]>dp[n1][j]+Abs(a[i+1].first-b[j].first)){
				dp[n2][j]=dp[n1][j]+Abs(a[i+1].first-b[j].first);
				pre[(i+1)*i/2+j]=j;
			}
			dp[n1][j]=inf;
		}
		cout<<dp[n1][m]<<endl;
		{
			int now=m;
			for(int i=n;i;--i){
				ans[a[i].second]=b[now].second;
				now=pre[i*(i-1)/2+now];
			}
		}
		for(int i=1;i<=n;++i) cout<<ans[i]<<(i!=n?" ":"\n");
	}
	return 0;
}
