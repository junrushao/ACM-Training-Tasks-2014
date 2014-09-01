#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 250;
int n, head, tail, Start, Finish, match[N], Father[N], Base[N], Q[N];
bool mark[N], mat[N][N], InBlossom[N], in_Queue[N];

void BlossomContract(int x, int y) {
	memset(mark, 0, sizeof(mark));
	memset(InBlossom, 0, sizeof(InBlossom));
#define pre Father[match[i]]
	int lca, i;
	for (i = x; i; i = pre) {
		i = Base[i];
		mark[i] = true;
	}

	for (i = y; i; i = pre) {
		i = Base[i];
		if (mark[i]) {
			lca = i;
			break;
		}
	}

	for (i = x; Base[i] != lca; i = pre) {
		if (Base[pre] != lca) {
			Father[pre] = match[i];
		}

		InBlossom[Base[i]] = true;
		InBlossom[Base[match[i]]] = true;
	}

	for (i = y; Base[i] != lca; i = pre) {
		if (Base[pre] != lca) {
			Father[pre] = match[i];
		}

		InBlossom[Base[i]] = true;
		InBlossom[Base[match[i]]] = true;
	}
#undef pre
	if (Base[x] != lca) Father[x] = y;
	if (Base[y] != lca) Father[y] = x;
	for (i = 1; i <= n; i++) {
		if (InBlossom[Base[i]]) {
			Base[i] = lca;
			if (!in_Queue[i]) {
				Q[++tail] = i;
				in_Queue[i] = true;
			}
		}
	}
}

void Change() {
	int x, y, z;
	z = Finish;
	while (z) {
		y = Father[z];
		x = match[y];
		match[y] = z;
		match[z] = y;
		z = x;
	}
}

void FindAugmentPath() {
	memset(Father, 0, sizeof(Father));
	memset(in_Queue, 0, sizeof(in_Queue));
	for (int i = 1; i <= n; i++) Base[i] = i;
	head = 0, tail = 1;
	Q[1] = Start;
	in_Queue[Start] = 1;
	while (head != tail) {
		int x = Q[++head];
		for (int y = 1; y <= n; y++) {
			if (mat[x][y] && Base[x] != Base[y] && match[x] != y) {
				if (Start == y || (match[y] && Father[match[y]])) {
					BlossomContract(x, y);
				} else if (!Father[y]) {
					Father[y] = x;
					if (match[y]) {
						Q[++tail] = match[y];
						in_Queue[match[y]] = true;
					} else {
						Finish = y;
						Change();
						return;
					}
				}
			}
		}
	}
}

void Edmonds() {
	memset(match, 0, sizeof(match));
	for (Start = 1; Start <= n; Start++) {
		if (match[Start] == 0) {
			FindAugmentPath();
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int tot;
		scanf("%d", &tot);
		while (tot--) {
			int x;
			scanf("%d", &x);
			mat[i][x] = 1;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i != j && (!mat[i][j] || !mat[j][i])) {
				mat[i][j] = mat[j][i] = 0;
			}
		}
	}

	Edmonds();
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		cnt += (match[i] > 0);
	}

	if (cnt == n) {
		printf("YES\n");
	} else {
		printf("NO\n");
	}

	return 0;
}
