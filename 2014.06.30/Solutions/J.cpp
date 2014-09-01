#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <map>

using namespace std;

#define maxn 110
#define maxm 100010

struct edge
{
	int to,dist;
	edge *next;
}e[maxm],*head[maxn];

int ne=0,cnt=0;
map <string,int> m;
string name[maxn];
int vis[maxn],dis1[maxn],dis2[maxn];
int q[maxm];
char s[maxm];

inline void add_edge(int from,int to,int dist)
{
	e[ne].to=to;
	e[ne].dist=dist;
	e[ne].next=head[from];
	head[from]=&e[ne++];
}

inline int get_num(string s)
{
	if (!m.count(s))
	{
		m[s]=++cnt;
		name[cnt]=s;
	}
	return m[s];
}

inline void spfa()
{
	int op=0,cls=1;
	q[1]=1;
	while (op != cls)
	{
		int x=q[++op];
		for (edge *p=head[x];p;p=p->next)
		{
			if (dis1[p->to] > dis2[x])
				dis1[p->to]=dis2[x];
			if (dis2[p->to] > dis2[x]+p->dist)
			{
				dis2[p->to]=dis2[x]+p->dist;
				if (!vis[p->to])
				{
					vis[p->to]=1;
					q[++cls]=p->to;
				}
			}
		}
	}
}

int main()
{
	memset(dis1,0x3f,sizeof(dis1));
	memset(dis2,0x3f,sizeof(dis2));
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		string temp;
		cin >> temp;
		int now=get_num(temp);
		int l=temp.size()+6;
		int k;
		scanf("%d",&k);
		for (int j=1;j<=k;j++)
		{
			cin >> temp;
			int a=get_num(temp);
			add_edge(now,a,l);
		}
	}
	gets(s);
	gets(s);
	int l=strlen(s);
	dis1[1]=dis2[1]=l;
	spfa();
	int ans=0;
	for (int i=1;i<=n;i++)
		if (dis1[i] <= 140)
			ans++;
	printf("%d\n",ans);
	for (int i=1;i<=n;i++)
		if (dis1[i] <= 140)
			cout << name[i] << endl;
	return 0;
}
