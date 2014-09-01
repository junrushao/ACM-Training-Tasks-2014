#include <cstdio>
#include <cstring>
#define bh(i,j) (((i) - 1) * c + (j))
const int N = 5010,M = 1000000,aa[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
int r,c,cost,ind,x,x1,y1,x2,y2,tot,h,t,nt[M],pt[M],last[M],co[M],f[N],pp[N][2],q[5000000];
bool bo[N];
char ch,a[N][N];
void edge(int x,int y,int z){
	last[x] = nt[last[x]] = ++ind;
	pt[ind] = y,co[ind] = z;
}
void p(int i,int j,int cost){
	for (int k = 0;k < 4;++k){
		int nx = i + aa[k][0],ny = j + aa[k][1];
		if (nx > 0 && ny > 0 && nx <= r && ny <= c && (a[nx][ny] == 'Y' || a[nx][ny] == 'C' || a[nx][ny] == '*' || a[nx][ny] == 'P')) edge(bh(nx,ny),bh(i,j),cost);
	}
}
int main(){
	for (;;){
		scanf("%d%d%d",&r,&c,&cost);
		if (feof(stdin)) return 0;
		memset(nt,0,sizeof(nt));
		memset(pt,0,sizeof(pt));
		memset(last,0,sizeof(last));
		memset(co,0,sizeof(co));
		memset(bo,0,sizeof(bo));
		tot = 0;
		ind = r * c;
		for (int i = 1;i <= ind;++i) last[i] = i,f[i] = 1010000000;
		for (int i = 1;i <= r;++i){
			for (ch = getchar();ch != 'Y' && ch != 'C' && ch != '*' && ch != '#' && ch != 'P';ch = getchar());
			a[i][1] = ch;
			for (int j = 2;j <= c;++j) a[i][j] = getchar();
		}
		for (int i = 1;i <= r;++i)
			for (int j = 1;j <= c;++j){
				if (a[i][j] == 'Y') x1 = i,y1 = j,p(i,j,0);
				if (a[i][j] == 'C') x2 = i,y2 = j,p(i,j,0);
				if (a[i][j] == '*') p(i,j,cost);
				if (a[i][j] == 'P') p(i,j,0),pp[++tot][0] = i,pp[tot][1] = j;
			}
		for (int i = 1;i < tot;++i)
			for (int j = i + 1;j <= tot;++j) edge(bh(pp[i][0],pp[i][1]),bh(pp[j][0],pp[j][1]),0),edge(bh(pp[j][0],pp[j][1]),bh(pp[i][0],pp[i][1]),0);
		for (h = t = 0,bo[q[++t] = bh(x1,y1)] = 1,f[bh(x1,y1)] = 0;h < t;){
			bo[x = q[++h]] = 0;
			for (int i = nt[x];pt[i];i = nt[i])if (f[x] + co[i] < f[pt[i]]){
				f[pt[i]] = f[x] + co[i];
				if (!bo[pt[i]]) bo[q[++t] = pt[i]] = 1;
			}
		}
		if (f[bh(x2,y2)] > 1000000000) printf("Damn teoy!\n");
		else printf("%d\n",f[bh(x2,y2)]);
	}
	return 0;
}