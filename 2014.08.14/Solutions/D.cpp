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
#include <bitset>
#include <queue>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

int T,N,K;

long double C[311][311];
bitset<311> B[311][311];
long double ans[311][311];
int rk[311][311];

struct edge{
	int t;edge *nxt;
	void init(const int _s,const int _t);
}e[601],*v[301],*pe;

void edge::init(const int _s,const int _t){
	t=_t,nxt=v[_s],v[_s]=this;
}

int val[311];
int la[311];
int cnt[311];
bool in[311];
pair<int,int> P[311];

bool cmp(const pair<int,int> &a,const pair<int,int> &b){
	return a.first<b.first||(a.first==b.first&&a.second>b.second);
}

queue<int> Q;

void bfs(int x){
	for(int i=1;i<=N;++i) in[i]=0;
	P[x]=make_pair(0,x);
	Q.push(x);
	in[x]=1;
	while(!Q.empty()){
		int y=Q.front();
		Q.pop();
		for(edge *ii=v[y];ii;ii=ii->nxt) if(!in[ii->t]){
			in[ii->t]=1;
			Q.push(ii->t);
			P[ii->t]=make_pair(P[y].first+1,ii->t);
		}
	}
	sort(P+1,P+N+1,cmp);
	for(int i=1;i<=N;++i){
		rk[x][P[i].second]=i;
	}
	for(int i=2;i<=N;++i){
		B[x][i]=B[x][i-1];
		B[x][i][P[i-1].second]=1;
	}
}
long double out;
int now,stpos;
void dfs(int x){
	in[x]=1;
	if(cnt[la[x]]++==0) ++now;
	out+=now*ans[stpos][x];
	for(edge *ii=v[x];ii;ii=ii->nxt) if(!in[ii->t]){
		dfs(ii->t);
	}
	if(--cnt[la[x]]==0) --now;
}

int main() {
	for(int i=0;i<=300;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j) C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&N,&K);
		pe=e;
		for(int i=1;i<=N;++i){
			v[i]=0;
			for(int j=1;j<=N;++j){
				B[i][j].reset();
			}
		}
		for(int i=1;i<N;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			pe++->init(x,y);
			pe++->init(y,x);
		}
		for(int i=1;i<=N;++i){
			scanf("%d",la+i);val[i]=la[i];
		}
		{
			sort(val+1,val+N+1);
			int tot=unique(val+1,val+N+1)-val-1;
			for(int i=1;i<=N;++i){
				la[i]=lower_bound(val+1,val+tot+1,la[i])-val;
			}
		}
		for(int i=1;i<=N;++i){
			bfs(i);
		}
		for(int i=1;i<=N;++i) for(int j=1;j<=N;++j) if(i!=j){
			int v=(B[i][rk[i][j]]&B[j][rk[j][i]]).count();
			ans[i][j]=C[v][K-2];
		}
		out=0;
		for(int i=1;i<=N;++i){
			memset(in,0,sizeof(in));
			now=0;
			stpos=i;
			dfs(i);
		}
		cout<<fixed<<setprecision(10)<<out/2/C[N][K]<<endl;
	}
	return 0;
}
