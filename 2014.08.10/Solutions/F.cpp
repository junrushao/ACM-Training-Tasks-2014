#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

const int dx[] = {-1, -1, 1, 1};
const int dy[] = {-1, 1, 1, -1};
const int N = 11;
const int S = (1 << 16) + 1;

int flag;
int ret;
int id[N][N];
int vis[N][N][S];
int cnt[S];
char board[N][N];

int valid(int x, int y)
{
	return x >= 0 && x < 10 && y >= 0 && y < 10 && board[x][y] == 'B' && id[x][y] >= 0;
}

void dfs(int x, int y, int s)
{
	if (vis[x][y][s] == flag) return;
	vis[x][y][s] = flag;
	ret = max(ret, cnt[s]);
	for(int i = 0; i < 4; ++ i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (valid(nx, ny) && ! (s >> id[nx][ny] & 1) && board[nx + dx[i]][ny + dy[i]] == '#') {
			dfs(nx + dx[i], ny + dy[i], s + (1 << id[nx][ny]));
		}
	}
}

void solve() {
	for(int i = 0; i < 10; ++ i) {
		scanf("%s", board[i]);
	}
	ret = 0;
	for(int i = 0; i < 10; ++ i) {
		for(int j = 0; j < 10; ++ j) {
			if (board[i][j] == 'W') {
				++ flag;
				board[i][j] = '#';
				dfs(i, j, 0);
				board[i][j] = 'W';
			}
		}
	}
	cout << ret << endl;
}

int main() {
	int test;
	int r = 0;
	memset(id, -1, sizeof id);
	for(int i = 0; i < 4; ++ i) {
		++ r;
		for(int j = 0; j < 4; ++ j) {
			id[r][j * 2 + 2] = i * 4 + j;
		}
		++ r;
		for(int j = 0; j < 4; ++ j) {
			id[r][j * 2 + 1] = i * 4 + j;
		}
	}
	cnt[0] = 0;
	for(int i = 1; i < S; ++ i) {
		cnt[i] = cnt[i - (i & -i)] + 1;
	}
	flag = 0;
	cin >> test;
	for( ; test --; ) {
		solve();
	}
	return 0;
}
