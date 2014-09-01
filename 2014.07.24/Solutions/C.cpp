#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

const int N = 1000 + 10;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
const int cx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int cy[] = {-1, 0, 1, 1, 1, 0, -1, -1};

int n, m;
int to[N][N][4];
char s[N][N];
int dis[N][N][8];
int cost[N][N][4];

struct Info
{
	int x, y, d;
	Info() {}
	Info(int nx1, int ny1, int nx2, int ny2) {
		x = nx1;
		y = ny1;
		for(int i = 0; i < 8; ++ i) {
			if (nx2 == nx1 + cx[i] && ny2 == ny1 + cy[i]) {
				d = i;
				break;
			}
		}
	}
	Info(int x, int y, int d) : x(x), y(y), d(d) {}
};

int valid(int nx1, int ny1, int nx2, int ny2)
{
	if (nx1 == nx2 && ny1 == ny2) return false;
	if (abs(nx1 - nx2) > 1) return false;
	if (abs(ny1 - ny2) > 1) return false;
	return true;
}

int valid(int i, int j)
{
	return i >= 1 && i <= n + 2 && j >= 1 && j <= m + 2;
}

int ok(int nx1, int ny1, int nx2, int ny2)
{
	if (nx1 > 1 && nx1 < n + 2 && ny1 > 1 && ny1 < m + 2) return false;
	if (nx2 > 1 && nx2 < n + 2 && ny2 > 1 && ny2 < m + 2) return false;
	return true;
}

int solve() {
	memset(s, 0, sizeof s);
	for(int i = 1; i <= 2 * n + 1; ++ i) {
		gets(s[i] + 1);
	}

	int sx1, sy1, sx2, sy2;
	for(int i = 1; i <= n + 2; ++ i) {
		for(int j = 1; j <= m + 2; ++ j) {
			int x = (i - 1) * 2;
			int y = (j - 1) * 2;
			if (s[x][y] == '1') {
				sx1 = i; 
				sy1 = j;
			}
			if (s[x][y] == '2') {
				sx2 = i; 
				sy2 = j;
			}

			for(int d = 0; d < 4; ++ d) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (to[i][j][d] == false) continue;
				if (s[nx][ny] == '|' || s[nx][ny] == '-') {
					to[i][j][d] = false;
				}
				cost[i][j][d] = (s[nx][ny] == '.');
			}
		}
	}

	deque<Info> que;
	int ux, uy, ud;
	for(int i = 0; i < 8; ++ i) {
		if (sx2 == sx1 + cx[i] && sy2 == sy1 + cy[i]) {
			ux = sx1;
			uy = sy1;
			ud = i;
			break;
		}
	}
	memset(dis, -1, sizeof dis);
	que.push_back(Info(ux, uy, ud));
	dis[ux][uy][ud] = 0;
	Info cur, nxt;
	int ax1, ax2, ay1, ay2;
	int bx1, bx2, by1, by2;


	for( ; que.size(); ) {
		cur = que.front();
		que.pop_front();

		ax1 = cur.x;
		ay1 = cur.y;
		ax2 = ax1 + cx[cur.d];
		ay2 = ay1 + cy[cur.d];
		for(int d = 0; d < 4; ++ d) {
			if (! to[ax1][ay1][d]) continue;
			bx1 = ax1 + dx[d];
			by1 = ay1 + dy[d];
			bx2 = ax2;
			by2 = ay2;
			if (! valid(bx1, by1, bx2, by2)) continue;

			nxt = Info(bx1, by1, bx2, by2);
			if (dis[nxt.x][nxt.y][nxt.d] < 0) {
				if (cost[ax1][ay1][d]) {
					dis[nxt.x][nxt.y][nxt.d] = dis[cur.x][cur.y][cur.d] + 1;
					que.push_back(nxt);
				} else {
					dis[nxt.x][nxt.y][nxt.d] = dis[cur.x][cur.y][cur.d];
					que.push_front(nxt);
				}
				if (ok(bx1, by1, bx2, by2)) {
					return dis[nxt.x][nxt.y][nxt.d];
				}
			}
		}

		for(int d = 0; d < 4; ++ d) {
			if (! to[ax2][ay2][d]) continue;
			bx2 = ax2 + dx[d];
			by2 = ay2 + dy[d];
			bx1 = ax1;
			by1 = ay1;
			if (! valid(bx1, by1, bx2, by2)) continue;

			nxt = Info(bx1, by1, bx2, by2);
			if (dis[nxt.x][nxt.y][nxt.d] < 0) {
				if (cost[ax2][ay2][d]) {
					dis[nxt.x][nxt.y][nxt.d] = dis[cur.x][cur.y][cur.d] + 1;
					que.push_back(nxt);
				} else {
					dis[nxt.x][nxt.y][nxt.d] = dis[cur.x][cur.y][cur.d];
					que.push_front(nxt);
				}
				if (ok(bx1, by1, bx2, by2)) {
					return dis[nxt.x][nxt.y][nxt.d];
				}
			}
		}
	}
	return -1;
}

char buf[100];

int main() {
	cin >> n >> m;
	gets(buf);
	for(int i = 1; i <= n + 2; ++ i) {
		for(int j = 1; j <= m + 2; ++ j) {
			for(int d = 0; d < 4; ++ d) {
				to[i][j][d] = false;
				int ni = i + dx[d];
				int nj = j + dy[d];
				if (valid(ni, nj)) {
					to[i][j][d] = true;
				}
			}
		}
	}
	int ret = solve();
	if (ret < 0) {
		cout << "Death" << endl;
		return 0;
	}
	cout << ret << endl;
	return 0;
}
