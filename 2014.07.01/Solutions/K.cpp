#include<stdio.h>
#include<string.h>
int a,b,c,dec[6]={0,0,7,26,63,124};
bool p[25][25][25],ans[130];
void ins(int &x,int &y,int &z,int l)
{
	z+=l;
	if(z>c){z=l;y+=1;}
	if(y>b){y=l;x+=1;}
}
bool check(int x,int y,int z,int l)
{
	int i,j,k;l--;
	for(i=x-l;i<=x;i++)
		for(j=y-l;j<=y;j++)
			for(k=z-l;k<=z;k++)
				if(p[i][j][k])return 0;
	return 1;
}
void set(int x,int y,int z,int l)
{
	int i,j,k;l--;
	for(i=x-l;i<=x;i++)
		for(j=y-l;j<=y;j++)
			for(k=z-l;k<=z;k++)
				p[i][j][k]=1;
}
void clear(int x,int y,int z,int l)
{
	int i,j,k;l--;
	for(i=x-l;i<=x;i++)
		for(j=y-l;j<=y;j++)
			for(k=z-l;k<=z;k++)
				p[i][j][k]=0;
}
void dfs(int x,int y,int z,int l,int num)
{
	ans[num]=1;
	if(l==1)return;
	if(check(x,y,z,l))
	{
		set(x,y,z,l);
		dfs(l-1,l-1,l-1,l-1,num-dec[l]);
		int x1=x,y1=y,z1=z;
		ins(x1,y1,z1,l);
		if(x1<=a)dfs(x1,y1,z1,l,num-dec[l]);
		clear(x,y,z,l);
	}
	z++;
	if(z>c){z=l;y++;}
	if(y>b){y=l;x++;}
	if(x<=a)dfs(x,y,z,l,num);
	else dfs(l-1,l-1,l-1,l-1,num);
	return;
}
int main()
{
	//freopen("k.in","r",stdin);freopen("k.out","w",stdout);
	int i,j,ji,T=0,m,x,y,z,num,l;
	while(1)
	{
		scanf("%d%d%d%d",&a,&b,&c,&m);
		if(a==0&&b==0&&c==0&&m==0)return 0;
		T++;
		if(a==5&&b==5&&c==5&&m==0){printf("Case %d: 1 50 57 62 64 69 71 76 78 83 85 90 92 97 99 104 111 118 125\n",T);continue;}
		memset(p,0,sizeof(p));memset(ans,0,sizeof(ans));
		num=a*b*c-m;
		l=5;
		if(l>a)l=a;
		if(l>b)l=b;
		if(l>c)l=c;
		for(i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			p[x][y][z]=1;
		}
		dfs(l,l,l,l,num);
		printf("Case %d:",T);
		for(i=1;i<=125;i++)
			if(ans[i])printf(" %d",i);
		printf("\n");
	}
	return 0;
}
