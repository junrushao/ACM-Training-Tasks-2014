#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

const int N = 30005;
const int M = 2000005;

int dx[3][3];
int dy[3][3];
int number, tot, top, color;
int n, m, x[N], y[N], done[N], pos[N];
int dfn[N], low[N], belong[N], s[N], in[N];
int e[M], succ[M], last[N], sum;
int q[N], type[N], hashNow[N], hashCnt;

vector <pair <int, int> > v[N];

void add(int a, int b) {
	e[++sum] = b, succ[sum] = last[a], last[a] = sum;
}

void res(int a, int b, int v) {
	int ta = type[a], tb = type[b];	
	int ok1 = (abs(x[a] + dx[ta][1] - (x[b] + dx[tb][1])) + abs(y[a] + dy[ta][1] - (y[b] + dy[tb][1])) == v);
	int ok2 = (abs(x[a] + dx[ta][1] - (x[b] + dx[tb][2])) + abs(y[a] + dy[ta][1] - (y[b] + dy[tb][2])) == v);
	if (ok1 && !ok2) {
		add(pos[a], pos[b]);
	} else if (!ok1 && ok2) {
		add(pos[a], pos[b] + number);
	} else if (!ok1 && !ok2) {
		add(pos[a], pos[a] + number);
	}

	ok1 = (abs(x[a] + dx[ta][2] - (x[b] + dx[tb][1])) + abs(y[a] + dy[ta][2] - (y[b] + dy[tb][1])) == v);
	ok2 = (abs(x[a] + dx[ta][2] - (x[b] + dx[tb][2])) + abs(y[a] + dy[ta][2] - (y[b] + dy[tb][2])) == v);	
	if (ok1 && !ok2) {
		add(pos[a] + number, pos[b]);
	} else if (!ok1 && ok2) {
		add(pos[a] + number, pos[b] + number);
	} else if (!ok1 && !ok2) {
		add(pos[a] + number, pos[a]);
	}
}

void dfs(int now) {
	dfn[now] = low[now] = ++tot;
	s[++top] = now;
	in[now] = 1;
	for (int x = last[now]; x; x = succ[x]) {
		int y = e[x];
		if (dfn[y] == 0)
			dfs(y), low[now] = min(low[now], low[y]);
		else if (in[y] == 1)
			low[now] = min(low[now], dfn[y]);
	}

	if (dfn[now] == low[now]) {
		color++;
		while (s[top] != now) {
			belong[s[top]] = color;
			in[s[top]] = 0;
			top--;
		}

		belong[s[top]] = color;
		in[s[top]] = 0;
		top--;
	}
}

int doWith(int st, int typeWithSt) {
	int h, t;
	type[st] = typeWithSt;
	hashCnt++;
	hashNow[st] = hashCnt;
	q[1] = st;
	number = 0;
	for (h = t = 1; h <= t; h++) {
		int now = q[h];
		pos[now] = ++number;
		done[now] = 1;
		for (vector <pair <int, int> > :: iterator it = v[now].begin(); it != v[now].end(); ++it) {
			int id = it->first, disNeed = it->second, typeNeed;
			if ((abs(x[now] - x[id]) + abs(y[now] - y[id]) & 1) == (disNeed & 1)) {
				typeNeed = type[now];
			} else {
				typeNeed = 3 - type[now];
			}

			if (hashNow[id] == hashCnt) {
				if (type[id] != typeNeed) {
					return 0;
				}
			} else {
				type[id] = typeNeed;
				hashNow[id] = hashCnt;
				q[++t] = id;
			}
		}
	}

	for (int i = 1; i <= number; i++) {
		last[i] = last[i + number] = 0;
		dfn[i] = low[i] = in[i] = 0;
		dfn[i + number] = low[i + number] = in[i + number] = 0;
	}

	sum = 0;
	for (h = 1; h <= t; h++) {
		int now = q[h];
		for (vector <pair <int, int> > :: iterator it = v[now].begin(); it != v[now].end(); ++it) {
			int id = it->first;
			res(now, id, it->second);
		}
	}

	tot = top = color = 0;
	for (int i = 1; i <= number + number; i++) {
		if (dfn[i] == 0) {
			dfs(i);
		}
	}

	for (int i = 1; i <= number; i++) {
		if (belong[i] == belong[i + number]) {
			return 0;
		}
	}
}

void work() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &x[i], &y[i]);
		v[i].clear();
		done[i] = 0;
		type[i] = 0;
	}

	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		v[a].push_back(make_pair(b, c));
		v[b].push_back(make_pair(a, c));
	}

	for (int i = 1; i <= n; i++) {
		if (!done[i]) {
			if (!doWith(i, 1) && !doWith(i, 2)) {
				printf("impossible\n");
				return;
			}
		}
	}

	printf("possible\n");
	return;
}

int test;

int main() {
	dx[1][1] = 0, dy[1][1] = 0;
	dx[1][2] = 1, dy[1][2] = 1;
	dx[2][1] = 1, dy[2][1] = 0;
	dx[2][2] = 0, dy[2][2] = 1;
	scanf("%d", &test);
	while (test--) {
		work();
	}

	return 0;
}

