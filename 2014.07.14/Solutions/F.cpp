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

vector<int> prime;
int la[20010];
vector<int> fact[20010];
int cnt[20010];
int prem[20010];
int pnow[20010];
int invalid;
int T,n,m;
const int stp=10010;
int stpnow[20010];

vector<pair<int,int> > ans;

int main() {
	for(int i=2;i<=10100;i++){
		if(fact[i].size()==0U){
			fact[i].push_back(prime.size());
			la[i]=prime.size();
			prime.push_back(i);
		}
		for(int j=0;j<=la[i];++j){
			if(prime[j]*i>10100) break;
			fact[prime[j]*i]=fact[i];
			fact[prime[j]*i].push_back(j);
			la[prime[j]*i]=j;
		}
	}
	for(int i=2;i<=stp;++i){
		for(int j=0;j<int(fact[i].size());++j){
			++stpnow[fact[i][j]];
		}
	}
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		memset(cnt,0,sizeof(cnt));
		memset(prem,0,sizeof(prem));
		while(n--){
			int x;
			scanf("%d",&x);
			++cnt[x];
		}
		while(m--){
			int x;
			scanf("%d",&x);
			--cnt[x];
		}
		for(int i=10100;i;--i) cnt[i]+=cnt[i+1];
		for(int i=2;i<=10000;++i){
			for(int j=0;j<int(fact[i].size());++j){
				prem[fact[i][j]]+=cnt[i];
			}
		}
		{
			bool flag=0;
			for(int i=0;i<int(prime.size());++i){
				if(prem[i]<0){flag=true;break;}
			}
			if(flag){
				printf("-1\n");
				continue;
			}
		}
		ans.clear();
		invalid=0;
		for(int i=0;i<int(prime.size());++i){
			pnow[i]=stpnow[i];
			invalid+=pnow[i]>prem[i];
		}
		for(int i=stp;i>1;--i){
			if(!invalid){
				int maxd=0;
				for(int j=0;j<int(prime.size());++j){
					if(prime[j]>i) break;
					if(pnow[j]!=0){
						if(maxd==0) maxd=prem[j]/pnow[j];
						else maxd=min(maxd,prem[j]/pnow[j]);
					}
				}
				for(int j=0;j<int(prime.size());++j){
					if(prime[j]>i) break;
					prem[j]-=pnow[j]*maxd;
					invalid+=pnow[j]>prem[j];
				}
				ans.push_back(make_pair(i,maxd));
			}
			for(int j=0;j<int(fact[i].size());++j){
				if(--pnow[fact[i][j]]==prem[fact[i][j]]) --invalid;
			}
		}
		printf("%d\n",int(ans.size()));
		for(int i=0;i<int(ans.size());++i){
			printf("%d %d\n",ans[i].first,ans[i].second);
		}
	}
	return 0;
}

