#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 55;
const int M = 258;

char board[N][N];
bool visit[N][N];

int w, h, m;
char faces[N][6];
int perm[6];

int crawl[2][6] = {
	{1, 5, 2, 3, 0, 4},//DOWN
	{2, 1, 5, 0, 4, 3},//LEFT
};

int tr[3][6] = {
{3, 1, 0, 5, 4, 2},
{4, 0, 2, 3, 5, 1},
{0, 3, 1, 4, 2, 5}
};

bool isOk(int x, int y) {
	if (board[x][y] != '.' && !visit[x][y]) {
		return true;
	} else {
		return false;
	}
}


void go(char a[], int b[]) {
	static char temp[N];
	for(int i = 0; i < 6; i++) {
		temp[i] = a[i];
	}
	for(int i = 0; i < 6; i++) {
		a[i] = temp[b[i]];
	}
}

void go(int a[], int b[]) {
	static int temp[N];
	for(int i = 0; i < 6; i++) {
		temp[i] = a[i];
	}
	for(int i = 0; i < 6; i++) {
		a[i] = temp[b[i]];
	}
}

void dfs(int x, int y) {
//printf("%d %d\n", x, y);
	faces[m][perm[0]] = board[x][y];
	visit[x][y] = 1;
	
	if (x > 1 && isOk(x - 1, y)) {
		go(perm, crawl[0]);
		dfs(x - 1, y);	
		go(perm, crawl[0]);
		go(perm, crawl[0]);
		go(perm, crawl[0]);
	}
	if (y < w && isOk(x, y + 1)) {
		go(perm, crawl[1]);
		go(perm, crawl[1]);
		go(perm, crawl[1]);
		dfs(x, y + 1);
		go(perm, crawl[1]);
	}
	if (x < h && isOk(x + 1, y)) {
		go(perm, crawl[0]);
		go(perm, crawl[0]);
		go(perm, crawl[0]);
		dfs(x + 1, y);
		go(perm, crawl[0]);
	}
	if (y > 1 && isOk(x, y - 1)) {
		go(perm, crawl[1]);
		dfs(x, y - 1);
		go(perm, crawl[1]);
		go(perm, crawl[1]);
		go(perm, crawl[1]);
	}
}

int number[M], used[N];
char fcolor[N];
char per[N];
vector<char> colors;
bool over;
int vis[N];

int goCheck(int aa, int bb, int cc) {
	int a = fcolor[aa], b = fcolor[bb], c = fcolor[cc];
	for(int i = 1; i <= 8; i++) 
		if (!vis[i]) {
			for(int k = 0; k < 3; k++) {
				if (a == faces[i][k % 3] && b == faces[i][(1 + k) % 3] && c == faces[i][(2 + k) % 3]) {
					vis[i] = 1;
					return true;
				}
			}
		}
	return false;
}

void search(int dep) {
	if (over) {
		return ;
	}
	if (dep == 6) {
		for(int i = 1; i <= 8; i++) {
			vis[i] = false;
		}
		if (!goCheck(0, 1, 2)) {
			return ;
		}
		if (!goCheck(3, 1, 0)) {
			return ;
		}
		if (!goCheck(5, 1, 3)) {
			return ;
		}
		if (!goCheck(2, 1, 5)) {
			return ;
		}
		if (!goCheck(0, 2, 4)) {
			return ;
		}
		if (!goCheck(3, 0, 4)) {
			return ;
		}
		if (!goCheck(5, 3, 4)) {
			return ;
		}
		if (!goCheck(2, 5, 4)) {
			return ;
		}
		over = true;
		return ;
	}
	for(int i = 0; i < 6; i++) {
		if (!used[i]) {
			used[i] = 1;
			fcolor[dep] = colors[i];
			search(dep + 1);
			used[i] = 0;
		}
	}
}

int solve() {
	if (m != 8) {
		return 0;
	}
	
	/*
	puts("phase 1");
	for(int i = 1; i <= 8; i++, printf("\n"))
		for(int j = 0; j < 6; j++) {
			printf("%c", faces[i][j]);
		}
	puts("");
	*/
	
	for(int i = 1; i <= m; i++) {
		int isBlack = 0;
		for(int j = 0; j < 6; j++) {
			if (faces[i][j] == '#') {
				isBlack++;
			} else {
				colors.push_back(faces[i][j]);
				number[faces[i][j]]++;
			}
		}
		if (isBlack != 3) {
			return 0;
		}
		bool flag = false;
		for(int j = 0; j < 4 && !flag; j++)
			for(int k = 0; k < 4 && !flag; k++)
				for(int l = 0; l < 4 && !flag; l++) {
					for(int it = 0; it < 6; it++) {
						per[it] = faces[i][it];
					}
					for(int o = 0; o < j; o++) {
						go(per, tr[0]);
					}
					for(int o = 0; o < k; o++) {
						go(per, tr[1]);
					}
					for(int o = 0; o < l; o++) {
						go(per, tr[2]);
					}
					if (per[3] == '#' && per[4] == '#' && per[5] == '#') {
						flag = true;
						for(int o = 0; o < 6; o++) {
							faces[i][o] = per[o];
						}
					}
				}
		if (!flag) {
			return 0;
		}
	}
	//puts("phase 2");
	
	sort(colors.begin(), colors.end());
	colors.erase(unique(colors.begin(), colors.end()), colors.end());
	if ((int)colors.size() != 6) {
		return 0;
	}
	for(int i = 0; i < (int)colors.size(); i++) {
		if (number[colors[i]] != 4) {
			return 0;
		}
	}
	//printf("WoW\n");
	over = false;
	search(0);
	return over;
}

int main() {
	scanf("%d %d", &h, &w);
	for(int i = 1; i <= h; i++) {
		scanf("%s", board[i] + 1);
	}
	
	m = 0; 
	for(int i = 1; i <= h; i++)
		for(int j = 1; j <= w; j++) {
			if (visit[i][j] || board[i][j] == '.') {
				continue;	
			}
			++m;
			for(int k = 0; k < 6; k++) {
				perm[k] = k;
			}
			dfs(i, j);
		}
	if (solve()) {
		puts("Yes");
	} else {
		puts("No");
	}
	return 0; 
}
