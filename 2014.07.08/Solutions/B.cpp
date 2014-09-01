#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

struct point{
	int A, B, C, D;
} a[100001];

struct pointx{
	int value, pos;
	bool operator < (const pointx &A) const{
		return(value < A.value);
	}
} c[200001];

int f[200001], n, cnt, pos1[100001], pos2[100001], ans[100001];

bool cmp1(const int &x, const int &y){
	return(a[x].A < a[y].A);
}

bool cmp2(const int &x, const int &y){
	return(a[x].B < a[y].B);
}

inline void insert(int now, int k){
	for (; now <= cnt; now += now & (-now))
		if (k > f[now]) f[now] = k;
		else break;
}

int calc(int now){
	int will = 0;
	for (; now; now -= now & (-now)) will = max(will, f[now]);
	return(will);
}

int main(){
	//freopen("d.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d%d%d", &a[i].A, &a[i].B, &a[i].C, &a[i].D);
		c[++cnt].value = a[i].C; c[cnt].pos = cnt;
		c[++cnt].value = a[i].D; c[cnt].pos = cnt;
	}
	sort(c + 1, c + cnt + 1);
	for (int i = 1; i <= cnt; i++)
		if (c[i].pos & 1) a[(c[i].pos + 1) / 2].C = i;
		else a[c[i].pos / 2].D = i;
	for (int i = 1; i <= n; i++) pos1[i] = i;
	for (int i = 1; i <= n; i++) pos2[i] = i;
	sort(pos1 + 1, pos1 + n + 1, cmp1);
	sort(pos2 + 1, pos2 + n + 1, cmp2);
	memset(f, 0, sizeof(f));
	memset(ans, 0, sizeof(ans));
	int Left = 1;
	for (int i = 1; i <= n; i++)
	{
		while (Left <= n && a[pos2[Left]].B < a[pos1[i]].A) 
		{	
			insert(a[pos2[Left]].D, ans[pos2[Left]]);
			++Left; 
		}
		ans[pos1[i]] = calc(a[pos1[i]].C) + 1;
	}
	int Ans = 0;
	for (int i = 1; i <= n; i++) Ans = max(Ans, ans[i]);
	printf("%d\n", Ans);
}
