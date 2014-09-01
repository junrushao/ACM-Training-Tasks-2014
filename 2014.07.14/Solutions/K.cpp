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
#include <cctype>
using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

int n,m,T;

struct edge{
	int t;
	edge *nxt;
	void init(const int _s,const int _t);
}E[200101],*V[10101],*PE;

void edge::init(const int _s,const int _t){
	t=_t,nxt=V[_s],V[_s]=this;
}
bool in[10101];
int color[10101];
int use[10101];
int D[10101];
int Q[10101],QT;
int cntuse;

void dfs(int x){
	in[x]=1;
	for(edge *ii=V[x];ii;ii=ii->nxt){
		if(!in[ii->t]) dfs(ii->t);
	}
	Q[++QT]=x;
}

inline void Read(int &x){
	x=0;
	register int y=0;
	while(isdigit(y=getchar())) x=x*10+y-'0';
}

int main() {
	Read(T);
	while(T--){
		Read(n),Read(m);
		QT=0;
		PE=E;
		while(m--){
			int x,y;
			Read(x),Read(y);
			PE++->init(x,y);
			PE++->init(y,x);
			++D[x],++D[y];
		}
		int maxc=0;
		{
			int choose;
			for(int i=1;i<=n;++i){
				if(~D[i]&1){
					choose=i;
				}
				maxc=max(maxc,D[i]);
				D[i]=0;
			}
			if(~maxc&1) ++maxc;
			dfs(choose);
		}
		for(int i=1;i<=n;++i){
			in[i]=0;
			int x=Q[i];
			++cntuse;
			for(edge* &ii= V[x];ii;ii=ii->nxt){
				use[color[ii->t]]=cntuse;
			}
			color[x]=1;
			while(use[color[x]]==cntuse) ++color[x];
		}
		printf("%d\n",maxc);
		for(int i=1;i<=n;++i) printf("%d\n",color[i]),color[i]=0;
	}
	return 0;
}

