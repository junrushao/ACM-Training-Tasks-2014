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

int pos[101001];
int a[101001];
int n,T;
vector<pair<int,int> > ans;
int main() {
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);
			pos[a[i]]=i;
		}
		ans.clear();
		for(int i=1;i<=n;++i) if(pos[i]!=i){
			int aim=(i&1)==(pos[i]&1)?i:i+1;
			if(pos[i]!=aim){
				int l=aim;
				int x=a[l];
				int mid=(aim+pos[i])/2;
				int y=a[mid];
				int r=pos[i];
				ans.push_back(make_pair(l+1,r));
				ans.push_back(make_pair(l,r-1));
				swap(pos[i],pos[x]);
				swap(pos[x],pos[y]);
				swap(a[r],a[l]);
				swap(a[r],a[mid]);
			}
			if(pos[i]!=i){
				swap(a[i],a[i+1]);
				swap(pos[a[i]],pos[a[i+1]]);
				ans.push_back(make_pair(i,i+1));
			}
		}
		printf("%d\n",(int)ans.size());
		for(int i=0;i<int(ans.size());++i){
			printf("%d %d\n",ans[i].first,ans[i].second);
		}
	}
}

