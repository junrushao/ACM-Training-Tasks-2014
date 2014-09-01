#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

#define MO 1000003ll
#define rep(a,b,c) for(ll a=b;a<=c;a++)

ll A,B,X,Y,Z;
ll fc[MO+10],inv[MO+10],pw[4][MO+10];
int T;

inline ll inverse(ll a){
	return	(a==1)?(1):((MO-MO/a)*(inverse(MO%a))%MO);
}

ll solve(ll A,ll B){
	if	(A==0 && B==0)	return	1;
	ll a=A%MO,b=B%MO,ret=0;
	rep(i,max(0ll,a+b-MO+1),min(a,b)){
		ret+=fc[a+b-i]*inv[a-i]%MO*inv[b-i]%MO*inv[i]%MO*pw[1][a-i]%MO*pw[2][b-i]%MO*pw[3][i]%MO;
	}
	return	ret*solve(A/MO,B/MO)%MO;
}

int main(){
	fc[0]=1;
	rep(i,1,MO-1)	fc[i]=fc[i-1]*i%MO;
	rep(i,0,MO-1)	inv[i]=inverse(fc[i]);
	scanf("%d",&T);
	rep(TT,1,T){
		cin >>A>>B>>X>>Y>>Z;
		pw[1][0]=pw[2][0]=pw[3][0]=1;
		rep(i,1,MO-1){
			pw[1][i]=pw[1][i-1]*(X%MO)%MO;
			pw[2][i]=pw[2][i-1]*(Y%MO)%MO;
			pw[3][i]=pw[3][i-1]*(Z%MO)%MO;
		}
		cout <<solve(A,B) <<endl;
	}
}

