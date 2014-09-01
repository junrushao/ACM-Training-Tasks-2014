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

const int N = 400000 + 10;

struct Info
{
	int cntBlack, cntWhite;
	Info() {}
	Info(int cntBlack, int cntWhite) : cntBlack(cntBlack), cntWhite(cntWhite) {
	}
	void flipMe() {
		swap(cntBlack, cntWhite);
	}
	void clear() {
		cntBlack = cntWhite = 0;
	}
};

Info operator + (const Info &a, const Info &b) {
	return Info(a.cntBlack + b.cntBlack, a.cntWhite + b.cntWhite);
}

struct Tree
{
	bool flip1, flip2;
	int l, r;
	Tree *ch[2];
	Info count;
	Tree() {}
	Tree(int, int);
	void appFlip1(int, int);	
	void getFlip1() {
		flip1 ^= true;
		count.flipMe();
	}
	void appFlip2(int, int);	
	int countIt(int, int);
	int getCnt(int);
	void relax() {
		if (flip1) {
			ch[0]->getFlip1();
			ch[1]->getFlip1();
			flip1 = false;
		}
	}
} nodePool[N], *totNode, *root[N];

int n;
vector<int> adj[N];
int color[N];
int father[N], size[N], depth[N], treeSize[N];
int bfsOrd[N], pathId[N], ordInPath[N];

Tree::Tree(int _l, int _r) 
{
	l = _l; r = _r;
	count.clear();
	flip1 = flip2 = 0;
	if (l == r) {
		if (l) count.cntWhite = 1;
		return;
	}
	int mid = (l + r) >> 1;
	ch[0] = new(totNode ++) Tree(l, mid);
	ch[1] = new(totNode ++) Tree(mid + 1, r);
	count = ch[0]->count + ch[1]->count;
}

void Tree::appFlip1(int a, int b)
{
	if (b < l || a > r) return;
	if (a <= l && r <= b) {
		getFlip1();
		return;
	}
	relax();
	ch[0]->appFlip1(a, b);
	ch[1]->appFlip1(a, b);
	count = ch[0]->count + ch[1]->count;
}

void Tree::appFlip2(int a, int b)
{
	if (b < l || a > r) return;
	if (a <= l && r <= b) {
		flip2 ^= true;
		return;
	}
	relax();
	ch[0]->appFlip2(a, b);
	ch[1]->appFlip2(a, b);
	count = ch[0]->count + ch[1]->count;
}

int Tree::countIt(int a, int b)
{
	if (b < l || a > r) return 0;
	if (a <= l && r <= b) {
		return count.cntBlack;
	}
	relax();
	int ret = ch[0]->countIt(a, b) + ch[1]->countIt(a, b);
	count = ch[0]->count + ch[1]->count;
	return ret;
}

int Tree::getCnt(int p)
{
	if (p < l || p > r) return 0;
	if (l == r) {
		return flip2;
	}
	relax();
	int ret = ch[0]->getCnt(p) ^ ch[1]->getCnt(p) ^ flip2;
	count = ch[0]->count + ch[1]->count;
	return ret;
}

void doBfs(int s)
{
	int *que = bfsOrd;
	int qh = 0, qt = 0;
	father[s] = -1;
	depth[s] = 0;
	for(que[qt ++] = s; qh < qt; ) {
		int u = que[qh ++];
		for(int i = 0; i < (int)adj[u].size(); ++ i) {
			int v = adj[u][i];
			if (v == father[u]) continue;
			father[v] = u;
			depth[v] = depth[u] + 1;
			que[qt ++] = v;
		}
	}
}

void doSplit()
{
	for(int i = n - 1; i >= 0; -- i) {
		int u = bfsOrd[i];
		size[u] = 1;
		for(int j = 0; j < (int)adj[u].size(); ++ j) {
			int v = adj[u][j];
			if (v == father[u])
				continue;
			size[u] += size[v];
		}
	}

	memset(pathId, -1, sizeof pathId);
	for(int i = 0; i < n; ++ i) {
		int top = bfsOrd[i];
		if (pathId[top] != -1) continue;
		int cnt = 0;
		for(int u = top; u != -1; ) {
			ordInPath[u] = cnt;
			pathId[u] = top;
			++ cnt;

			int nxt = -1;
			for(int j = 0; j < (int)adj[u].size(); ++ j) {
				int v = adj[u][j];
				if (v == father[u]) continue;
				if (nxt < 0 || size[nxt] < size[v]) {
					nxt = v;
				}
			}

			u = nxt;
		}

		treeSize[top] = cnt;
		root[top] = new(totNode ++) Tree(0, cnt - 1);
	}
}

void reverseEdge(int u, int v)
{
	int l, r;
	for( ; ; ) {
		if (pathId[u] == pathId[v]) {
			l = ordInPath[u];
			r = ordInPath[v];
			if (l > r) swap(l, r);
			if (l != r)
				root[pathId[u]]->appFlip1(l + 1, r);
			return;
		} 
	   	if (depth[pathId[u]] >= depth[pathId[v]]) {
			l = 0;
			r = ordInPath[u];
			if (l != r)
			   	root[pathId[u]]->appFlip1(l + 1, r);
			u = pathId[u];
			color[u] ^= true;
			u = father[u];
		} else {
			l = 0;
			r = ordInPath[v];
			if (l != r)
				root[pathId[v]]->appFlip1(l + 1, r);
			v = pathId[v];
			color[v] ^= true;
			v = father[v];
		}
	}
}

void reverseNeighbor(int u, int v)
{
	int l, r;
	for( ; ; ) {
		if (pathId[u] == pathId[v]) {
			l = ordInPath[u];
			r = ordInPath[v];
			if (l > r) swap(l, r);
			root[pathId[u]]->appFlip2(l, r);
			if (l) 
				root[pathId[u]]->appFlip1(l, l);
			if (r + 1 < treeSize[pathId[u]]) 
				root[pathId[u]]->appFlip1(r + 1, r + 1);
			return;
		} 
	   	if (depth[pathId[u]] >= depth[pathId[v]]) {
			l = 0;
			r = ordInPath[u];
			root[pathId[u]]->appFlip2(l, r);
			if (l) 
				root[pathId[u]]->appFlip1(l, l);
			if (r + 1 < treeSize[pathId[u]]) 
				root[pathId[u]]->appFlip1(r + 1, r + 1);
			u = pathId[u];
			u = father[u];
		} else {
			l = 0;
			r = ordInPath[v];
			root[pathId[v]]->appFlip2(l, r);
			if (l) 
				root[pathId[v]]->appFlip1(l, l);
			if (r + 1 < treeSize[pathId[v]]) 
				root[pathId[v]]->appFlip1(r + 1, r + 1);
			v = pathId[v];
			v = father[v];
		}
	}
}

int countBlack(int u, int v)
{
	int ret = 0;
	int l, r;
	for( ; ; ) {
		if (pathId[u] == pathId[v]) {
			l = ordInPath[u];
			r = ordInPath[v];
			if (l > r) swap(l, r);
			if (l != r) 
				ret += root[pathId[u]]->countIt(l + 1, r);
			return ret;
		} 
	   	if (depth[pathId[u]] >= depth[pathId[v]]) {
			l = 0;
			r = ordInPath[u];
			if (l != r) 
				ret += root[pathId[u]]->countIt(l + 1, r);
			u = pathId[u];
			ret += (color[u] ^ root[u]->getCnt(0) ^ root[pathId[father[u]]]->getCnt(ordInPath[father[u]]));
			u = father[u];
		} else {
			l = 0;
			r = ordInPath[v];
			if (l != r) 
				ret += root[pathId[v]]->countIt(l + 1, r);
			v = pathId[v];
			ret += (color[v] ^ root[v]->getCnt(0) ^ root[pathId[father[v]]]->getCnt(ordInPath[father[v]]));
			v = father[v];
		}
	}
}

void solve() {
	totNode = nodePool;
	cin >> n;
	for(int i = 0; i < n; ++ i) {
		adj[i].clear();
		color[i] = 0;
	}
	int u, v;
	for(int i = 0; i < n - 1; ++ i) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	doBfs(0);
	doSplit();

	int q, t;
	cin >> q;
	for( ; q --; ) {
		scanf("%d%d%d", &t, &u, &v);
		-- u, -- v;
		if (t == 1) {
			reverseEdge(u, v);
		}
		if (t == 2) {
			reverseNeighbor(u, v);
		}
		if (t == 3) {
			printf("%d\n", countBlack(u, v));
		}
	}
}

int main() {
	int test;
	cin >> test;
	for( ; test --; ) {
		solve();
	}
	return 0;
}
