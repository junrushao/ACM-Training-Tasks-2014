#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<iostream>
#include<ctype.h>
#include<algorithm>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<cmath>
#include<bitset>
#include<iomanip>
#include<complex>
#include<utility>

#define X first
#define Y second
#define REP_0(i,n) for(int i=0;i<(n);++i)
#define REP_1(i,n) for(int i=1;i<=(n);++i)
#define REP_2(i,a,b) for(int i=(a);i<(b);++i)
#define REP_3(i,a,b) for(int i=(a);i<=(b);++i)
#define REP_4(i,a,b,c) for(int i=(a);i<(b);i+=(c))
#define DOW_0(i,n) for(int i=(n)-1;-1<i;--i)
#define DOW_1(i,n) for(int i=(n);0<i;--i)
#define DOW_2(i,a,b) for(int i=(b);(a)<i;--i)
#define DOW_3(i,a,b) for(int i=(b);(a)<=i;--i)
#define FOREACH(a,b) for(typeof((b).begin()) a=(b).begin();a!=(b).end();++a)
#define RFOREACH(a,b) for(typeof((b).rbegin()) a=(b).rbegin();a!=(b).rend();++a)
#define PB push_back
#define PF push_front
#define MP make_pair
#define IS insert
#define ES erase
#define IT iterator
#define RI reserve_iterator
#define PQ priority_queue
#define LB lower_bound
#define UB upper_bound
#define ALL(x) x.begin(),x.end()

#define PI 3.1415926535897932384626433832795
#define EXP 2.7182818284590452353602874713527

using namespace std;

typedef long long LL;
typedef long double LD;
typedef double DB;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef pair<int,PII> PIII;
typedef pair<LD,int> PLDI;
typedef vector<PII> VII;

template<class T>
T Mul(T x,T y,T P){
	T F1=0;
	while(y)
	{
		if(y&1)
		{
			F1+=x;
			if(F1<0||F1>=P)F1-=P;
		}
		x<<=1;
		if(x<0||x>=P)x-=P;
		y>>=1;
	}
	return F1;
}

template<class T>
T Pow(T x,T y,T P){
	T F1=1;x%=P;
	while(y)
	{
		if(y&1)
		{
			F1=Mul(F1,x,P);
		}
		x=Mul(x,x,P);
		y>>=1;
	}
	return F1;
}

template<class T>
T Gcd(T x,T y){
	if(y==0)return x;
	T z;
	while(z=x%y){
		x=y,y=z;
	}
	return y;
}

template<class T>
void UpdateMin(T &x,T y){
	if(y<x)
	{
		x=y;
	}
}

template<class T>
void UpdateMax(T &x,T y){
	if(x<y)
	{
		x=y;
	}
}

template<class T>
T Sqr(const T x){
	return x*x;
}

template<class T>
T Abs(const T x){
	return x<0?-x:x;
}

#define MaxBuffer 20000000
class ReadBuffer{
	private:
	char buff[MaxBuffer];
	char *buf;
	public:
	void init(int size=MaxBuffer)
	{
		fread(buff,1,size,stdin);
		buf=buff;
	}
	template<class T>
	bool readInteger(T &x)
	{
		x=0;
		while(*buf&&isspace(*buf)) ++buf;
		if(*buf==0) return false;
		static bool flag;
		flag=0;
		if(*buf=='-') flag=true;
		else x=*buf-'0';
		while(isdigit(*++buf)) x=x*10+*buf-'0';
		if(flag) x=-x;
		return true;
	}
	template<class T>
	bool readFloat(T &x)
	{
		long double nowpos=0.1;
		x=0;
		while(*buf&&isspace(*buf)) ++buf;
		if(*buf==0) return false;
		static bool flag,decimal;
		decimal=flag=0;
		if(*buf=='-') flag=true,++buf;
		else if(*buf=='.') decimal=true;
		while(isdigit(*buf)||*buf=='.')
		{
			if(*buf=='.') decimal=true;
			else
			{
				if(decimal)
				{
					x+=nowpos*(*buf-'0');
					nowpos*=0.1;
				}
				else
				{
					x=x*10+*buf-'0';
				}
			}
			++buf;
		}
		return true;
	}
	bool readChar(char c)
	{
		if(*buf==0) return 0;
		return c=*buf++,1;
	}
	bool readString(char *s)
	{
		while(*buf&&isspace(*buf)) ++buf;
		if(!*buf) return false;
		while(!isspace(*buf)) *s++=*buf++;
		*s++=0;
		return true;
	}
	int countSpacetonext(){
		int total=0;
		while(*buf&&*buf==' ') ++total,++buf;
		return total;
	}
	bool splitBycharactor(char *s,char Split='\n'){
		while(*buf&&*buf!=Split) *s++=*buf++;
		*s++=0;
		return *buf!=0;
	}
};

struct EDGE{
	int T;EDGE *Nxt;
};

LL totalans[52][52];
LL torotate[52][52];
int movedir[2][52][52][9];
const int dx[]={-1,-1,0,1,1,1,0,-1};
const int dy[]={0,1,1,1,0,-1,-1,-1};
int N,M,T,S;
int recordnum=0;
LL ans;
int t1,t2;

const int mod=1000000007;
#define Addmod(x,y) x+=y;if(x>=mod) x-=mod

map<vector<int>, int> Map;

LL record[801][52][52];

void Rotate(int N,int M){
	REP_1(i,N) REP_1(j,M){
		torotate[j][N-i+1]=totalans[i][j];
	}
	REP_1(i,M) REP_1(j,N) totalans[i][j]=torotate[i][j];
}

void Flip(int N,int M){
	REP_1(i,N) REP_1(j,M) torotate[N+1-i][j]=totalans[i][j];
	REP_1(i,N) REP_1(j,M) totalans[i][j]=torotate[i][j];
}

int main(){
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	scanf("%d",&T);
	//T=100;
	REP_1(tt,T){
		scanf("%d%d%d",&N,&M,&S);
		//N=50,M=50,S=500;
		int x,y;
		scanf("%d%d",&x,&y);
		//x=y=25;
		vector<int> GG;
		GG.PB(N),GG.PB(M),GG.PB(S),GG.PB(x),GG.PB(y);
		if(!Map.count(GG)){
			memset(totalans,0,sizeof(totalans));
			memset(movedir,0,sizeof(movedir));
			t1=0,t2=1;
			totalans[x][y]=1;
			REP_0(i,8) movedir[t1][x+dx[i]][y+dy[i]][i]=1;
			REP_1(ss,S){
				REP_1(i,N) REP_1(j,M){
					LL s=0;
					REP_0(k,8){
						s+=movedir[t1][i][j][k];
					}
					while(s>=mod) s-=mod;
					REP_0(k,8){
						int nx=i+dx[k];
						int ny=j+dy[k];
						movedir[t2][nx][ny][k]=movedir[t1][i][j][k]+s;
						if(movedir[t2][nx][ny][k]>=mod) movedir[t2][nx][ny][k]-=mod;
					}
					totalans[i][j]+=s;
				}
				t1^=1,t2^=1;
			}
			REP_1(times,4){
				Rotate(GG[0],GG[1]);
				swap(GG[0],GG[1]),swap(GG[3],GG[4]);
				GG[4]=GG[1]+1-GG[4];
				if(!Map.count(GG)){
					Map[GG]=++recordnum;
					REP_1(i,GG[0]) REP_1(j,GG[1]) record[recordnum][i][j]=totalans[i][j];
				}
			}
			Flip(GG[0],GG[1]);
			GG[3]=GG[0]+1-GG[3];
			REP_1(times,4){
				Rotate(GG[0],GG[1]);
				swap(GG[0],GG[1]),swap(GG[3],GG[4]);
				GG[4]=GG[1]+1-GG[4];
				if(!Map.count(GG)){
					Map[GG]=++recordnum;
					REP_1(i,GG[0]) REP_1(j,GG[1]) record[recordnum][i][j]=totalans[i][j];
				}
			}
			Flip(GG[0],GG[1]);
			GG[3]=GG[0]+1-GG[3];
		}
		else{
			int num=Map[GG];
			REP_1(i,N) REP_1(j,M) totalans[i][j]=record[num][i][j];
		}
		ans=0;
		REP_1(i,N){
			REP_1(j,M){
				scanf("%d",&x);
				//x=0;
				ans+=(LL)x*(totalans[i][j]%mod);
				if(ans>=mod) ans%=mod;
			}
		}
		printf("%d\n",int(ans));
	}
	//printf("Time = %d\n",(int)clock());
	return 0;
}

