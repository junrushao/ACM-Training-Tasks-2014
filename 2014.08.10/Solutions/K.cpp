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
#include <queue>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

void solve() {
}

bool G[27][27];
char s[10];
int T,N;

vector<int> dfn;

bool vis[27];
bool instack[27];
vector<int> circle;

bool dfs(int x){
	vis[x]=instack[x]=1;
	dfn.push_back(x);
	for(int i=0;i<26;++i) if(G[x][i]){
		if(!vis[i]){
			if(dfs(i)) return true;
		}
		else if(instack[i]){
			int k=(int)dfn.size()-1;
			while(dfn[k]!=i) --k;
			for(int j=k;j<int(dfn.size());++j) circle.push_back(dfn[j]);
			return true;
		}
	}
	dfn.pop_back();
	instack[x]=0;
	return false;
}

bool findCircle(){
	dfn.clear();
	circle.clear();
	memset(vis,0,sizeof(vis));
	memset(instack,0,sizeof(instack));
	for(int i=0;i<26;++i) if(!vis[i]){
		if(dfs(i)){
			return true;
		}
	}
	return false;
}

int ans;
char anss[27][27];
int nxt[27];
int dp[27];
int D[27];

queue<int> Q;

int main() {
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		memset(G,1,sizeof(G));
		while(N--){
			scanf("%s",s);
			G[s[0]-'a'][s[1]-'a']=0;
		}
		if(findCircle()){
			ans=20;
			for(int i=0;i<ans;++i){
				for(int j=0;j<ans;++j){
					anss[i][j]=circle[(i+j)%(int)circle.size()]+'a';
				}
				anss[i][ans]=0;
			}
		}
		else{
			for(int i=0;i<26;++i){
				D[i]=0;
				dp[i]=0;
				for(int j=0;j<26;++j){
					D[i]+=G[i][j];
				}
				if(D[i]==0) Q.push(i);
				nxt[i]=-1;
			}
			int first=-1;
			while(!Q.empty()){
				int x=Q.front();
				Q.pop();
				if(first==-1||dp[x]>dp[first]) first=x;
				for(int i=0;i<26;++i){
					if(G[i][x]){
						if(dp[i]<dp[x]+1){
							dp[i]=dp[x]+1;
							nxt[i]=x;
						}
						if(--D[i]==0) Q.push(i);
					}
				}
			}
			ans=max(dp[first]/2+1,1);
			circle.clear();
			while(first!=-1){
				circle.push_back(first);
				first=nxt[first];
			}
			for(int i=0;i<ans;++i){
				for(int j=0;j<ans;++j){
					anss[i][j]=circle[(i+j)%(int)circle.size()]+'a';
				}
				anss[i][ans]=0;
			}
		}
		for(int i=0;i<ans;++i) printf("%s\n",anss[i]);
	}
}

