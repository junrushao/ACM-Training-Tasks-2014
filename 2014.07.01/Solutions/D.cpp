#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long long ll;
using namespace std;
#define rep(a,b,c) for(ll a=b;a<=c;a++)

const ll MO=10000000000007;

int T;
ll L,M,N;

ll calc(ll n,ll m){
	ll res=1;
	rep(i,n-m+1,n)	res=(res*i)%MO+1;
	res%=MO;
	return	res;
}

int main(){
	scanf("%d",&T);
	rep(TT,1,T){
		cin >>L >>M >>N;
		ll ans=(calc(L*L,N)-calc(L*L,M-1))%MO;
		ans=(ans+MO)%MO;
		cout <<"Case " <<TT <<": " <<ans <<endl;
	}
}

