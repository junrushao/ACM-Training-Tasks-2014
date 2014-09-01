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

const int N = 100 + 10;
const int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};

int n, m;
vector<pair<int, int> > cur;
char a[N][N];
char d[N][N];
vector<pair<int, int> > b[10];

int valid(int x, int y)
{
	return x >= 0 && x < n && y >= 0 && y < m;
}

void dfs(int x, int y)
{
	a[x][y] = '0';
	cur.push_back(make_pair(x, y));
	for(int i = 0; i < 8; ++ i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (valid(nx, ny) && a[nx][ny] == '1') {
			dfs(nx, ny);
		}
	}
}

vector<pair<int, int> > uniform(vector<pair<int, int> > rec)
{
	pair<int, int> x = rec[0];
	for(int i = 0; i < (int)rec.size(); ++ i) {
		x = min(x, rec[i]);
	}
	for(int i = 0; i < (int)rec.size(); ++ i) {
		rec[i].first -= x.first;
		rec[i].second -= x.second;
	}
	sort(rec.begin(), rec.end());
	return rec;
}

vector<pair<int, int> > rot(vector<pair<int, int> > vec)
{
	for(int i = 0; i < (int)vec.size(); ++ i) {
		swap(vec[i].first, vec[i].second);
		vec[i].second *= -1;
	}
	return vec;
}

vector<pair<int, int> > flip(vector<pair<int, int> > vec)
{
	for(int i = 0; i < (int)vec.size(); ++ i) {
		vec[i].second *= -1;
	}
	return vec;
}

void solve() {
	for(int i = 0; i < n; ++ i) {
		scanf("%s", a[i]);
		for(int j = 0; j < m; ++ j) {
			d[i][j] = '0';
		}
		d[i][m] = 0;
	}
	
	char color = 'A';
	map<vector<pair<int, int> >, char> c;
	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j < m; ++ j) {
			if (a[i][j] == '1') {
				cur.clear();
				dfs(i, j);
				vector<pair<int, int> > rec = cur;

				b[0] = uniform(cur);
				for(int k = 1; k < 4; ++ k) {
					cur = rot(cur);
					b[k] = uniform(cur);
				}
				cur = flip(cur);
				b[4] = uniform(cur);
				for(int k = 5; k < 8; ++ k) {
					cur = rot(cur);
					b[k] = uniform(cur);
				}
				cur = b[0];
				for(int k = 1; k < 8; ++ k) {
					cur = min(cur, b[k]);
				}
				/*
				for(int k = 0; k < 8; ++ k) {
					for(int l = 0; l < b[k].size(); ++ l) {
						cout << b[k][l].first << ' ' << b[k][l].second << endl;
					}
					cout << endl;
				}
				cout << endl;
				return;
				*/
				if (c.count(cur) == 0) {
					c[cur] = color;
					if (color == 'Z')
						color = 'a';
					else ++ color;
				}
				char tmp = c[cur];
				for(int k = 0; k < (int)rec.size(); ++ k) {
					d[rec[k].first][rec[k].second] = tmp;
				}
			}
		}
	}
	cout << c.size() << endl;
	for(int i = 0; i < n; ++ i) {
		puts(d[i]);
	}
}

int main() {
	int flag = false;
	for( ; cin >> n >> m && (n || m); ) {
		if (flag) cout << endl;
		flag = true;
		solve();
	}
	return 0;
}
