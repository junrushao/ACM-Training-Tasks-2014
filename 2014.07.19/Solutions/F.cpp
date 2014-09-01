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

int T,Q,N;
int M;
LL C[51][51];
double v[51][51];
vector<int> V;
int tt=0;
int main() {
	for(int i=0;i<=50;++i){
		v[i][0]=1;
		C[i][0]=1;
		for(int j=1;j<=i;++j) C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	scanf("%d",&T);
	while(T--){
		printf("Test Case #%d:\n",++tt);
		scanf("%d",&M);
		for(int i=1;i<=M;++i){
			scanf("%lf",v[i]+1);
			for(int j=2;j<=50;++j) v[i][j]=v[i][j-1]*v[i][1];
		}
		scanf("%d",&Q);
		while(Q--){
			scanf("%d",&N);
			V.clear();
			for(int i=1;i<=N;++i){
				int x;
				scanf("%d",&x);
				V.push_back(x);
			}
			sort(V.begin(),V.end());
			int cnt=1,st=V[0];
			double ans=1;
			for(int i=1;i<(int)V.size();++i){
				if(V[i]==st) ++cnt;
				else ans=ans*C[N][cnt]*v[st][cnt],N-=cnt,st=V[i],cnt=1;
			}
			ans=ans*v[st][cnt];
			int B=0;
			double now=1;
			while(ans*now+1e-9<1){
				++B;now*=10;
			}
			printf("%.5f x 10^%d\n",ans*now+1e-9,-B);
		}
	}
	return 0;
}
