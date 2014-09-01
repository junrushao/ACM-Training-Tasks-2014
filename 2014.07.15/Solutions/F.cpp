#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

const int MAXV = 100000;
const int N = 5005;

int bfsHash[N], bfsHashTag;
int hashNow[N], h_tag;
int val[N][N], v[N][N];
int q1[N], q2[N], h1, t1, h2, t2;
int f[N], size[N], rel[N], need[N];
int n, m;
long long ans;

vector <pair <int, int> > edge[MAXV + 5];

int find(int i) {
	if (f[i] == i) {
		return f[i];
	}

	return f[i] = find(f[i]);
}

void bfs(int s, int q[], int &h, int &t) {
	q[1] = s;
	bfsHashTag++;
	bfsHash[s] = bfsHashTag;
	for (h = t = 1; h <= t; h++) {
		int now = q[h], s = v[now][0];
		for (int i = 1; i <= s; i++) {
			int x = v[now][i];
			if (bfsHash[x] != bfsHashTag) {
				q[++t] = x;
				bfsHash[x] = bfsHashTag;
			}
		}
	}
}

void merge(int a, int b, int vnow) {
	rel[b] += rel[a];
	need[b] += need[a];
	bfs(a, q1, h1, t1);
	bfs(b, q2, h2, t2);
	for (int i = 1; i <= t1; i++) {
		for (int j = 1; j <= t2; j++) {
			int x = q1[i], y = q2[j];
			if (val[x][y]) {
				need[b]++;
			}
		}
	}

	//printf("%d %d %d\n", a, b, vnow);
	//printf("rel = %d need = %d\n", rel[b], need[b]);
	v[b][++v[b][0]] = a;
	f[a] = b;
	size[b] += size[a];
	size[a] = 0;
}

void work() {
	for (int i = 1; i <= MAXV; i++) {
		edge[i].clear();
	}

	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			val[i][j] = 0;
		}
	}

	for (int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		val[a][b] = val[b][a] = c;
		edge[c].push_back(make_pair(a, b));
	}

	for (int i = 1; i <= n; i++) {
		f[i] = i;
		need[i] = 0;
		rel[i] = 0;
		size[i] = 1;
		v[i][0] = 0;
	}

	ans = 0;
	for (int i = MAXV; i >= 1; i--) {
		for (vector <pair <int, int> > :: iterator it = edge[i].begin(); it != edge[i].end(); ++it) {
			int a = it->first, b = it->second, fa = find(a), fb = find(b);
			if (fa == fb) {
				rel[fb]++;
			} else {
				merge(fa, fb, i);
				rel[fb]++;
			}
		}

		h_tag++;
		for (vector <pair <int, int> > :: iterator it = edge[i].begin(); it != edge[i].end(); ++it) {
			int a = it->first, b = it->second, fa = find(a), fb = find(b);
			if (fa == fb) {
				if (hashNow[fa] == h_tag) {
					continue;
				} else if (rel[fa] == need[fa]) {
					hashNow[fa] = h_tag;
					ans += size[fa];
				}
			}
		}
	}

	cout << ans << endl;
}

int test;

int main() {
	scanf("%d", &test);
	while (test--)
		work();
	return 0;
}

