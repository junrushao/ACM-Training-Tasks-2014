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

int n,m;
int T;

struct edge{
	int t,c;
	edge *nxt;
	void init(const int _s,const int _t,const int _c);
}E[401000],*V[100010],*PE;
void edge::init(const int _s,const int _t,const int _c){
	t=_t,c=_c,nxt=V[_s],V[_s]=this;
}
const int inf=0x3f3f3f3f;
int dist[100010];
int Q[100010],QH,QT;
pair<int,int> pre[100010];
vector<int> VV[2];
vector<int> ans;
int main() {
	scanf("%d",&T);
	while(T--){
		PE=E;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i) V[i]=0,dist[i]=inf,pre[i]=make_pair(inf,inf);
		while(m--){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			PE++->init(x,y,z);
			PE++->init(y,x,z);
		}
		QH=QT=-1;
		Q[++QT]=n;
		dist[n]=0;
		while(QH++!=QT){
			int x=Q[QH];
			for(edge *ii=V[x];ii;ii=ii->nxt){
				if(dist[ii->t]>dist[x]+1){
					dist[ii->t]=dist[x]+1;
					Q[++QT]=ii->t;
				}
			}
		}
		printf("%d\n",dist[1]);
		VV[0].clear();
		VV[1].clear();
		VV[0].push_back(1);
		for(int i=1;i<=dist[1];++i){
			int now=inf;
			for(int j=0;j<int(VV[0].size());++j){
				int x=VV[0][j];
				for(edge *ii=V[x];ii;ii=ii->nxt){
					if(dist[ii->t]==dist[x]-1){
						if(ii->c<now) now=ii->c,VV[1].clear();
						if(ii->c==now&&pre[ii->t].first>ii->c){
							pre[ii->t]=make_pair(ii->c,x);
							VV[1].push_back(ii->t);
						}
					}
				}
			}
			VV[0].clear();
			swap(VV[0],VV[1]);
		}
		ans.clear();
		{
			int now=n;
			while(now!=1){
				ans.push_back(pre[now].first);
				now=pre[now].second;
			}
		}
		reverse(ans.begin(),ans.end());
		for(int i=0;i<dist[1];++i) printf("%d%c",ans[i],i==dist[1]-1?'\n':' ');
	}
	return 0;
}
