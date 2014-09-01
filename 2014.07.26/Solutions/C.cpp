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

int sum;
vector<int> cnt;
int t,n,m;
int main() {
	scanf("%d",&t);
	while(t--){
		cnt.clear();
		int sum=0;
		cnt.push_back(sum);
		scanf("%d%d",&m,&n);
		for(int i=1;i<=n;++i){
			int x;
			scanf("%d",&x);
			sum+=x;
			if(sum>=m) sum%=m;
			cnt.push_back(sum);
		}
		sort(cnt.begin(),cnt.end());
		LL ans=0;
		for(int i=0;i<int(cnt.size());){
			int j=i;
			while(j<(int)cnt.size()&&cnt[j]==cnt[i]) ++j;
			ans+=(LL)(j-i)*(j-i-1)/2;
			i=j;
		}
		cout<<ans<<endl;
	}
	return 0;
}
