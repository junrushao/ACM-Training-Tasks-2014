#include <cstdio>
#include <iostream>
#include <string>
#include <map>

using namespace std;

#define maxn 1010

string name[20];
map <string,string> m;
int ans[maxn];

int main()
{
	for (int i=1;i<=4;i++)
	{
		cin >> name[i];
		m[name[i]]="gold";
	}
	for (int i=5;i<=8;i++)
	{
		cin >> name[i];
		m[name[i]]="silver";
	}
	for (int i=9;i<=12;i++)
	{
		cin >> name[i];
		m[name[i]]="bronze";
	}
	int n;
	scanf("%d",&n);
	int max=-1;
	for (int i=1;i<=n;i++)
	{
		int k;
		scanf("%d",&k);
		ans[i]=0;
		for (int j=1;j<=k;j++)
		{
			string temp1,temp2;
			cin >> temp1;
			cin >> temp2;
			cin >> temp2;
			if (m[temp1] == temp2)
				ans[i]++;
		}
		if (ans[i] > max)
			max=ans[i];
	}
	int cnt=0;
	for (int i=1;i<=n;i++)
		if (ans[i] == max)
			cnt++;
	printf("%d\n",cnt*5);
	return 0;
}
