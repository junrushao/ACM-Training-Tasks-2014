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

const int pp[6] = {
999999937,
999999929,
999999893,
999999883,
999999797,
1000000007
};

LL inv(LL x,LL mod){
	LL y=mod-2;
	LL ans=1;
	while(y){
		if(y&1){
			if((ans*=x)>=mod) ans%=mod;
		}
		if((x*=x)>=mod) x%=mod;
		y>>=1;
	}
	return ans;
}
LL mul(LL x,LL y,LL mod){
	x*=y;
	if(x>=mod) x%=mod;
	return x;
}
LL G[102][102];
int NG[102][102];
LL *F[102];
int n;
LL Gauss(LL mod){
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j){
		G[i][j]=(mod+NG[i][j])%mod;
	}
	for(int i=1;i<=n;++i) F[i]=G[i];
	LL sign=1;
	LL ans=1;
	for(int i=1;i<=n;++i){
		for(int j=i;j<=n;++j){
			if(F[j][i]!=0){
				swap(F[j],F[i]);
				if(j!=i) sign=-sign;
				break;
			}
		}
		if(F[i][i]==0) return 0;
		ans=mul(ans,F[i][i],mod);
		LL d=inv(F[i][i],mod);
		for(int j=i+1;j<=n;++j){
			LL f=mul(d,F[j][i],mod);
			for(int k=i;k<=n;++k){
				F[j][k]-=mul(f,F[i][k],mod);
				if(F[j][k]<0) F[j][k]+=mod;
			}
		}
	}
	return sign?ans:mod-ans;
}

bool check(int val){
	for(int i=0;i<6;++i){
		LL checkval=(val+pp[i])%pp[i];
		if(Gauss(pp[i])!=checkval){
			return false;
		}
	}
	return true;
}

bool isp(int p) {
	for (int i = 2; i * i <= p; i++)
	if (p % i == 0) return false;
	return true;
}

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j)scanf("%d",&NG[i][j]);
	if(check(1)||check(-1)) printf("Death\n");
	else printf("Power of magic saves lives\n");
	return 0;
}
