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

struct node{
	int a,b,id;
	int sta,stb;
	bool ch;
}p[10101];

int lena,lenb,n;
int suma,sumb,maxab,lim;

bool cmpsum(const node &a,const node &b){
	return a.a+a.b>b.a+b.b;
}
bool cmpid(const node &a,const node &b){
	return a.id<b.id;
}
bool intersect(int a,int b,int c,int d){
	return !(a>=d)&&!(c>=b);
}
bool dfs(int sa,int ta,int sb,int tb,int i){
	if(i==n+1) return true;
	if(p[i].ch){
		return dfs(sa,ta,sb,tb,i+1);
	}
	if(p[i].a>p[i].b){
		if(!intersect(sa,sa+p[i].a,sb,sb+p[i].b)){
			p[i].sta=sa,p[i].stb=sb;
			if(dfs(sa+p[i].a,ta,sb+p[i].b,tb,i+1)) return true;
		}
		if(!intersect(ta-p[i].a,ta,tb-p[i].b,tb)){
			p[i].sta=ta-p[i].a,p[i].stb=tb-p[i].b;
			if(dfs(sa,ta-p[i].a,sb,tb-p[i].b,i+1)) return true;
		}
	}
	else{
		if(!intersect(ta-p[i].a,ta,tb-p[i].b,tb)){
			p[i].sta=ta-p[i].a,p[i].stb=tb-p[i].b;
			if(dfs(sa,ta-p[i].a,sb,tb-p[i].b,i+1)) return true;
		}
		if(!intersect(sa,sa+p[i].a,sb,sb+p[i].b)){
			p[i].sta=sa,p[i].stb=sb;
			if(dfs(sa+p[i].a,ta,sb+p[i].b,tb,i+1)) return true;
		}
	}
	return false;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&p[i].a,&p[i].b);
		suma+=p[i].a;
		sumb+=p[i].b;
		p[i].id=i;
		p[i].ch=0;
		maxab=max(maxab,p[i].a+p[i].b);
	}
	{
		lim=max(max(suma,sumb),maxab);
		sort(p+1,p+n+1,cmpsum);
		for(int i=1;i<=n;++i){
			if(lena+lenb+p[i].a+p[i].b<=lim){
				p[i].ch=1;
				lena+=p[i].a,lenb+=p[i].b;
			}
		}
		if(!dfs(lena,lim,0,lim-lenb,1)){
			vector<int> C;
			while(1) C.push_back(1);
			printf("%d\n",(int)C.size());
		}
		lena=0,lenb=lim-lenb;
		for(int i=1;i<=n;++i) if(p[i].ch){
			p[i].sta=lena;
			lena+=p[i].a;
			p[i].stb=lenb;
			lenb+=p[i].b;
		}
		printf("%d\n",lim);
		sort(p+1,p+n+1,cmpid);
		for(int i=1;i<=n;++i) printf("%d %d\n",p[i].sta,p[i].stb);
	}
	return 0;
}
