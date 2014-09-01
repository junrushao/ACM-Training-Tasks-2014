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

int dp[1048580];
int N;
int main() {
	while(scanf("%d",&N)==1&&N>0){
		while(N--){
			int x,y;
			scanf("%d%d",&x,&y);
			dp[x]+=y;
		}
		for(int i=1;i<1048580;i<<=1){
			for(int j=0;j<1048576;++j){
				if(j&i) dp[j]+=dp[j^i];
			}
		}
		int ans=dp[0];
		for(int i=0;i<1048576;++i){
			ans=max(ans,dp[i]);
			dp[i]=0;
		}
		printf("%d\n",ans);
	}
	return 0;
}
