#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

const int N = 1111;
const int LIMIT = 11111;
const int INF = 111111111;

struct Node {
	Node *child[4];
	Node *fail;
	int id, isEnd;
	void clear() {
		memset(child, 0, sizeof(child));
		isEnd = 0;
	}
}mem[LIMIT];


vector<Node*> queue;
Node *root;

int t, used = 0;
char str[N];
int f[N][N], tot;

int getID(char x) {
	if (x == 'A') {
		return 0;
	} else if (x == 'C') {
		return 1;
	} else if (x == 'G') {
		return 2;
	} else {
		return 3;
	}
}

Node* newNode() {
	mem[++used].clear();
	return &mem[used];
}

void bfs() {
	queue.clear();
	queue.push_back(root);
	root->fail = NULL;
	for(int head = 0; head < (int)queue.size(); head++) {
		Node *x = queue[head];
		x->id = head;
		for(int i = 0; i < 4; i++) {
			Node* y = x->child[i];
			if (y == NULL) {
				continue;
			}
			queue.push_back(y);
			if (x == root) {
				y->fail = root;
			} else {
				Node *tmp = x->fail;
				while(tmp != NULL && tmp->child[i] == NULL) {
					tmp = tmp->fail;
				}
				if (tmp == NULL) {
					y->fail = root;
				} else {
					y->fail = tmp->child[i];
				}
				if (y->fail->isEnd) {
					y->isEnd = 1;
				}
			}
		}
	}
	tot = (int)queue.size();
}

int main() {
	while(scanf("%d", &t) == 1 && t) {
		used = 0;
		root = newNode();
		for(int i = 0; i < t; i++) {
			scanf("%s", str + 1);
			Node *r = root;
			for(int j = 1; str[j]; j++) {
				int idx = getID(str[j]);
				if (r->child[idx] == NULL) {
					r->child[idx] = newNode();
				}
				r = r->child[idx];
			}
			r->isEnd = 1;
		}
		bfs();
		scanf("%s", str + 1);
		int n = strlen(str + 1);
		static int testCount = 0;
		printf("Case %d: ", ++testCount);
		for(int i = 0; i <= n; i++)
			for(int j = 0; j < tot; j++) {
				f[i][j] = INF;
			}
		f[0][0] = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < tot; j++) {
				if (queue[j]->isEnd) {
					continue;
				}
				int id = getID(str[i + 1]);
				for(int k = 0; k < 4; k++) {
					Node *t = queue[j];
					while(t != root && t->child[k] == NULL) {
						t = t->fail;
					}
					if (t->child[k]) {
						t = t->child[k];
					}
					f[i + 1][t->id] = min(f[i + 1][t->id], f[i][j] + (id != k));
				}
			}
		int ans = INF;
		for(int i = 0; i < tot; i++) {
			if (queue[i]->isEnd == 0) {
				ans = min(ans, f[n][i]);
			}
		}
		if (ans == INF) {
			printf("-1\n");
		} else {
			printf("%d\n", ans);
		}
	}
	return 0;
}

