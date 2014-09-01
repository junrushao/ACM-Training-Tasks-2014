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

struct edge{
	int t;edge *nxt;
	void init(const int _s,const int _t);
}*v[50101],*pe,e[100101];
int T,n;
int val[50101];
int D[50101];
void edge::init(const int _s,const int _t){
	t=_t,nxt=v[_s],v[_s]=this;
}

int tree[2],ring;

bool in[50101];
int Q[50101],HH,TT;
bool bfs(int x){
	in[x]=1;
	HH=TT=-1;
	Q[++TT]=x;
	int cntM=0;
	while(HH++!=TT){
		int x=Q[HH];
		cntM+=D[x];
		for(edge *ii=v[x];ii;ii=ii->nxt){
			if(!in[ii->t]){
				in[ii->t]=1;
				Q[++TT]=ii->t;
			}
		}
	}
	int cntN=TT+1;
	cntM/=2;
	if(cntN<cntM){
		return false;
	}
	if(cntN==cntM){
		for(int i=0;i<=TT;++i){
			int x=Q[i];
			if(ring==-1||x<ring) ring=x;
		}
	}
	else if(cntN==cntM+1){
		for(int i=0;i<=TT;++i){
			int x=Q[i];
			if(tree[1]==-1||(val[tree[1]]<val[x])||(val[tree[1]]==val[x]&&tree[1]>x)) tree[1]=x;
			if(tree[0]==-1||(val[tree[0]]<val[tree[1]])||(val[tree[0]]==val[tree[1]]&&tree[0]>tree[1])){
				swap(tree[0],tree[1]);
			}
		}
	}
	return 1;
}

void check(){
	tree[0]=tree[1]=-1,ring=-1;
	for(int i=1;i<=n;++i) if(!in[i]){
		if(!bfs(i)){
			printf("impossible\n");
			return;
		}
	}
	if(tree[0]!=-1&&tree[1]!=-1&&ring!=-1&&val[tree[0]]==val[tree[1]]){
		if(ring<tree[1]){
			tree[1]=ring;
		}
		printf("%d %d\n",min(tree[0],tree[1]),max(tree[1],tree[0]));
		return;
	}
	if(ring!=-1){
		printf("%d %d\n",min(tree[0],ring),max(ring,tree[0]));
	}
	else printf("%d %d\n",min(tree[0],tree[1]),max(tree[1],tree[0]));
}

int main() {
	scanf("%d",&T);
	while(T--){
		pe=e;
		scanf("%d",&n);
		for(int i=1;i<n;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			++D[x],++D[y];
			pe++->init(x,y);
			pe++->init(y,x);
		}
		for(int i=1;i<=n;++i) scanf("%d",val+i);
		check();
		for(int i=1;i<=n;++i) v[i]=0,D[i]=0,in[i]=0;
	}
	return 0;
}
