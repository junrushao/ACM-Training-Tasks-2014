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

double l,mid,r;
int SP[2001000];
int SN[2001000];
double ST;
int maxv;
int a0,A,B,M,N;

bool check() {
	double delta=mid*SP[N];
	for(int i=N+1;i>=0;--i){
		if(i==N+1) maxv=N+1,ST=2*SP[i]-mid*SN[i];
		else{
			double STnow=2*SP[i]-mid*SN[i];
			if(STnow+delta<=ST){
				//return true;
				return mid=2.0*(SP[maxv]-SP[i])/(SP[N+1]+SN[maxv]-SN[i]),true;
			}
			if(STnow>ST) ST=STnow,maxv=i;
		}
	}
	return false;
}

int main() {
	while(scanf("%d",&N)==1){
		scanf("%d%d%d%d",&a0,&A,&B,&M);
		for(int i=1;i<=N+1;++i){
			SP[i]=a0+SP[i-1];
			a0=(A*a0+B)%M;
			SN[i]=a0+SN[i-1];
			a0=(A*a0+B)%M;
		}
		for(int i=1;i<=N+1;++i) SN[i]+=SP[i];
		if(1&&SP[N+1]==0){
			printf("%.6f\n",1.0);
			continue;
		}
		int H=min(N+1,200);
		int T=min(N+1,200);
		double ans=0;
		for(int i=0;i<=H;++i){
			for(int j=i+1;j<=H;++j){
				ans=max(2.0*(SP[j]-SP[i])/(SP[N+1]+SN[j]-SN[i]),ans);
			}
			for(int j=max(i+1,N+1-T);j<=N+1;++j){
				ans=max(2.0*(SP[j]-SP[i])/(SP[N+1]+SN[j]-SN[i]),ans);
			}
		}
		printf("%.6f\n",ans);
	}
	return 0;
}
