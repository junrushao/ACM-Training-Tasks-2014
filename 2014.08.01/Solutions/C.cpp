#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
#define maxn 100005

typedef int Thash[maxn][20];
Thash A,B;
int seed[30],a[maxn],b[maxn],n;
char tt[maxn];

inline void Init(int a[],Thash& A)
{
	for (int i=1;i<=n;++i)
		A[i][0]=seed[a[i]];
	for (int i=n,x=0;i;x=int(log(n+1-(--i))/log(2)))
		for (int j=1;j<=x;++j)
			A[i][j]=A[i][j-1]*seed[j]^A[i+(1<<j-1)][j-1];
}

inline int lcp(Thash& A,int a,int b)
{
	int tmp=a;
	for (int k=int(log(n)/log(2));k>=0;--k)
	if (a+(1<<k)-1<=n && b+(1<<k)-1<=n && A[a][k]==A[b][k])
	{
		a+=1<<k;
		b+=1<<k;
	}
	return a-tmp;
}

inline int calc(int pos,int len)
{
	int res=lcp(A,pos,pos+len)+lcp(B,n-pos-len+2,n-pos+2)+len;
	return res/len;
}

int main()
{
	for (int i=0;i<30;++i)
		seed[i]=rand();
	for (int test=1;scanf("%s",tt+1) && tt[1]!='#';++test)
	{
		n=strlen(tt+1);
		for (int i=1;i<=n;++i)
		{
			a[i]=tt[i]-'a';
			b[n-i+1]=a[i];
		}
		Init(a,A);Init(b,B);
		int ans=1,ansp=1,anslen=1;
		for (int l=1;l<=n;++l)
			for (int st=1;st+l<=n;st+=l)
			{
				int tmp=calc(st,l);
				if (tmp>ans)
				{
					ans=tmp;
					anslen=l;
				}
			}
		printf("Case %d: ",test);
		ansp=-1;
		int ll=anslen*ans;
		for (int st=1;st+ll-1<=n;++st)
		{
			if (lcp(A,st,st+anslen)/anslen+1==ans)
			{
				if (ansp==-1) ansp=st;
				else
				{
					bool fl=false;
					for (int i=0;i<anslen;++i)
					{
						if (tt[st+i]<tt[ansp+i])
						{
							fl=true;
							break;
						}
						if (tt[st+i]>tt[ansp+i]) break;
					}
					if (fl) ansp=st;
				}
			}
		}
		for (int i=0;i<ll;++i)
			printf("%c",tt[i+ansp]);
		puts("");
	}
	return 0;
}
