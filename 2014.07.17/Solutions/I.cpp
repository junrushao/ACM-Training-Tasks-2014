#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>

const int oo=1073741819,mo=19880830;

using namespace std;

vector <int> stack;
map < int , long long > Map;
int next[2000000],sora[2000000],cost[2000000],st[500000],u[500000],tail[500000],b[2000000];
int v[500000],col[500000],d[500000],rt[3][500000];
int ss,n,m,m1,s,t,q;

struct dist{
	int m;
	long long c;
}D[3][500000],ans[500000];

void origin()
{
    ss=n;
    for (int i=1;i<=n;i++) tail[i]=i,next[i]=0;
    for (m1=1;m1<=n+2;m1<<=1) ;
    for (int i=1;i<=m1+m1;i++) b[i]=0;
    for (int i=1;i<=n;i++) b[i+m1]=i,d[i]=oo;
    for (int i=1;i<=n;i++) {
        v[i]=col[i]=0;
        for (int j=0;j<=2;j++)
            D[j][i].m=oo,D[j][i].c=0,rt[j][i]=0;
        ans[i].m=oo,ans[i].c=0;
    }
  	Map.clear(),stack.clear();
}

void link(int x,int y,int z)
{
	++ss,next[tail[x]]=ss,tail[x]=ss,sora[ss]=y,cost[ss]=z,next[ss]=0;
	++ss,next[tail[y]]=ss,tail[y]=ss,sora[ss]=x,cost[ss]=z,next[ss]=0;
}

int mind(int x,int y)
{
    return (d[x]<d[y]) ? x : y;
}

void change(int x,int w)
{
    d[x]=w;
    for (x=((x+m1)>>1);x;x>>=1) 
        b[x]=mind(b[x<<1],b[(x<<1)+1]);
}

void dij(int e,int &r)
{
    for (;d[b[1]]!=oo;) {
        int x=b[1],cos=d[x];
        st[++r]=x,D[e][x].m=cos;
        change(x,oo);
        for (int i=x,ne;next[i];) {
            i=next[i],ne=sora[i];
            if (d[ne]!=oo && cos+cost[i]<d[ne] && v[x]==v[ne]) {
                rt[e][ne]=x;
                change(ne,cos+cost[i]);
            }
        }
    }
}

void spfa(int s,int e)
{
    for (int i=0;i<=n;i++) change(i,oo+1);
    change(s,0);
    int r=0;
    dij(e,r);
    D[e][st[1]].c=1;
    for (int i=1;i<=r;i++) {
        int x=st[i];
        for (int i=x,ne;next[i];) {
            i=next[i],ne=sora[i];
            if (D[e][x].m+cost[i]==D[e][ne].m)
                (D[e][ne].c+=D[e][x].c)%=mo;
        }
    }
}

void dfs(int x,int level)
{
	stack.push_back(x);
	v[x]=level;
	for (int i=x,ne;next[i];) {
		i=next[i],ne=sora[i];
		if (D[0][x].m+cost[i]==D[0][ne].m && !v[ne] && !col[ne]) dfs(ne,level);
	}
}

bool cmp(int i,int j)
{
	if (v[i]!=v[j]) return v[i]>v[j];
	return col[i]<col[j];
}

void updata(int w,long long c)
{
	map < int , long long > :: iterator it=Map.find(w);
	if (it==Map.end()) {
		Map[w]=c;
		return ;
	}
	it->second=((it->second+c)%mo+mo)%mo;
	if (!(it->second)) Map.erase(it);
}

void add_o_d(int x,int e)
{
	for (int i=x,ne;next[i];) {
    i=next[i],ne=sora[i];
    if (v[ne]<v[x]) {
    	int cos=D[2][x].m+cost[i]+D[1][ne].m;
  		long long tmp=(D[2][x].c*D[1][ne].c)%mo;
  		if (!tmp) return ; 
    	updata(cos,tmp*e);
  	}
  }
}

void add_u_d(int x,int e)
{
	for (int i=x,ne;next[i];) {
    i=next[i],ne=sora[i];
    if (e*v[ne]>e*v[x]) {
      int cos;
      long long tmp;
      if (e==1) {
      	cos=D[0][ne].m+cost[i]+D[1][x].m;
      	tmp=(D[0][ne].c*D[1][x].c)%mo;
      }
      else {
      	cos=D[0][x].m+cost[i]+D[1][ne].m;
      	tmp=(D[0][x].c*D[1][ne].c)%mo;
      }
      if (!tmp) return ;
      updata(cos,-tmp*e);
    }
  }
}

int main()
{
    for (int test=1;scanf("%d%d%d%d%d",&n,&m,&s,&t,&q)==5;test++) {
    		if (!n && !m && !s && !t && !q) break;
        origin();
        for (int i=1;i<=m;i++) {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            link(x,y,z);
        }
        spfa(s,0);
        spfa(t,1);
        for (int i=t;i;i=rt[0][i]) col[i]=1;
        for (int i=t,cnt=1;i;i=rt[0][i],++cnt) {
        	stack.clear();
        	dfs(i,cnt);
        	for (int i=1;i<(int)stack.size();i++) {
        		int x=stack[i];
        		d[x]=oo+1;
        		for (int i=x,ne;next[i];) {
        			i=next[i],ne=sora[i];
        			if (!v[ne] && D[0][ne].m+cost[i]<d[x]) 
        				change(x,D[0][ne].m+cost[i]);
        		}
        	}
        	int r=0;
        	dij(2,r);
        	for (int i=1;i<=r;i++) {
        		int x=st[i];
        		for (int i=x,ne;next[i];) {
        			i=next[i],ne=sora[i];
        			if (!v[ne]) {
        				if (D[0][ne].m+cost[i]==D[2][x].m)
        					(D[2][x].c+=D[0][ne].c)%=mo;
        			}	
        		}
        		for (int i=x,ne;next[i];) {
        			i=next[i],ne=sora[i];
        			if (v[ne]==v[x] && !col[ne]) {
        				if (D[2][x].m+cost[i]==D[2][ne].m)
        					(D[2][ne].c+=D[2][x].c)%=mo;
        			}
        		}
        	}
        }
        for (int i=1;i<=n;i++) u[i]=i;
        sort(u+1,u+n+1,cmp);
        for (int i=1;i<=n;i++) {
        	int x=u[i];
        	add_u_d(x,1);
        	if (!col[x]) {
        		add_o_d(x,1);
        	}
        	else {
        		if (Map.empty()) ans[x].m=oo,ans[x].c=0;
        		else {
        			map < int , long long > :: iterator it;
        			it=Map.begin();
        			if (it!=Map.end())
        				ans[x].m=it->first,ans[x].c=it->second;
        		}
        		for (int j=i-1;j>=1 && v[u[j]]==v[u[i]];j--)  
        			add_o_d(u[j],-1);
        		for (int j=i;j>=1 && v[u[j]]==v[u[i]];j--)  
        			add_u_d(u[j],-1);
        	}
        }
        printf("Case %d:",test);
        for (int i=1;i<=q;i++) {
        	int x; 
        	scanf("%d",&x);
        	long long Ans=0,X=1;
        	for (int j=1;j<=n;j++) {
        		if (ans[j].m==oo) {
        			if (col[j]) ans[j].m=0,ans[j].c=0;
        			else {
        				ans[j].m=D[0][t].m,ans[j].c=D[0][t].c;
        				int x=j;
        				for (int i=x,ne;next[i];) {
        					i=next[i],ne=sora[i];
        					if (D[0][x].m+cost[i]+D[1][ne].m==D[0][t].m) ans[j].c=((ans[j].c-D[0][x].c*D[1][ne].c)%mo+mo)%mo;
        				}
        				if (ans[j].m==oo) ans[j].m=0,ans[j].c=0;
        			}
        		}
        		Ans=(Ans+X*ans[j].m)%mo;
        		X=(X*x)%mo;
        		Ans=(Ans+ans[j].c*X)%mo;
        		X=(X*x)%mo;
        	}
        	printf(" %lld",Ans);
        }
        printf("\n\n");
    }
    return 0;
}
