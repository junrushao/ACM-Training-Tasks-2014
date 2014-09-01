#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define rep(a,b,c) for(int a=b;a<=c;a++)

const int MAXN=30000000;

int N,T;
int ans[MAXN+10];

int main(){
	rep(i,1,MAXN)
		for	(int j=2*i;j<=MAXN;j+=i)
			if	((j&i)==i)	ans[j]++;
	rep(i,1,MAXN)	ans[i]+=ans[i-1];
	cin >>T;
	rep(TT,1,T){
		cin >>N;
		printf("Case %d: %d\n",TT,ans[N]);
	}
}

