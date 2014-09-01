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

void solve() {
}

int dp[2011][2011];
int T,N,S,W,M;

struct th{
	int p,w,v;
	void init(){scanf("%d%d%d",&p,&w,&v);}
}P[1001];

inline int getCount(const th &x){
	if(x.w==0) return W+M/x.p;
	else return W/x.w;
}

bool cmp(const th &x,const th &y){
	return x.w>y.w||(x.w==y.w&&x.p>y.p);
}

LL ans[5];

inline void Update(int &x,int y){
	if(x<y) x=y;
}

int main() {
	scanf("%d",&T);
	for(int tt=1;tt<=T;++tt){
		scanf("%d%d%d%d",&N,&S,&W,&M);
		//N=1000,S=1000000000,W=1000,M=1;
		bool flag=W>M;
		if(flag) swap(W,M);
		for(int i=1;i<=N;++i){
			P[i].init();
			//P[i].p=rand()%10;
			//P[i].w=rand()%10+1;
			//P[i].v=rand()%1000000;
			if(flag) swap(P[i].p,P[i].w);
		}
		sort(P+1,P+N+1,cmp);
		memset(dp,128,sizeof(dp));
		dp[0][0]=0;
		for(int i=1;i<=N;){
			int maxv=P[i].v;
			int j=i+1;
			while(j<=N&&P[i].p==P[j].p&&P[i].w==P[j].w){
				maxv=max(maxv,P[j].v);
				++j;
			}
			if(P[i].p==0&&P[i].w==0){
				break;
			}
			int limit=getCount(P[i]);
			for(int ii=0;ii<=W-P[i].w;++ii){
				for(int jj=0;jj<=M-P[i].p;++jj){
					for(int kk=0;kk<=limit;++kk) if(dp[ii*(M+1)+jj][kk]>=0){
						Update(dp[(ii+P[i].w)*(M+1)+(jj+P[i].p)][kk+1],dp[ii*(M+1)+jj][kk]+maxv);
					}
				}
			}
			i=j;
		}
		{
			int maxv=-1;
			for(int i=1;i<=N;++i) if(P[i].p==0&&P[i].w==0) maxv=max(P[i].v,maxv);
			ans[1]=ans[2]=ans[3]=0;
			if(maxv!=-1){
				ans[0]=S;
			}
			else ans[0]=0;
			{
				
				for(int i=0;i<=W;++i) for(int j=0;j<=M;++j) for(int k=0;k<=(W+M)&&k<=S;++k) if(dp[i*(M+1)+j][k]>=0){
					ans[0]=max(ans[0],LL(k));
					ans[1]=max(ans[1],LL(j));
					ans[2]=max(ans[2],LL(i));
				}
			}
			maxv=max(maxv,0);
			for(int i=0;i<=W;++i){
				for(int j=0;j<=M;++j){
					for(int k=0;k<=W+M&&k<=S;++k) if(dp[i*(M+1)+j][k]>=0) {
						ans[3]=max(ans[3],dp[i*(M+1)+j][k]+(LL)(S-k)*maxv);
					}
				}
			}
		}
		if(flag) swap(ans[1],ans[2]);
		cout<<"Case "<<tt<<": "<<ans[0]<<" "<<ans[1]<<" "<<ans[2]<<" "<<ans[3]<<endl;
	}
	return 0;
}
