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

int T;

char pocker[10][10];

int cnt[20];

inline int change(char c){
	if(isdigit(c)) return c-'0';
	if(c=='A') return 14;
	if(c=='T') return 10;
	if(c=='J') return 11;
	if(c=='Q') return 12;
	return 13;
}

vector<pair<int,int> > P;

int C[20][20];
int Rank[9];
inline int calc(vector<pair<int,int> > V){
	int len=V.size();
	for(int i=0;i<len;++i) --V[i].second;
	int ans=0;
	for(int i=0;i<len;++i){
		ans+=C[V[i].second-1][len-i];
		if(len==5&&i==0){
			ans-=max(0,V[i].second-5);
			if(V[i].second==13) --ans;
		}
	}
	return ans;
}
inline bool isFlush(){
	for(int i=0;i<5;++i) if(pocker[i][1]!=pocker[0][1]) return false;
	return true;
}
inline int isStraight(){
	if(P.size()!=5) return -1;
	if(P[0].second==14&&P[1].second==5) return 5;
	return P[0].second-4==P[4].second?P[0].second:-1;
}
int main() {
	for(int i=0;i<=13;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j) C[i][j]+=C[i-1][j]+C[i-1][j-1];
	}
	Rank[0]=C[13][5]-10;
	Rank[1]=13*C[12][3];
	Rank[2]=C[13][2]*11;
	Rank[3]=13*C[12][2];
	Rank[4]=10;
	Rank[5]=C[13][5]-10;
	Rank[6]=Rank[7]=13*12;
	Rank[8]=10;
	for(int i=1;i<=8;++i) Rank[i]+=Rank[i-1];
//	for(int i=0;i<9;++i) printf("%d\n",Rank[i]);
	scanf("%d",&T);
	while(T--){
		memset(cnt,0,sizeof(cnt));
		for(int i=0;i<5;++i) scanf("%s",pocker[i]),++cnt[change(pocker[i][0])];
		P.clear();
		for(int i=2;i<=14;++i) if(cnt[i]) P.push_back(make_pair(cnt[i],i));
		sort(P.begin(),P.end());
		reverse(P.begin(),P.end());
		if(isFlush()){
			int now=isStraight();
			if(now==-1) printf("%d\n",Rank[4]+calc(P)+1);// 5
			else printf("%d\n",Rank[7]+now-4);// 8
		}
		else{
			int now=isStraight();
			if(now!=-1){
				printf("%d\n",Rank[3]+now-4);// 4
				continue;
			}
			if(P[0].first==4){// 7
				printf("%d\n",(P[0].second-2)*12+P[1].second-1-(P[1].second>P[0].second) + Rank[6]);
				continue;
			}
			if(P[0].first==3){
				if(P[1].first==2){// 6
					printf("%d\n",(P[0].second-2)*12+P[1].second-1-(P[1].second>P[0].second) + Rank[5]);
				}
				else{// 3
					vector<pair<int,int> > FP;
					FP.push_back(make_pair(1,P[1].second-(P[1].second>P[0].second)));
					FP.push_back(make_pair(1,P[2].second-(P[2].second>P[0].second)));
					printf("%d\n",(P[0].second-2)*C[12][2]+calc(FP)+1 + Rank[2]);
				}
				continue;
			}
			if(P[0].first==2){
				if(P[1].first==2){//2
					vector<pair<int,int> > FP;
					FP.push_back(P[0]);
					FP.push_back(P[1]);
					printf("%d\n",calc(FP)*11+(P[2].second-1-(P[2].second>P[1].second)-(P[2].second>P[0].second)) + Rank[1]);
				}
				else{//1
					vector<pair<int,int> > FP;
					for(int i=1;i<4;++i){
						FP.push_back(make_pair(1,P[i].second-(P[i].second>P[0].second)));
					}
					printf("%d\n",(P[0].second-2)*C[12][3]+calc(FP) + 1 + Rank[0]);
				}
				continue;
			}
			printf("%d\n",calc(P)+1);
		}
	}
}

