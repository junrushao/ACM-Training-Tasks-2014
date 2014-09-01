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

int cnt[1001001];
int n,m;

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		int x;
		scanf("%d",&x);
		++cnt[x];
	}
	int now=0,t=0,ans=0;
	for(int i=1;i<=1000000;++i){
		if(cnt[i]*i>m) break;
		if((now+cnt[i])*i>m){
			ans+=cnt[i];
			++t;
			now=cnt[i];
		}
		else now+=cnt[i],ans+=cnt[i];
	}
	if(now) ++t;
	printf("%d %d\n",ans,t);
	return 0;
}
