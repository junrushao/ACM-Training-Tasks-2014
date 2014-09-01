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
#include <stack>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

int nxtR[21001],nxtL[20101];
int pos[20101];
int a[20101];
int b[200100];
int n,m,t;
stack<int> S;
int chpos,chnum;
bool Valid(int pos,int ch){// need stack
	if(ch==-1) return false;
	if(::pos[b[pos]]>=::pos[ch]) return false;
	if(pos+(int)S.size()>2*n) return false;
	if(b[pos]>m&&ch>m) return false;
	if(b[pos]<=m&&ch<=m){
		return true;
	}
	if(b[pos]<=m&&ch>m) return true;
	if(b[pos]>m&&ch<=m) return true;
	return false;
}
void Construct(int pos){
	for(int i=1;i<=pos;++i){
		if(b[i]>m) S.pop();
		else S.push(b[i]+m);
	}
	for(int i=pos+1;i<=2*n;++i){
		if((int)S.size()+i>2*n|| (!S.empty() && ::pos[S.top()] < ::pos[nxtL[0]])){
			b[i]=S.top();
			S.pop();
		}
		else{
			b[i]=nxtL[0];
			S.push(m+nxtL[0]);
		}
	}
}
int main() {
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=2*m;++i){
			int x;
			scanf("%d",&x);
			if(x<0) x=-x+m;
			a[i]=x;
			pos[x]=i;
		}
		nxtL[a[2*m]]=nxtR[a[2*m]]=-1;
		for(int i=2*m-1;i>=0;--i){
			nxtL[a[i]]=nxtL[a[i+1]];
			nxtR[a[i]]=nxtR[a[i+1]];
			if(a[i+1]>m) nxtR[a[i]]=a[i+1];
			else nxtL[a[i]]=a[i+1];
		}
		for(int i=1;i<=2*n;++i){
			scanf("%d",b+i);
			if(b[i]<0) b[i]=-b[i]+m;
		}
		chpos=-1;
		for(int i=1;i<=2*n;++i){
			if(Valid(i,nxtL[b[i]])){
				chpos=i,chnum=nxtL[b[i]];
			}
			if(!S.empty()&&Valid(i,S.top())){
				if(chpos!=i) chpos=i,chnum=S.top();
				else if(pos[chnum]>pos[S.top()]){
					chnum=S.top();
				}
			}
			if(b[i]>m) S.pop();
			else S.push(b[i]+m);
		}
		if(chpos==-1){
			Construct(0);
		}
		else{
			b[chpos]=chnum;
			Construct(chpos);
		}
		for(int i=1;i<=2*n;++i){
			printf("%d%c",b[i]<=m?b[i]:-(b[i]-m),i==2*n?'\n':' ');
		}
	}
	return 0;
}
