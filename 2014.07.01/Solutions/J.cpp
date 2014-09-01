#include<stdio.h>
#include<string.h>
bool b[30];
char s[1005];
int main()
{
	int i,j,ji,T,TT,ans=0,l;
	scanf("%d",&TT);gets(s);
	for(T=1;T<=TT;T++)
	{
		ans=0;gets(s+1);l=strlen(s+1);
		for(i=1;i<=l;i++)
		{
			ji=0;memset(b,0,30);
			for(j=i;j<=l;j++)
			{
				if(b[s[j]-97]==0)
				{
					b[s[j]-97]=1;ji++;
				}
				else
				{
					b[s[j]-97]=0;ji--;
				}
				if(ji<=1)ans++;
			}
		}
		printf("Case %d: %d\n",T,ans);
	}
	return 0;
}

