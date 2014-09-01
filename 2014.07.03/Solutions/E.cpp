/*
 * 1.cpp
 *
 *  Created on:
 *      Author:
 */

#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <climits>
#include <cassert>

#include <iostream>
#include <sstream>

#include <string>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <bitset>

#include <utility>
#include <numeric>
#include <functional>
#include <algorithm>
#define LL long long
using namespace std;

LL oo=1000000007;
LL c[55][55];
LL px[55],py[55];
int g[21][21][55];
LL p[256][256];
LL dp[55][250][55];
/*
inline LL f(int i,int j) {
	if (i == 0 || j == 0) return 0;
	return c[k][i]*c[k-i][j]%oo*p[i][x]%oo*p[j][y]%oo;
}
*/
void prepare()
{
	c[0][0] = 1;
	for (int i=1;i<=51;i++) c[i][i]=c[i][0]=1;
	for (int i=2;i<=51;i++)
	{
		for (int j=1;j<=i-1;j++)
		{
		c[i][j]=(c[i-1][j]+c[i-1][j-1])%oo;
		//printf("%d ",c[i][j]);
		}
	//printf("\n");
	}
	for (int i=1;i<=251;i++) p[i][0]=1;
	for (int i=1;i<=251;i++)
	for (int j=1;j<=251;j++) p[i][j]=(p[i][j-1]*i)%oo;
	for (int k=1;k<=50;k++)
	{
		dp[k][0][0]=1;
		for (int i=0;i<=200;i++)
		for (int j=0;j<=50;j++)
		if (dp[k][i][j])
		{
			LL v=dp[k][i][j];
			dp[k][i+1][j]=(dp[k][i+1][j]+v*j)%oo;
			dp[k][i+1][j+1]=(dp[k][i+1][j+1]+v*(k-j))%oo;
		}
	}
}
void work(int lab)
{
	int n,m,k;
	int x, y;
	printf("Case %d: ",lab);
	scanf("%d %d %d",&m,&n,&k);
	if (g[m][n][k]!=-1)
	{
		printf("%d\n",g[m][n][k]);
		return;
	}
//	printf("n = %d, m = %d\n", n, m);
	if ( n % 2 == 1 || m % 2 == 1 )
		x = y = (n + 1) * (m + 1) / 2;
	else {
		x = ((n + 1) * (m + 1) + 1) / 2;
		y = ((n + 1) * (m + 1) - 1) / 2;
	}

//	printf("x= %d y= %d\n",x,y);
	if (x==0||y==0)
	{
		printf("%d\n",g[m][n][k]=k);return;
	}
	if (k==1)
	{
		printf("0\n");return;
	}
	static int F[55][55];
	for (int i = 1; i <= k - 1; ++i)
		for (int j = 1; j <= k - i; ++j) {
			F[i][j] = c[k][i]*c[k-i][j]%oo*dp[i][x][i]%oo*dp[j][y][j]%oo;
		//	cout << i << ' ' << j << ' ' << F[i][j] << endl;
		//	if (F[i][j] < 0) cout << i << ' ' << j << endl;
		}
//	puts("");
	int ans = 0;
	for (int i = 1; i <= k - 1; i++)
		for (int j = 1; j <= k - i; j++) {
			ans+=F[i][j];
			if (ans>=oo) ans-=oo;
		}
	ans %= oo;
//	ans=(ans+f(i,j)+f(i-1,j-1)-f(i-1,j)-f(i,j-1)+2*oo)%oo;
	g[m][n][k]=ans;
	printf("%d\n",ans);
}
int main() {
	int times;
	memset(g,-1,sizeof(g));
	scanf("%d",&times);
	prepare();
	for (int i=1;i<=times;i++)
	work(i);
	return 0;
}
