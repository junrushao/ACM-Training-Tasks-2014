#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int n, m, k, blg[55][77], x, y, len, X, Y, dx[555], dy[555];
char ans[55][77], pth[11111], id[11];
bool lm[55][77], rm[55][77], flag;
void mrk(int x, int y, char c1, char c2)
{
	if(c1 == 'A')
	{
		if(c2 == 'E' or c2 == 'D') lm[x][y] = rm[x][y] = true;
		if(c2 == 'C' or c2 == 'B' or c2 == 'H' or c2 == 'A') lm[x][y] = true;
	}
	if(c1 == 'B')
	{
		if(c2 == 'E' or c2 == 'D' or c2 == 'F') lm[x][y] = rm[x][y] = true;
		if(c2 == 'C' or c2 == 'B' or c2 == 'A' or c2 == 'H') lm[x][y] = true;
	}
	if(c1 == 'C')
	{
		if(c2 == 'D' or c2 == 'E' or c2 == 'F' or c2 == 'G') rm[x][y] = true;
	}
	if(c1 == 'D')
	{
		if(c2 == 'D' or c2 == 'E' or c2 == 'F' or c2 == 'G') rm[x][y] = true;
		if(c2 == 'H') lm[x][y] = rm[x][y] = true;
	}
	if(c1 == 'E')
	{
		if(c2 == 'D' or c2 == 'E' or c2 == 'F' or c2 == 'G') rm[x][y] = true;
		if(c2 == 'H' or c2 == 'A') lm[x][y] = rm[x][y] = true;
	}
	if(c1 == 'F')
	{
		if(c2 == 'D' or c2 == 'E' or c2 == 'F' or c2 == 'G') rm[x][y] = true;
		if(c2 == 'H' or c2 == 'A' or c2 == 'B') lm[x][y] = rm[x][y] = true;
	}
	if(c1 == 'G')
	{
		if(c2 == 'A' or c2 == 'B' or c2 == 'C' or c2 == 'H') lm[x][y] = true;
	}
	if(c1 == 'H')
	{
		if(c2 == 'C' or c2 == 'B' or c2 == 'H' or c2 == 'A') lm[x][y] = true;
		if(c2 == 'D') lm[x][y] = rm[x][y] = true;
	}
}
bool check(int x, int y)
{return 1 <= x and x <= n and 1 <= y and y <= m;}
int main()
{
	dx['A'] = -1; dy['A'] = 0;
	dx['B'] = -1; dy['B'] = +1;
	dx['C'] = 0; dy['C'] = +1;
	dx['D'] = +1; dy['D'] = +1;
	dx['E'] = +1; dy['E'] = 0;
	dx['F'] = +1; dy['F'] = -1;
	dx['G'] = 0; dy['G'] = -1;
	dx['H'] = -1; dy['H'] = -1;
	
	for(;;)
	{
		scanf("%d%d%d", &n, &m, &k);
		if(!n or !m or !k) break;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) blg[i][j] = 0, ans[i][j] = '.';
		for(int i = 1; i <= k; i++)
		{
			scanf("%s%d%d%d", &id, &x, &y, &len);
			X = x; Y = y;
			for(int i = 0; i < len; i++)
			{
				scanf("%c", &pth[i]);
				if(pth[i] < 'A' or pth[i] > 'H') scanf("%c", &pth[i]);
			}
			
			for(int i = 0; check(X, Y) and i < len; i++)
			{
				//printf("XY %d %d\n", X, Y);
				X = X + dx[pth[i]];
				Y = Y + dy[pth[i]];
			}
			if(!check(X, Y)) {printf("REGION %c GOES OUTSIDE THE ARRAY\n", id[0]); continue;}
			if(X != x or Y != y) {printf("REGION %c BOUNDARY IS NOT CLOSED\n", id[0]); continue;}
			X = x; Y = y;
			for(int i = 0; ans[X][Y] == '.' and i < len; i++)
			{
				X = X + dx[pth[i]];
				Y = Y + dy[pth[i]];
			}
			if(ans[X][Y] != '.') {printf("REGION %c BOUNDARY INTERSECTS REGION %c\n", id[0], ans[X][Y]); continue;}
			for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) lm[i][j] = rm[i][j] = false;
			pth[len] = pth[0];
			for(int i = 0; i < len; i++) 
			{
				x = x + dx[pth[i]];
				y = y + dy[pth[i]];
				mrk(x, y, pth[i], pth[i + 1]);
			}
			for(int i = 1; i <= n; i++)
			{
				flag = false;
				for(int j = 1; j <= m; j++)
				{
					if(lm[i][j]) flag = true;
					if(flag) ans[i][j] = id[0];
					if(rm[i][j]) flag = false;
				}
			}
		}
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++) printf("%c", ans[i][j]);
			printf("\n");
		}
		printf("\n");
	}
	fclose(stdin);
	return 0;
}
