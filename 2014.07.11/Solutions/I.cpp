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

vector<int> V;

char s[1101];
int len;
bool valid[1101][1101];
int vis[1101][1101];
LL value[1101][1101][2];
int next[1101];
int cnt=0;
bool solve(int l,int r){
	if(vis[l][r]==cnt) return valid[l][r];
	vis[l][r]=cnt;
	if(!isdigit(s[r])) return valid[l][r]=false;
	if(isdigit(s[l])){
		if(r-l>8) return valid[l][r]=false;
		if(s[l]=='0'&&l!=r) return valid[l][r]=false;
		int now=0;
		for(int i=l;i<=r;++i){
			if(!isdigit(s[i])) return valid[l][r]=false;
			now=now*10+s[i]-'0';
		}
		return value[l][r][0]=value[l][r][1]=now,valid[l][r]=true;
	}
	valid[l][r]=false;
	if(s[l]=='-'&&solve(l+1,r)){
		valid[l][r]=1;
		value[l][r][0]=-value[l+1][r][1];
		value[l][r][1]=-value[l+1][r][0];
	}
	if(isdigit(s[l+1])){
		for(int i=l+1;i<=l+9&&i<r;++i){
			if(!isdigit(s[i])) break;
			if(solve(l+1,i)&&solve(i+1,r)){
				for(int j=0;j<2;++j) for(int k=0;k<2;++k){
					LL now=s[l]=='+'?value[l+1][i][j]+value[i+1][r][k]:value[l+1][i][j]-value[i+1][r][k];
					if(!valid[l][r]){
						valid[l][r]=1;
						value[l][r][0]=value[l][r][1]=now;
					}
					else{
						value[l][r][0]=min(value[l][r][0],now);
						value[l][r][1]=max(value[l][r][1],now);
					}
				}
			}
		}
		return valid[l][r];
	}
	for(int i=r-1;i>=r-9&&i>l;--i){
		if(!isdigit(s[i])) break;
		if(solve(l+1,i)&&solve(i+1,r)){
			for(int j=0;j<2;++j) for(int k=0;k<2;++k){
				LL now=s[l]=='+'?value[l+1][i][j]+value[i+1][r][k]:value[l+1][i][j]-value[i+1][r][k];
				if(!valid[l][r]){
					valid[l][r]=1;
					value[l][r][0]=value[l][r][1]=now;
				}
				else{
					value[l][r][0]=min(value[l][r][0],now);
					value[l][r][1]=max(value[l][r][1],now);
				}
			}
		}
	}
	for(int x=next[l+1];V[x]<r;++x){
		int i=V[x];
		if(solve(l+1,i)&&solve(i+1,r)){
			for(int j=0;j<2;++j) for(int k=0;k<2;++k){
				LL now=s[l]=='+'?value[l+1][i][j]+value[i+1][r][k]:value[l+1][i][j]-value[i+1][r][k];
				if(!valid[l][r]){
					valid[l][r]=1;
					value[l][r][0]=value[l][r][1]=now;
				}
				else{
					value[l][r][0]=min(value[l][r][0],now);
					value[l][r][1]=max(value[l][r][1],now);
				}
			}
		}
	}
	return valid[l][r];
}

int main() {
	while(scanf("%s",s+1)==1){
		//for(int i=1;i<=1000;++i) if(i<=500) s[i]='-';else s[i]=rand()%9+'1';
		//printf("%s",s);
		len=strlen(s+1);
		V.clear();
		V.push_back(0);
		for(int i=1;i<len;++i){
			if(isdigit(s[i])&&!isdigit(s[i+1])) V.push_back(i);
		}
		V.push_back(len+1);
		{
			int nownxt=V.size()-1;
			for(int i=len;i>=1;--i){
				next[i]=nownxt;
				if(V[nownxt-1]==i) --nownxt;
			}
		}
		++cnt;
		solve(1,len);
		printf("%lld %lld\n",value[1][len][0],value[1][len][1]);
	}
	return 0;
}