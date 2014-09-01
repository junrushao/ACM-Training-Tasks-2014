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

vector<int> board[10101];

int n;
int cnt;
int ans[100101];
int use[6];
int getnum(int x,int y,int z=-1){
	int sel=0;
	for(int i=1;i<=5;++i){
		if(i!=x&&i!=y&&i!=z){
			if(sel==0||use[i]<use[sel]) sel=i;
		}
	}
	++use[sel];
	return sel;
}
int main() {
	ans[1]=1;
	use[1]=1;
	cnt=1;
	board[0].push_back(1);
	board[0].push_back(1);
	for(int i=1;cnt<10000;i++){
		board[i].push_back(0);
		int st=cnt+1;
		int now=0;
		for(int j=0;j<6;++j){
			for(int k=0;k<i-1;++k){
				if(j==0&&k==0){
					++cnt,ans[cnt]=getnum(board[i-1][now],board[i-1][now+1]);
					board[i].push_back(ans[cnt]);
					++now;
				}
				else{
					++cnt,ans[cnt]=getnum(board[i-1][now],board[i-1][now+1],ans[cnt-1]);
					board[i].push_back(ans[cnt]);
					++now;
				}
			}
			if(j!=5){
				++cnt;
				ans[cnt]=getnum(board[i-1][now],ans[cnt-1]);
				board[i].push_back(ans[cnt]);
			}
			else{
				++cnt,ans[cnt]=getnum(board[i-1][now],ans[cnt-1],ans[st]);
				board[i].push_back(ans[cnt]);
			}
		}
		board[i][0]=ans[cnt];
	}
//	for(int i=1;i<=100;++i) printf("%d: %d\n",i,ans[i]);
	int t;
	scanf("%d",&t);
	while(t--){
		int x;
		scanf("%d",&x);
		printf("%d\n",ans[x]);
	}
	return 0;
}
