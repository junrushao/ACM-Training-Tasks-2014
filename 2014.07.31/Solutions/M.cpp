#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int lim = 10000000;

bool b[lim];
int p[1000000], tot;

void prepare()
{
	tot = 0;
	for(int i = 2; i < lim; ++i)
	{
		if(!b[i])
			p[tot++] = i;
		for(int j = 0; j < tot && (long long)i * p[j] < lim; ++j)
		{
			b[i * p[j]] = true;
			if(i % p[j] == 0)
				break;
		}
	}
}

char s[1000000 + 10];

long long fastmul(long long x, long long b, long long Mod)
{
	long long ret = 1;
	while(b)
	{
		if(b & 1)
			ret = ret * x % Mod;
		x = x * x % Mod;
		b >>= 1;
	}
	return ret;
}

long long calc(int n, long long p)
{
	p *= 9;
	long long ret = fastmul(10, n, p);
	ret -= 1;
	if(ret < 0) ret += p;
	return ret;
}

int main()
{
	prepare();
	scanf("%s", s);
	int Len = strlen(s), C = 0;
	for(int i = 0; i < Len; ++i)
		C += s[i] - '0';
	for(int i = 0; i < tot; ++i)
	{
		int P = p[i];
		if((long long)C % P == 0 || calc(Len, P) == 0)
		{
			printf("%d\n", P);
			break;
		}
	}
	return 0;
}
