#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;
#define rep(a,b,c) for(int a=b;a<=c;a++)

int T,a,b,c;

int main(){
	scanf("%d",&T);
	while	(T){
		ll ans=0,vol=0;
		rep(i,1,T){
			scanf("%d%d%d",&a,&b,&c);
			if	(c==ans)	vol=max(vol,ll(a)*b*c);
			if	(c>ans)	ans=c,vol=ll(a)*b*c;
		}
		cout <<vol <<endl;
		scanf("%d",&T);
	}
}

