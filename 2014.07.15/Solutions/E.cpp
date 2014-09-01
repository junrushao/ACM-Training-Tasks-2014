#include <cstdio>
#include <cstdlib>

const int mo = 9999991;

const int N = 25;

int ans, tot, root, n, test;
int size[N], val[N], ch[N][2];
int C[N][N];

void insert(int now, int v) {
	if (v < val[now]) {
		if (ch[now][0] == 0)
			ch[now][0] = ++tot, val[tot] = v;
		else
			insert(ch[now][0], v);
	} else {
		if (ch[now][1] == 0)
			ch[now][1] = ++tot, val[tot] = v;
		else
			insert(ch[now][1], v);
	}
}

void dfs(int i) {
	if (ch[i][0] == 0 && ch[i][1] == 0) {
		if (i != 0) {
			size[i] = 1;
		}

		return;
	}

	dfs(ch[i][0]);
	dfs(ch[i][1]);
	size[i] = size[ch[i][0]] + 1 + size[ch[i][1]];
	if (ch[i][0] > 0 && ch[i][1] > 0) {
		ans = (long long)ans * C[size[i] - 1][size[ch[i][0]]] % mo;
	}
}

void work() {
	scanf("%d", &n);
	for (int i = 1; i <= 20; i++) {
		ch[i][0] = ch[i][1] = val[i] = 0;
	}

	root = tot = 1;
	int x;
	scanf("%d", &x);
	val[1] = x;
	for (int i = 2; i <= n; i++) {
		int x;
		scanf("%d", &x);
		insert(root, x);
	}

	ans = 1;
	//printf("%d\n", tot);
	dfs(1);
	printf("%d\n", ans);
}

int main() {
	C[0][0] = 1;
	for (int i = 1; i <= 20; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mo;
		}
	}
	scanf("%d", &test);
	while (test--)
		work();
	return 0;
}

