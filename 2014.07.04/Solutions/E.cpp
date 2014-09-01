#include<iostream>
#include<cstdio>
using namespace std;
const int Mo = 1000000009;
const int N = 111;
int a;
int n1, n0;
int c1, c0;
char s1[N], s2[N];
long long f[N][N];
long long dp[N][N];
int n, m, k;
int main(){
  f[0][0] = 1;
  for(int i = 1;i <= 100; i++)
  {
  	f[i][0] = 1;
  	for (int j = 1 ; j <= i ;j++)
  	{
  		f[i][j] = f[i-1][j] + f[i-1][j-1];
  		if (f[i][j] >= Mo) f[i][j] -= Mo;
  	}
  }
  while (scanf("%d%d%d", &n , &k, &m) == 3){
  		scanf("%s",s1);
  		scanf("%s",s2);
  		n1 = 0;  		n0 = 0;
  		for (int i = 0; i <= k; i++)
  			for (int j = 0; j <= n; j++)
  				dp[i][j] = 0;
  		for (int i = 0; i < n; i++)
  			if (s1[i] != s2[i]) ++n1;
  		dp[0][n1] = 1;
  		for (int i = 0; i < k; i++)
  			for ( int j = 0; j <= n; j++)
  			{
  				c1 = j;
  				c0 = n - j;
  				for (int l = 0; l <= m; l++)
  				{
  					int p = l, q = m - l;
  					if (j - p + q >= 0 && j - p + q <= n){
  						dp[i + 1][ j - p + q ] += (((f[c1][p] * f[c0][q]) % Mo) * dp[ i ][ j ]) % Mo;
  					if (dp[i + 1][j - p + q] >= Mo) dp[i + 1][j - p + q] -= Mo;
					}
  				}
  			//	printf("%d %d %lld\n", i, j, dp[i][j]);	
  			}
  //		for (int j = 0; j <= n ;j ++) printf("%d %d %lld\n", k, j, dp[k][j]);
  		cout << dp[k][0] << endl;
  }
}
