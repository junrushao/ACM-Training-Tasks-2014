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

int a,b,c,d;
const int maxPre=200000;
LL prework[maxPre+10];

vector<pair<int,int> > V;

int main(){
	for(int i=2;i<=maxPre;++i){
		prework[i]=1;
		for(int j=2;j*j<=i;++j) if(i%j==0){
			int k=0;
			int l=i;
			while(l%j==0) l/=j,++k;
			if(l==1) prework[i]+=prework[k];
		}
	}
	while(scanf("%d^%d^%d ",&a,&b,&c)==3){
		if(a==1){
			printf("0\n");
			continue;
		}
		d=1;
		for(int i=2;i*i<=a;++i){
			int cnt=0,now=1;
			while(now<a){
				++cnt,now*=i;
			}
			if(now==a){
				d=cnt;
				a=i;
				break;
			}
		}
		//(a^d)^(b^c)
		V.clear();
		if(d!=1){
			for(int i=2;i*i<=d;++i){
				if(d%i==0){
					int cnt=0;
					while(d%i==0){
						++cnt,d/=i;
					}
					V.push_back(make_pair(i,cnt));
				}
			}
			if(d!=1) V.push_back(make_pair(d,1));
		}
		for(int i=0;i<int(V.size());++i){
			while(b%V[i].first==0){
				b/=V[i].first;
				V[i].second+=c;
			}
		}
		for(int i=2;i*i<=b;++i){
			if(b%i==0){
				int cnt=0;
				while(b%i==0) b/=i,cnt+=c;
				V.push_back(make_pair(i,cnt));
			}
		}
		if(b!=1) V.push_back(make_pair(b,c));
		int maxv=0;
		for(int i=0;i<(int)V.size();++i) maxv=max(maxv,V[i].second);
		LL ans=0;
		for(int i=2;i<=maxv;++i){
			LL cnt=1;
			for(int j=0;j<(int)V.size();++j) cnt*=V[j].second/i+1;
			--cnt;
			ans+=cnt*prework[i];
		}
		printf("%lld\n",ans);
	}
	return 0;
}