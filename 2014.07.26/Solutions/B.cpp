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
#include <stack>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

void solve() {
}
int T,n,len;
char s[500000];
stack<int> S;
int nxt[500101][2];
LL Hash[500101];
LL P[500101];
inline LL calcHash(int H,int T){
	return Hash[T]-Hash[H]*P[T-H];
}

pair<LL,int> F[500101];
int cnt,total;
char output[500101];
int lo;

void AppendInt(int x){
	int now=1;
	while(now*10<=x) now*=10;
	while(now){
		output[++lo]=x/now+'0';
		x%=now;
		now/=10;
	}
}
void Append(char c){
	output[++lo]=c;
}
void predfs(int l,int r){
	F[++total].first=calcHash(l-1,r);
	F[total].second=0;
	for(int i=l;i<=r;++i){
		if(s[i]=='('){
			predfs(i+1,nxt[i][0]-1);
			predfs(nxt[i][0]+1,nxt[i][1]-1);
			break;
		}
	}
	return;
}
void dfs(int l,int r){
	LL hashVal=calcHash(l-1,r);
//	V.push_back(make_pair(make_pair(l,r),hashVal));
	int d=lower_bound(F+1,F+total+1,make_pair(hashVal,0))-F;
	if(F[d].second==0){
		F[d].second=++cnt;
	}
	else{
		AppendInt(F[d].second);
		return;
	}
	while(l<=r&&s[l]!='('){
		Append(s[l]);
		++l;
	}
	if(s[l]=='('){
		Append('(');
		dfs(l+1,nxt[l][0]-1);
		Append(',');
		dfs(nxt[l][0]+1,nxt[l][1]-1);
		Append(')');
	}
}

const int mod=1000000007;
//const int mod=1000;
int main(){
	scanf("%d",&T);
	P[0]=1;
	for(int i=1;i<=500000;++i) P[i]=P[i-1]*mod;
	while(T--){
		scanf("%s",s+1);
		len=strlen(s+1);
		for(int i=1;i<=len;++i) Hash[i]=Hash[i-1]*mod+s[i];
		for(int i=1;i<=len;++i){
			if(s[i]=='('){
				S.push(i);
			}
			else if(s[i]==','){
				nxt[S.top()][0]=i;
			}
			else if(s[i]==')'){
				nxt[S.top()][1]=i;
				S.pop();
			}
		}
		total=0;
		predfs(1,len);
		sort(F+1,F+total+1);
		total=unique(F+1,F+total+1)-F-1;
		cnt=0;
		lo=0;
		dfs(1,len);
		output[lo+1]=0;
		puts(output+1);
	}
	return 0;
}
