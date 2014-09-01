#include<stdio.h>
#include<string.h>
int begin[2505],next[50005],d[50005],d2[50005],v[50005],sta[3005],dl;
bool b[2505];
int main()
{
	int i,j,k,ji,T,TT,l,n,m,source,x,y,h,t,num;
	scanf("%d",&TT);
	for(T=1;T<=TT;T++)
	{
		memset(b,0,sizeof(b));
		memset(v,0,sizeof(v));
		memset(begin,0,sizeof(begin));
		memset(next,0,sizeof(next));
		scanf("%d%d%d",&n,&m,&source);
		dl=1;
		for(i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&j);
			dl++;next[dl]=begin[x];begin[x]=dl;d[dl]=y;d2[dl]=x;
			dl++;next[dl]=begin[y];begin[y]=dl;d[dl]=x;d2[dl]=y;
		}
		h=0;t=1;num=0;sta[1]=source;b[source]=1;
		while(h<t)
		{
			h++;k=sta[h];
			for(i=begin[k];i;i=next[i])
			{
				j=d[i];
				if(b[j]==0)
				{
					b[j]=1;num++;
					v[i]=num;v[i^1]=num;
					//printf("? %d %d %d\n",k,j,num);
					t++;sta[t]=j;
				}
			}
		}
		printf("Case %d:\n",T);
		for(i=2;i<=dl;i+=2)
		{
			if(v[i]==0){num++;v[i]=num;}
			printf("%d %d %d\n",d2[i],d[i],v[i]);
		}
	}
	return 0;
}

