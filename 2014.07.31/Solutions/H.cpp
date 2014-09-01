#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cassert>
#include <bitset>

using namespace std;

long long num = 0, up = 0;
int n, m, k;
long long kj[10], jie[10];
int con[10][10];
bool tra[10];
int per[10];

int main() {
	scanf("%d%d%d", &n, &m , &k);
	memset(con,0,sizeof(con));
	kj[1]=k;
	for(int i=2; i<10; ++i) kj[i]=kj[i-1]*k;
	jie[0]=1;
	jie[1]=1;
	for(int i=2;i<10;++i) jie[i]=jie[i-1]*i;
	for(int i=0;i<m;++i){
		int x,y;
		scanf("%d%d", &x, &y);
		con[x][y]++;
		con[y][x]++;
	}
	for(int i=0; i<jie[n]; ++i){
		int tmp=i;
		for(int j=1;j<=n;++j) per[j]=j;
		for(int j=1;j<=n;++j){
			swap(per[j], per[j+tmp%(n-j+1)]);
			tmp/=(n-j+1);
		}
		bool ok=1;
		for(int i=1; i<=n;++i){
			for(int j=i;j<=n;++j){
				if(con[i][j]!=con[per[i]][per[j]]){
					ok=0;
					break;
				}
			}
			if(ok==0) break;
		}
		if(ok==0)continue;
		int xun=0;
		memset(tra, 0, sizeof(tra));
		int s=1;
		while(s<=n){
			++xun;
			int now=s;
			while(tra[now]==0){
				tra[now]=1;
				now=per[now];
			}
			while(tra[s])++s;
		}
		++num;
		up+=kj[xun];
	}
	int ans=up/num;
	printf("%d\n", ans);
	return 0;
}
