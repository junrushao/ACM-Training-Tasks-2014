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

int T;
int n,m;
struct edge{
	int t,c;edge *nxt;
	void init(int _s,int _t,int _c);
}e[101000],*pe,*v[50101];
void edge::init(int _s,int _t,int _c){
	t=_t,c=_c,nxt=v[_s],v[_s]=this;
}

int w[50101];
bool in[50101];
LL tw[50101];
LL tl[50101];
LL ans[50101];
void dfs(int x){
	tw[x]=w[x];
	tl[x]=0;
	in[x]=1;
	for(edge *ii=v[x];ii;ii=ii->nxt){
		if(!in[ii->t]){
			dfs(ii->t);
			tw[x]+=tw[ii->t];
			tl[x]+=tw[ii->t]*ii->c+tl[ii->t];
		}
	}
}

void dfs2(int x){
	in[x]=0;
	for(edge *ii=v[x];ii;ii=ii->nxt){
		if(in[ii->t]){
			ans[ii->t]=ans[x]-tw[ii->t]*ii->c+ii->c*(tw[1]-tw[ii->t]);
			dfs2(ii->t);
		}
	}
}
LL anss;
vector<int> out;
int main() {
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		pe=e;
		for(int i=1;i<n;++i){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			pe++->init(x,y,z);
			pe++->init(y,x,z);
		}
		scanf("%d",&m);
		while(m--){
			int x,y;
			scanf("%d%d",&x,&y);
			w[x]+=y;
		}
		dfs(1);
		ans[1]=tl[1];
		//for(int i=1;i<=n;++i) cout<<i<<": "<<w[i]<<" "<<tw[i]<<" "<<tl[i]<<endl;
		dfs2(1);
		anss=ans[1];
		out.clear();
		for(int i=1;i<=n;++i){
			if(anss>ans[i]) anss=ans[i],out.clear();
			if(anss==ans[i]) out.push_back(i);
		}
		printf("%lld\n",anss*2);
		for(int i=0;i<int(out.size());++i){
			printf("%d%c",out[i],i==int(out.size())-1?'\n':' ');
		}
		for(int i=1;i<=n;++i) v[i]=0,w[i]=0;
	}
	return 0;
}
