#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100005;

long long mi[N], h1[N], h2[N];
int test;
char str[N], s2[N], miwen[N], mingwen[N];

int main() {
	mi[0] = 1;
	for (int i = 1; i <= 100000; i++)
		mi[i] = mi[i - 1] * 31;
	scanf("%d", &test);
	while (test--)
	{
		scanf("%s", str + 1);
		for (int c = 'a'; c <= 'z'; c++)
		{
			miwen[c] = str[c - 'a' + 1];
			mingwen[str[c - 'a' + 1]] = c;
		}

		scanf("%s", str + 1);
		int len = strlen(str + 1);
		h1[0] = h2[0] = 0;
		for (int i = 1; i <= len; i++)
		{
			s2[i] = miwen[str[i]];
			h1[i] = h1[i - 1] * 31 + str[i] - 'a';
			h2[i] = h2[i - 1] * 31 + s2[i] - 'a';
		}

		int ans = len;
		for (int i = 1; i <= len; i++)
		{
			if (len - i > i)
				continue;
			int lnow = len - i;
			if (h2[len] - h2[i] * mi[lnow] == h1[len - i])
			{
				ans = i;
				break;
			}
		}

		for (int i = 1; i <= ans; i++)
			printf("%c", str[i]);
		for (int i = 1; i <= ans; i++)
			printf("%c", mingwen[str[i]]);
		printf("\n");
	}

	return 0;
}
