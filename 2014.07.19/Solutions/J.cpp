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

int sum[2000];
int T;
int N;
char s[100];

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		memset(sum,0,sizeof(sum));
		while(N--){
			int x,y;
			scanf("%s",s);sscanf(s,"%d:%d",&x,&y);
			++sum[x*60+y];
			scanf("%s",s);sscanf(s,"%d:%d",&x,&y);
			--sum[x*60+y+1];
		}
		int nowans=0,stpos=0,edpos=0;
		bool flag=false;
		for(int i=0;i<60*24;++i){
			if(i) sum[i]+=sum[i-1];
			if(sum[i]>nowans) nowans=sum[i],edpos=stpos=i,flag=true;
			else if(sum[i]==nowans&&flag){
				edpos=i;
			}
			else flag=false;
		}
		printf("%02d:%02d %02d:%02d\n",stpos/60,stpos%60,edpos/60,edpos%60);
	}
	return 0;

}
