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

int N;
int dist[2001][2001];
bool used[2001][2001];
int fa[2001];
bool inCircle[2001];
vector<int> Circle;
vector<int> Chl[2001];
const int maxV=1000000;
vector<pair<int,int> > V[maxV+1000];
bool ans[2001][2001];
struct Edge{
	int T,V;Edge *Nxt;
	void init(const int _S,const int _T,const int _V);
}E[4001],*Node[2001],*pe;
void Edge::init(const int _S,const int _T,const int _V){
	T=_T,V=_V,Nxt=Node[_S],Node[_S]=this;
}
int Dist[2001];
const int inf=0x7f7f7f7f;
int Q[2001];
int pred[2001];
int H,T;
int getfa(int x){return fa[x]==x?x:(fa[x]=getfa(fa[x]));}
void Bfs(const vector<int> &v,const int st){
	for(int i=0;i<(int)v.size();++i) Dist[v[i]]=inf;
	bool checkCircle=false;
	Dist[st]=0;
	H=-1,T=0;
	Q[0]=st;
	while(H++!=T){
		int x=Q[H];
		if(inCircle[x]&&!checkCircle){
			checkCircle=1;
			for(int i=0;i<int(Circle.size());++i){
				if(Dist[Circle[i]]>Dist[x]+dist[x][Circle[i]]){
					Dist[Circle[i]]=Dist[x]+dist[x][Circle[i]];
					pred[Circle[i]]=x;
					Q[++T]=Circle[i];
				}
			}
		}
		Edge *ii=Node[x];
		while(ii){
			if(Dist[ii->T]>Dist[x]+ii->V){
				Dist[ii->T]=Dist[x]+ii->V;
				pred[ii->T]=x;
				Q[++T]=ii->T;
			}
			ii=ii->Nxt;
		}
	}
}
void buildCircle(const int x,const int y){
	int z=fa[x];
	Bfs(Chl[z],x);
	int w=y;
	while(w!=x){
		inCircle[w]=1;
		Circle.push_back(w);
		w=pred[w];
	}
	inCircle[w]=1;
	Circle.push_back(w);
	for(int i=0;i<int(Chl[z].size());++i) for(int j=0;j<int(Chl[z].size());++j){
		used[Chl[z][i]][Chl[z][j]]=1;
	}
	ans[x][y]=1;
	pe++->init(x,y,dist[x][y]);
	pe++->init(y,x,dist[x][y]);
}
void buildLink(const int x,const int y){
	int z=fa[x],w=fa[y];
	Bfs(Chl[z],x);
	Bfs(Chl[w],y);
	for(int i=0;i<(int)Chl[z].size();++i){
		int a=Chl[z][i];
		for(int j=0;j<(int)Chl[w].size();++j){
			int b=Chl[w][j];
			if(dist[a][b]==Dist[a]+Dist[b]+dist[x][y]){
				used[a][b]=used[b][a]=1;
			}
		}
	}
	if(Chl[z].size()>Chl[w].size()) swap(z,w);
	fa[z]=w;
	for(int i=0;i<(int)Chl[z].size();++i) Chl[w].push_back(Chl[z][i]);
	ans[x][y]=1;
	pe++->init(x,y,dist[x][y]);
	pe++->init(y,x,dist[x][y]);
}
int main() {
	bool firstTest=true;
	while(scanf("%d",&N)==1){
		if(firstTest) firstTest=false;
		else printf("\n");
		Circle.clear();
		pe=E;
		for(int i=1;i<=N;++i){
			fa[i]=i;
			Node[i]=0;
			Chl[i].clear();
			Chl[i].push_back(i);
			inCircle[i]=0;
			for(int j=1;j<=N;++j){
				scanf("%d",dist[i]+j);
				ans[i][j]=used[i][j]=false;
				if(i<j) V[dist[i][j]].push_back(make_pair(i,j));
			}
		}
		int cnt=0;
		for(int value=1;value<=maxV;++value){
			for(int i=0;i<int(V[value].size());++i){
				int x=V[value][i].first,y=V[value][i].second;
				if(!used[x][y]){
					++cnt;
					if(getfa(x)==getfa(y)){
						buildCircle(x,y);
					}
					else{
						buildLink(x,y);
					}
				}
			}
			V[value].clear();
		}
		for(int i=1;i<=N;++i) for(int j=i+1;j<=N;++j) if(ans[i][j]){
			printf("%d %d %d\n",i,j,dist[i][j]);
			if(cnt<N) ++cnt,printf("%d %d %d\n",i,j,dist[i][j]);
		}
	}
	return 0;
}