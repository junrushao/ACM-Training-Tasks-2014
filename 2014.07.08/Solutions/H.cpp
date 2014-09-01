#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int n, m, k, Q;

int main()
{
	scanf("%d", &Q);
	for(int i = 1; i <= Q; i++)
	{
		scanf("%d%d%d", &n, &m, &k);
		if(n >= 2 * m + 2)
		{
			n -= 2 * m;
			if((n & -n) == n) printf("0\n");
			else
			{
				int tmp = 1;
				while(tmp * 2 <= n) tmp *= 2;
				if(k > 2 * m + tmp) printf("Thrown\n");
				else printf("%d\n", 0);
			}
		}else
		{
			if(k == n) printf("%d\n", m - (n - 1) / 2);
			else printf("%d\n", k % 2 == n % 2);
		}
	}
	fclose(stdin);
	return 0;
}