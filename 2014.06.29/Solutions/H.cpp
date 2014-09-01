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

int T,N;
int tt=0;
char* Name[100001];
int Writer[101];
bitset<100100> B[101];
bitset<100100> ans;
int reorder[101];
int cnt;
bool in[101];
char s[2000001];
char recordbuff[2000001];
char *buff;
vector<int> V;
int NameOrder[100100];
int rank[100100];
struct node{
	char *s;
	node(){}
	node(char *s):s(s){}
	bool operator <(const node &x)const{
		for(int i=0;;++i){
			if(!*(x.s+i)) return false;
			if(!*(s+i)) return true;
			if(*(s+i)!=*(x.s+i)) return *(s+i)<*(x.s+i);
		}
	}
};

map<node,int> M;

inline bool cmp(const int &x,const int &y){
	return NameOrder[x]<NameOrder[y];
}

inline bool cmpwriter(const int &x,const int &y){
	return NameOrder[Writer[x]]<NameOrder[Writer[y]];
}
inline int try_insert(char *s){
	if(M.count(node(s))){
		return M[node(s)];
	}
	else{
		++cnt;
		Name[cnt]=buff;
		while(*s){
			*(buff++)=*(s++);
		}
		*(buff++)=0;
		M[node(Name[cnt])]=cnt;
		return cnt;
	}
}

stack<int> S;

int main(){
//	freopen("a.out","r",stdin);
//	freopen("a.ans","w",stdout);
	while(scanf("%d%d",&T,&N)==2&&(T||N)){
		buff=recordbuff;
		M.clear();
		cnt=0;
		gets(s);
		REP_1(i,N){
			B[i].reset();
			gets(s);
			V.clear();
			char *ss=s;
			while(*ss){
				while(*ss&&!isalpha(*ss)){
					++ss;
				}
				if(!*ss) break;
				char *sss=ss;
				while(*sss&&isalpha(*sss)) ++sss;
				char d=*sss;
				*sss=0;
				V.push_back(try_insert(ss));
				*sss=d;
				ss=sss;
			}
			Writer[i]=V[0];
			REP_0(j,int(V.size())){
				B[i][V[j]]=1;
			}
			reorder[i]=i;
		}
		{
			int rank=0;
			for(map<node,int>::iterator iter=M.begin();iter!=M.end();++iter){
				NameOrder[iter->Y]=++rank;
				::rank[rank]=iter->Y;
			}
		}
		sort(reorder+1,reorder+N+1,cmpwriter);
		printf("--- CASE %d\n",++tt);
		REP_1(i,N){
			int x=reorder[i];
			ans.reset();
			memset(in,0,sizeof(in));
			S.push(x);
			in[x]=1;
			while(!S.empty()){
				int y=S.top();
				S.pop();
				ans|=B[y];
				REP_1(j,N) if(!in[j]&&B[y][Writer[j]]) S.push(j),in[j]=1;
			}
			if((ans^=B[x]).count()){
				printf("%s",Name[Writer[x]]);
				REP_1(j,cnt) if(ans[rank[j]]) printf(" %s",Name[rank[j]]);
				printf("\n");
			}
		}
	}
//	printf("%d\n",(int)clock());
	return 0;
}
