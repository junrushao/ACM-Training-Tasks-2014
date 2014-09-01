#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

#define rep(a,b,c) for(int a=b;a<=c;a++)

typedef long long ll;

const ll MO=1000000007ll;

int T;
vector<int> pr;
ll got[1010];
ll n,k,ans1,ans2;

int main(){
	scanf("%d",&T);
	pr.clear();
	rep(i,2,1000){
		bool ff=0;
		rep(j,2,i/2)	if	(i%j==0)	ff=1;
		if	(!ff)	pr.push_back(i);
	}
	rep(TT,1,T){
		cin >>n >>k;
		memset(got,0,sizeof got);
		rep(j,0,pr.size()-1){
			ll cur=n;
			while	(cur/pr[j]){
				cur/=pr[j];
				got[j]+=cur;
			}
		}
		ans1=ans2=1;
		rep(j,0,pr.size()-1){
			ans1=ans1*(got[j]/k+1)%MO;
			ans2=ans2*(got[j]/(k+1)+1)%MO;
		}
		//cout <<ans1 << " " <<ans2 <<endl;
		ans1=(ans1-ans2)%MO;
		ans1=(ans1+MO)%MO;
		cout <<"Case " <<TT <<": " <<ans1 <<endl;
	}
}

