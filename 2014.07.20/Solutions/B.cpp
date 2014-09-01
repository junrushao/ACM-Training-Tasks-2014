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

map<LL,int> Map;

int bt[2000000],*t[20];
int T,M;
LL delta;

void Ins(int *t,int x,int add,int maxlen){
	++x;
	while(x<=maxlen){
		t[x]+=add;
		x+=x&-x;
	}
}

int calc(int *t,int x,int y){
	int ans=0;
	--x;
	while(y){
		ans+=t[y],y^=y&-y;
	}
	while(x){
		ans-=t[x],x^=x&-x;
	}
	return ans;
}

int Query(int *t,int l,int r,int delta,int maxlen){
//	printf("%d %d %d %d\n",l,r,delta,maxlen);
//	for(int i=1;i<=maxlen;++i) printf("%d ",t[i]);
//	printf("\n");
	if(delta>(maxlen>>1)){
		return t[maxlen]-calc(t,l-(delta-(maxlen>>1)),r-(delta-(maxlen>>1)));
	}
	else return calc(t,l-delta,r-delta);
}

int main() {
	{
		int *nt=bt;
		for(int i=17;i>=0;--i){
			t[i]=nt;
			nt+=(1<<(i+1))+10;
		}
	}
	scanf("%d",&T);
	for(int tt=1;tt<=T;++tt){
		printf("Case %d:\n",tt);
		Map.clear();
		memset(bt,0,sizeof(bt));
		delta=0;
		scanf("%d",&M);
		while(M--){
			static char s[10];
			static LL x;
			static int xxxxx;
			scanf("%s%d",s,&xxxxx);
			x=xxxxx;
			if(s[2]=='S'){//ins
				x-=delta;
				++Map[x];
				for(int i=0;i<=17;++i) Ins(t[i],int(x&((1<<(i+1))-1)),1,1<<(i+1));
			}
			else if(s[2]=='L'){//del
				x-=delta;
				map<LL,int>::iterator iter=Map.find(x);
				if(iter!=Map.end()){
					int y=iter->second;
					Map.erase(iter);
					for(int i=0;i<=17;++i) Ins(t[i],int(x&((1<<(i+1))-1)),-y,1<<(i+1));
				}
				else{
					printf("Del error\n");
				}
			}
			else if(s[2]=='D'){//add
				delta+=x;
			}
			else if(s[2]=='B'){//sub
				if(!Map.size()||Map.begin()->first+delta-x>=0){
					delta-=x;
				}
				else printf("Sub error\n");
			}
			else if(s[2]=='U'){//qnum
				x-=delta;
				if(Map.count(x)){
					printf("%d\n",Map[x]);
				}
				else printf("0\n");
			}
			else{//qbit
				printf("%d\n",Query(t[x],(1<<x)+1,1<<(x+1),int(delta&((1<<(x+1))-1)),1<<(x+1)));
			}
		}
		printf("\n");
	}
	return 0;
}
