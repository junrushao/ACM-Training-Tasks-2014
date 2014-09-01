#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>

using namespace std;

int Dir[7][2] = {{-1, 0}, {0, -1}, {1, -1}, {-1, 1}, {0, 1}, {1, 0}, {0, 0}};
int ans, n, m, a[11][2], tx, ty, k, l;
vector< pair<int, int> > c, A;
vector< vector< pair<int, int> > > q;
set< pair<int, int> > stone;
map< vector< pair<int, int> >, int > events;
inline void soso(int step);

inline void soso1(int index, int value){
	//printf("%d\n", index);
	if (index >= n) 
	{
		if (abs(A[0].first - tx) + abs(A[0].second - ty) > 2 * (20 - value)) return;  
		if (events.find(A) == events.end())
		{
			events[A] = value + 1;
			if (tx == A[0].first && ty == A[0].second) l = k;
			q.push_back(A); ++k;
		}
		return;
	}
	for (int i = 0; i < 6; i++)
	{
		int aimx = A[index].first + Dir[i][0], 
			aimy = A[index].second + Dir[i][1];
		pair<int, int> now(aimx, aimy);
		if (stone.find(now) != stone.end()) continue;
		bool ok = true;
		for (int j = 0; j < index; j++)
			if (index != j && aimx == A[j].first && aimy == A[j].second)
			{
				ok = false;
				break;
			}
		if (!ok) continue;
		for (int j = 0; j <= index + 1 && j < n && ok; j++)
			if (j != index)
		{
			bool touch = false;
			for (int k = 0; k < 6; k++)
				if (aimx + Dir[k][0] == A[j].first && aimy + Dir[k][1] == A[j].second)
				{
					touch = true;
					break;
				}
			//printf("%d %d %d\n", index, j, touch);
			//printf("%d %d %d %d\n", aimx, aimy, A[j].first, A[j].second);
			if (touch) 
				 if (abs(index - j) != 1) ok = false;
				 else;
			else
				 if (abs(index - j) == 1) ok = false;
		}
		if (!ok) continue;
	//	printf("alive? %d %d\n", index, i);
	//	printf("haha %d %d\n", index, i);
		A[index].first += Dir[i][0]; 
		A[index].second += Dir[i][1];
		soso1(index + 2, value);
		A[index].first -= Dir[i][0]; 
		A[index].second -= Dir[i][1];
	//	printf("? %d %d\n", index, i);
	}
	bool ok = true;
	int aimx = A[index].first, aimy = A[index].second;
	for (int j = 0; j <= index + 1 && j < n && ok; j++)
		if (j != index)
	{
		bool touch = false;
		for (int k = 0; k < 6; k++)
			if (aimx + Dir[k][0] == A[j].first && aimy + Dir[k][1] == A[j].second)
			{
				touch = true;
				break;
			}
		//printf("%d %d %d\n", index, j, touch);
		//printf("%d %d %d %d\n", aimx, aimy, A[j].first, A[j].second);
		if (touch) 
			 if (abs(index - j) != 1) ok = false;
			 else;
		else
			 if (abs(index - j) == 1) ok = false;
	}
	for (int j = 0; j < index && ok; j++)
		if (index != j && aimx == A[j].first && aimy == A[j].second)
		{
			ok = false;
			break;
		}
	if (ok) soso1(index + 2, value);
}

int main(){
	//freopen("c.in", "r", stdin);
	events.clear();
	for (;;)
	{
		scanf("%d", &n);
		if (!n) return 0;
		q.clear();
		for (int i = 1; i <= n; i++) scanf("%d%d", &a[i][0], &a[i][1]);
		stone.clear();
		scanf("%d", &m);
		for (int i = 1; i <= m; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			pair<int, int> now(x, y);
			if (stone.find(now) == stone.end()) stone.insert(now);
		}
		scanf("%d%d", &tx, &ty);
		events.clear();
		c.clear();
		for (int i = 1; i <= n; i++) c.push_back(make_pair(a[i][0], a[i][1]));
		q.push_back(c); events[c] = 0;
		
		for (k = 0, l = 0; l <= k; l++)
		{
			A = q[l]; int value = events[A];
			//printf("%d\n", value);
			//for (int i = 0; i < A.size(); i++) printf("%d %d\n", A[i].first, A[i].second);
			//printf("\n");
			//if (!(l % 1000)) printf("%d %d\n", l, value); 
			if (A[0].first == tx && A[0].second == ty)
			{
				printf("%d\n", value);
				//printf("%d %d\n", l, events.size());
				break;
			}	
			soso1(0, value); soso1(1, value);
		}
	}
}
