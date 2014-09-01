#include <cstdio>

int main()
{
	int n;
	scanf("%d",&n);
	if (n%6 == 1 || n%6 == 5)
	{
		puts("Yes");
		for (int i=1;i<=n/2;i++)
			printf("%d ",i*2);
		for (int i=n/2+1;i<n;i++)
			printf("%d ",(i-n/2)*2-1);
		printf("%d\n",n);
	}
	else
		puts("No");
	return 0;
}
