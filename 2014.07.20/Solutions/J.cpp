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

int T,N,M,Q;

int dist[101][101];

pair<int,int> P[1101];
bool v[1001][1001];
int D[1001];
int in[1001],cnt;
bool match[1001];
inline bool Reach(pair<int,int> x,pair<int,int> y,int z,int w){
	return x.second+dist[x.first][y.first]<=y.second&&((x.second<y.second)||(x.second==y.second&&z<w));
}

bool dfs(int x){
	for(int i=1;i<=Q;++i) if(v[x][i]&&in[i]!=cnt){
		in[i]=cnt;
		if(D[i]==-1||dfs(D[i])){
			return D[i]=x,1;
		}
	}
	return 0;
}

int main() {
	scanf("%d",&T);
	for(int tt=1;tt<=T;++tt){
		scanf("%d%d%d",&N,&M,&Q);
		memset(dist,63,sizeof(dist));
		for(int i=1;i<=N;++i) dist[i][i]=0;
		while(M--){
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c),++a,++b;
			dist[a][b]=dist[b][a]=min(dist[a][b],c);
		}
		for(int k=1;k<=N;++k){
			for(int i=1;i<=N;++i){
				for(int j=1;j<=N;++j){
					dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
				}
			}
		}
		for(int i=1;i<=Q;++i){
			scanf("%d%d",&P[i].first,&P[i].second),++P[i].first;
			for(int j=1;j<i;++j){
				v[i][j]=Reach(P[i],P[j],i,j);
				v[j][i]=Reach(P[j],P[i],i,j);
			}
			D[i]=-1;
		}
		int ans=Q;
		for(int i=1;i<=Q;++i){
			match[i]=0;
			for(int j=1;j<=Q;++j) if(v[i][j]&&D[j]==-1){
				D[j]=i;
				match[i]=1;
				--ans;
				break;
			}
		}
		++cnt;
		for(int i=1;i<=Q;++i) if(!match[i]){
			if(dfs(i)){
				++cnt;
				ans--;
			}
		}
		printf("Case %d: %d\n",tt,ans-1);
	}
	return 0;
}
