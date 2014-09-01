#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>

using namespace std;

#define PII pair<int,int>
#define X first
#define Y second
#define pb push_back
#define mp make_pair
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define per(a,b,c) for(int a=b;a>=c;a--)

vector<PII >s1,s2,qus;
int ans[100010];
int T,n,m;

int main(){
	scanf("%d",&T);
	rep(TT,1,T){
		s1.clear();s2.clear();qus.clear();
		scanf("%d%d",&n,&m);
		memset(ans,0,sizeof ans);
		rep(i,1,n){
			int L,R;
			scanf("%d%d",&L,&R);
			s1.pb(mp((L+R)/2,L));
			s2.pb(mp((L+R+1)/2,R));
		}
		sort(s1.begin(),s1.end());
		sort(s2.begin(),s2.end());
		rep(i,1,m){
			int X;
			scanf("%d",&X);
			qus.pb(mp(X,i));
		}
		sort(qus.begin(),qus.end());
		int po=n-1,cur=1000000001;
		per(i,m-1,0){
			while	(po>=0 && s1[po].X>=qus[i].X){
				cur=min(cur,s1[po].Y);
				po--;
			}
			ans[qus[i].Y]=max(ans[qus[i].Y],qus[i].X-cur);
		}
		po=0;cur=-1;
		rep(i,0,m-1){
			while	(po<n && s2[po].X<=qus[i].X){
				cur=max(cur,s2[po].Y);
				po++;
			}
			ans[qus[i].Y]=max(ans[qus[i].Y],cur-qus[i].X);
		}
		printf("Case %d:\n",TT);
		rep(i,1,m)	printf("%d\n",ans[i]);
	}
}

