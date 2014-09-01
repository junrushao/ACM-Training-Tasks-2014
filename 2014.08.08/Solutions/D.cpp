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


int n,m;

int a[31][31];
int rec[5][31][31];

int pn,pm;
int ans;

void Rotate(int a, int n, int m) {
	static int tmp[33][33];
	REP(i, n) REP(j, m) tmp[i][j] = rec[a][i][j];
	REP(i, m) REP(j, n) rec[a][i][j] = tmp[j][m-1-i];
}

int solve(int n,int m){
	int ans=0;
	for(int i=0;i<4;++i){
		if((~i&1)||n==m){
			for(int j=0;j<4;++j){
				if((~j&1)||n==m){
					for(int k=0;k<4;++k){
						if((~k&1)||n==m){
							int minval=50000000;
							for(int ii=0;ii<n;++ii){
								for(int jj=0;jj<m;++jj){
									int now=0;
									for(int kk=0;kk<4;++kk) now+=rec[kk][ii][jj];
									if(minval>now) minval=now;
								}
							}
							if(minval>ans) ans=minval;
						}
						Rotate(3,(k&1)?m:n,(k&1)?n:m);
					}
				}
				Rotate(2,(j&1)?m:n,(j&1)?n:m);
			}
		}
		Rotate(1,(i&1)?m:n,(i&1)?n:m);
	}
	return ans;
}

void getMatrix(int lx,int ly,int cnt,int r){
	int N=pn,M=pm;
	if(r) swap(N,M);
	for(int i=0;i<N;++i) for(int j=0;j<M;++j){
		rec[cnt][i][j]=a[lx+i][ly+j];
	}
	if(r) Rotate(cnt,N,M);
}

void dfs(int lx,int ly,int rx,int ry,int cnt){
	if(cnt==4){
		ans=max(ans,solve(pn,pm));
		return;
	}
	if(pn==rx-lx){
		getMatrix(lx,ly,cnt,0);
		dfs(lx,ly+pm,rx,ry,cnt+1);
		getMatrix(lx,ry-pm,cnt,0);
		dfs(lx,ly,rx,ry-pm,cnt+1);
	}
	if(pm==ry-ly){
		getMatrix(lx,ly,cnt,0);
		dfs(lx+pn,ly,rx,ry,cnt+1);
		getMatrix(rx-pn,ly,cnt,0);
		dfs(lx,ly,rx-pn,ry,cnt+1);
	}
	if(pm==rx-lx){
		getMatrix(lx,ly,cnt,1);
		dfs(lx,ly+pn,rx,ry,cnt+1);
		getMatrix(lx,ry-pn,cnt,1);
		dfs(lx,ly,rx,ry-pn,cnt+1);
	}
	if(pn==ry-ly){
		getMatrix(lx,ly,cnt,1);
		dfs(lx+pm,ly,rx,ry,cnt+1);
		getMatrix(rx-pm,ly,cnt,1);
		dfs(lx,ly,rx-pm,ry,cnt+1);
	}
}

int main() {
	while(scanf("%d%d",&n,&m)==2){
		REP(i, n) REP(j, m) scanf("%d", &a[i][j]);
		ans=0;
		if(n%2==0&&m%2==0){
			pn=n/2,pm=m/2;
			for(int i=0;i<n/2;++i) for(int j=0;j<m/2;++j){
				rec[0][i][j]=a[i][j];
				rec[1][i][j]=a[i+n/2][j];
				rec[2][i][j]=a[i][j+m/2];
				rec[3][i][j]=a[i+n/2][j+m/2];
			}
			ans=solve(pn,pm);
		}
		if(n%4==0){
			pn=n/4;
			pm=m;
			dfs(0,0,n,m,0);
		}
		if(m%4==0){
			pm=m/4;
			pn=n;
			dfs(0,0,n,m,0);
		}
		printf("%d\n", ans);
	}
}
